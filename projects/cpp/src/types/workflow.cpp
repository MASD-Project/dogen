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
#include <iterator>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/types/meta_data/facet_settings_factory.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/types/workflow.hpp"

namespace {

const std::string id("cpp.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

const std::string model_modules_not_found(
    "Could not find model module for model: ");
const std::string multiple_generatable_model_modules(
    "More than one model module is generatable: ");

}

namespace dogen {
namespace cpp {

std::shared_ptr<cpp::registrar> workflow::registrar_;

workflow::~workflow() noexcept { }

cpp::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::registrar>();

    return *registrar_;
}

std::forward_list<dogen::formatters::file> workflow::format_entity(
    const formatter_facade& ff, const entity& e) const {
    return ff.format(e);
}

sml::module workflow::obtain_model_module_activity(const sml::model& m) const {
    sml::module r;
    bool found(false);
    for (const auto pair : m.modules()) {
        const auto mod(pair.second);
        if (mod.generation_type() != sml::generation_types::full_generation ||
            mod.type() != sml::module_types::model)
            continue;

        if (found) {
            BOOST_LOG_SEV(lg, error) << multiple_generatable_model_modules
                                     << mod.name();

            const auto sn(mod.name().simple_name());
            BOOST_THROW_EXCEPTION(workflow_error(
                    multiple_generatable_model_modules + sn));
        }
        r = pair.second;
        found = true;
    }

    if (!found) {
        BOOST_LOG_SEV(lg, error) << model_modules_not_found
                                 << r.name();

        const auto sn(r.name().simple_name());
        BOOST_THROW_EXCEPTION(workflow_error(model_modules_not_found + sn));
    }
    return r;
}

std::unordered_map<std::string, facet_settings>
workflow::create_facet_settings_activity(const sml::module& m) const {
    meta_data::facet_settings_factory f;
    return f.build(
        registrar().default_facet_settings_by_facet_id(),
        m.meta_data());
}

cpp_settings
workflow::create_cpp_settings_activity(const sml::module& /*m*/) const {
    cpp_settings r;
    return r;
}

std::string workflow::id() const {
    return ::id;
}

std::vector<boost::filesystem::path> workflow::managed_directories() const {
    std::vector<boost::filesystem::path> r;
    return r;
}

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating c++ backend workflow.";

    const auto reg(registrar());
    reg.validate();
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(reg.class_formatters().begin(),
                                 reg.class_formatters().end())
                             << " registered class formatter(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all class formatter.";
    for (const auto& f : reg.class_formatters())
        BOOST_LOG_SEV(lg, debug) << "Id: '" << f->formatter_id() << "'";

    BOOST_LOG_SEV(lg, debug) << "Finished validating c++ backend workflow.";
}

std::forward_list<dogen::formatters::file> workflow::generate(
    const dogen::formatters::general_settings& gs,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started C++ backend.";

    const auto mod(obtain_model_module_activity(m));
    const auto cs(create_cpp_settings_activity(mod));
    const auto fs(create_facet_settings_activity(mod));

    const formatter_facade ff(registrar(), gs, cs, fs);
    std::forward_list<dogen::formatters::file> r;
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(m, ff, m.modules()));
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(m, ff, m.concepts()));
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(m, ff, m.primitives()));
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(m, ff, m.enumerations()));
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(m, ff, m.objects()));

    BOOST_LOG_SEV(lg, debug) << "Finished C++ backend.";
    return r;
}

} }
