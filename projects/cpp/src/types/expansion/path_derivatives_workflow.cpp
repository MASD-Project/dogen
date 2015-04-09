/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/pair_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/cpp/types/settings/path_settings_factory.hpp"
#include "dogen/cpp/types/expansion/path_derivatives.hpp"
#include "dogen/cpp/io/expansion/path_derivatives_io.hpp"
#include "dogen/cpp/types/expansion/path_derivatives_factory.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/types/expansion/path_derivatives_workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.expansion.path_derivatives_workflow"));

const std::string duplicate_qname("Duplicate qname: ");
const std::string model_module_not_found("Model module not found for model: ");

}

namespace dogen {
namespace cpp {
namespace expansion {

/**
 * @brief Generates all path derivatives.
 */
class generator {
public:
    generator(
        const std::unordered_map<std::string, settings::path_settings>& ps)
        : factory_(ps) { }

private:
    /**
     * @brief Generates all of the path derivatives for the formatters
     * and qualified name.
     */
    void generate(const sml::qname& qn);

public:
    void operator()(const dogen::sml::object& o);
    void operator()(const dogen::sml::enumeration& e);
    void operator()(const dogen::sml::primitive& p);
    void operator()(const dogen::sml::module& m);
    void operator()(const dogen::sml::concept& c);

public:
    const std::unordered_map<sml::qname,
                             std::unordered_map<std::string, path_derivatives>
                             >& result() const;

private:
    const path_derivatives_factory factory_;
    std::unordered_map<sml::qname,
                       std::unordered_map<std::string, path_derivatives>
                       > result_;
};

void generator::generate(const sml::qname& qn) {
    const auto pair(result_.insert(std::make_pair(qn, factory_.make(qn))));
    const bool inserted(pair.second);
    if (!inserted) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
        BOOST_THROW_EXCEPTION(workflow_error(duplicate_qname + n));
    }
}

void generator::operator()(const dogen::sml::object& o) {
    generate(o.name());
}

void generator::operator()(const dogen::sml::enumeration& e) {
    generate(e.name());
}

void generator::operator()(const dogen::sml::primitive& p) {
    generate(p.name());
}

void generator::operator()(const dogen::sml::module& m) {
    generate(m.name());
}

void generator::operator()(const dogen::sml::concept& c) {
    generate(c.name());
}

const std::unordered_map<sml::qname,
                         std::unordered_map<std::string, path_derivatives>
                         >& generator::result() const {
    return result_;
}

path_derivatives_workflow::
path_derivatives_workflow(const formatters::container& c)
    : container_(c) { }

dynamic::schema::object path_derivatives_workflow::
obtain_root_object_activity(const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining model's root object.";

    const auto i(m.modules().find(m.name()));
    if (i == m.modules().end()) {
        const auto n(sml::string_converter::convert(m.name()));
        BOOST_LOG_SEV(lg, error) << model_module_not_found << n;
        BOOST_THROW_EXCEPTION(workflow_error(model_module_not_found + n));
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained model's root object.";
    return i->second.extensions();
}

std::unordered_map<std::string, settings::path_settings>
path_derivatives_workflow::
create_path_settings_activity(const config::cpp_options& opts,
    const dynamic::schema::repository& rp,
    const dynamic::schema::object& o) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating path settings.";
    settings::path_settings_factory f(opts, rp, container_);
    const auto r(f.make(o));
    BOOST_LOG_SEV(lg, debug) << "Created path settings";
    return r;
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, path_derivatives>
    > path_derivatives_workflow::obtain_path_derivatives_activity(
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started obtaining path derivatives.";

    generator g(ps);
    sml::all_model_items_traversal(m, g);

    BOOST_LOG_SEV(lg, debug) << "Finished obtaining path derivatives.";
    return g.result();
}

// std::unordered_map<
//     sml::qname,
//     std::unordered_map<std::string, std::list<std::string> >
//     >
// workflow::obtain_inclusion_dependencies_activity(
//     const dynamic::schema::repository& rp, const container& c,
//     const std::unordered_map<
//         sml::qname,
//         std::unordered_map<std::string, path_derivatives>
//         >& pd, const sml::model& m) const {

//     BOOST_LOG_SEV(lg, debug) << "Started obtaining inclusion dependencies.";

//     inclusion_dependencies_generator g(rp, c, pd);
//     sml::all_model_items_traversal(m, g);

//     BOOST_LOG_SEV(lg, debug) << "Finished obtaining inclusion dependencies.";
//     return g.result();
// }

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, path_derivatives>
    >
path_derivatives_workflow::execute(
    const config::cpp_options& opts, const dynamic::schema::repository& rp,
    const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";

    const auto ro(obtain_root_object_activity(m));
    const auto ps(create_path_settings_activity(opts, rp, ro));
    const auto r(obtain_path_derivatives_activity(ps, m));

    // registrar rg;
    // initialise_registrar_activity(fc, rg);
    // const auto& c(rg.container());
    // const auto d(obtain_inclusion_dependencies_activity(rp, c, pd, m));
    // const auto r(merge_into_expansion_inputs_activity(pd, d));

    BOOST_LOG_SEV(lg, debug) << "Finished workflow. Result: " << r;
    return r;
}

} } }
