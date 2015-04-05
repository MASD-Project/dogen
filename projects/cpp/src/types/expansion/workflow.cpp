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
#include "dogen/cpp/types/expansion/path_derivatives_factory.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_factory.hpp"
#include "dogen/cpp/types/expansion/expansion_inputs.hpp"
#include "dogen/cpp/io/expansion/expansion_inputs_io.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/types/expansion/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.expansion.workflow"));

const std::string duplicate_qname("Duplicate qname: ");
const std::string model_module_not_found("Model module not found for model: ");

}

namespace dogen {
namespace cpp {
namespace expansion {

/**
 * @brief Generates all path derivatives.
 */
class path_derivatives_generator {
public:
    path_derivatives_generator(
        const std::unordered_map<std::string, settings::path_settings>& ps)
        : factory_(ps) { }

private:
    /**
     * @brief Generates all of the path derivatives for the formatters
     * and qualified name.
     */
    void generate_path_derivatives_for_qname(const sml::qname& qn);

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

void path_derivatives_generator::
generate_path_derivatives_for_qname(const sml::qname& qn) {
    const auto pair(result_.insert(std::make_pair(qn, factory_.make(qn))));
    const bool inserted(pair.second);
    if (!inserted) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
        BOOST_THROW_EXCEPTION(workflow_error(duplicate_qname + n));
    }
}

void path_derivatives_generator::operator()(const dogen::sml::object& o) {
    generate_path_derivatives_for_qname(o.name());
}

void path_derivatives_generator::operator()(const dogen::sml::enumeration& e) {
    generate_path_derivatives_for_qname(e.name());
}

void path_derivatives_generator::operator()(const dogen::sml::primitive& p) {
    generate_path_derivatives_for_qname(p.name());
}

void path_derivatives_generator::operator()(const dogen::sml::module& m) {
    generate_path_derivatives_for_qname(m.name());
}

void path_derivatives_generator::operator()(const dogen::sml::concept& c) {
    generate_path_derivatives_for_qname(c.name());
}

const std::unordered_map<sml::qname,
                         std::unordered_map<std::string, path_derivatives>
                         >& path_derivatives_generator::result() const {
    return result_;
}

/**
 * @brief Generates all inclusion dependencies.
 */
class inclusion_dependencies_generator {
public:
    inclusion_dependencies_generator(const container& c,
        const std::unordered_map<
            sml::qname,
            std::unordered_map<std::string, path_derivatives>
            >& pd)
        : factory_(c, pd) { }

private:
    /**
     * @brief Generates all of the path derivatives for the formatters
     * and qualified name.
     */
    template<typename Entity>
    void generate_inclusion_dependencies(const Entity& e) {
        const auto deps(factory_.make(e));
        const auto pair(result_.insert(std::make_pair(e.name(), deps)));
        const bool inserted(pair.second);
        if (!inserted) {
            const auto n(sml::string_converter::convert(e.name()));
            BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
            BOOST_THROW_EXCEPTION(workflow_error(duplicate_qname + n));
        }
    }

public:
    void operator()(const dogen::sml::object& o);
    void operator()(const dogen::sml::enumeration& e);
    void operator()(const dogen::sml::primitive& p);
    void operator()(const dogen::sml::module& m);
    void operator()(const dogen::sml::concept& c);

public:
    const std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, std::list<std::string> >
    >& result() const;

private:
    const inclusion_dependencies_factory factory_;
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, std::list<std::string> >
        > result_;
};

void inclusion_dependencies_generator::operator()(const dogen::sml::object& o) {
    generate_inclusion_dependencies(o);
}

void inclusion_dependencies_generator::
operator()(const dogen::sml::enumeration& e) {
    generate_inclusion_dependencies(e);
}

void inclusion_dependencies_generator::
operator()(const dogen::sml::primitive& p) {
    generate_inclusion_dependencies(p);
}

void inclusion_dependencies_generator::operator()(const dogen::sml::module& m) {
    generate_inclusion_dependencies(m);
}

void inclusion_dependencies_generator::
operator()(const dogen::sml::concept& c) {
    generate_inclusion_dependencies(c);
}

const std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, std::list<std::string> >
    >& inclusion_dependencies_generator::result() const {
    return result_;
}

dynamic::schema::object workflow::
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

std::unordered_map<std::string, settings::path_settings> workflow::
create_path_settings_activity(const config::cpp_options& opts,
    const dynamic::schema::repository& rp,
    const dynamic::schema::object& o) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating path settings.";
    settings::path_settings_factory f(opts, rp);
    const auto r(f.make(o));
    BOOST_LOG_SEV(lg, debug) << "Created path settings.";
    return r;
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, path_derivatives>
    > workflow::obtain_path_derivatives_activity(
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started obtaining path derivatives.";

    path_derivatives_generator g(ps);
    sml::all_model_items_traversal(m, g);

    BOOST_LOG_SEV(lg, debug) << "Finished obtaining path derivatives.";
    return g.result();
}

void workflow::initialise_registrar_activity(
    const formatters::container& fc, registrar& rg) const {

    BOOST_LOG_SEV(lg, debug) << "Started registering all providers.";
    for (const auto f : fc.all_formatters()) {
        BOOST_LOG_SEV(lg, debug) << "Registered: "
                                 << f->ownership_hierarchy().formatter_name();
        f->register_inclusion_dependencies_provider(rg);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished registering all providers.";
}


std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, std::list<std::string> >
    >
workflow::obtain_inclusion_dependencies_activity(
    const container& c, const std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, path_derivatives>
        >& pd, const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started obtaining inclusion dependencies.";

    inclusion_dependencies_generator g(c, pd);
    sml::all_model_items_traversal(m, g);

    BOOST_LOG_SEV(lg, debug) << "Finished obtaining inclusion dependencies.";
    return g.result();
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, expansion_inputs>
    >
workflow::merge_into_expansion_inputs_activity(
        const std::unordered_map<
            sml::qname,
            std::unordered_map<std::string, path_derivatives>
            >& pd,
            const std::unordered_map<
                sml::qname,
                std::unordered_map<std::string, std::list<std::string> >
                >& inclusion_dependencies) const {

    BOOST_LOG_SEV(lg, debug) << "Merging into expansion inputs.";
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, expansion_inputs>
        > r;

    for (const auto& qn_pair : pd) {
        auto& formatter_map(r[qn_pair.first]);
        for (const auto& fn_pair : qn_pair.second)
            formatter_map[fn_pair.first].path_derivatives(fn_pair.second);
    }

    for (const auto& qn_pair : inclusion_dependencies) {
        auto& formatter_map(r[qn_pair.first]);
        for (const auto& fn_pair : qn_pair.second)
            formatter_map[fn_pair.first].inclusion_dependencies(fn_pair.second);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished merging into expansion inputs.";
    return r;
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, expansion_inputs>
    >
workflow::execute(
    const config::cpp_options& opts, const dynamic::schema::repository& rp,
    const formatters::container& fc, const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";

    const auto ro(obtain_root_object_activity(m));
    const auto ps(create_path_settings_activity(opts, rp, ro));
    const auto pd(obtain_path_derivatives_activity(ps, m));

    registrar rg;
    initialise_registrar_activity(fc, rg);
    const auto d(obtain_inclusion_dependencies_activity(rg.container(), pd, m));
    const auto r(merge_into_expansion_inputs_activity(pd, d));

    BOOST_LOG_SEV(lg, debug) << "Finished workflow. Result: " << r;
    return r;
}

} } }
