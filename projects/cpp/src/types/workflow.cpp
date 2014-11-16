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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/object_types_io.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/io/formatters/formatter_types_io.hpp"
#include "dogen/cpp/types/meta_data/cpp_settings_factory.hpp"
#include "dogen/cpp/types/meta_data/facet_settings_factory.hpp"
#include "dogen/cpp/types/bundler.hpp"
#include "dogen/cpp/types/workflow.hpp"

namespace {

const std::string id("cpp.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

const std::string model_modules_not_found(
    "Could not find model module for model: ");
const std::string multiple_generatable_model_modules(
    "More than one model module is generatable: ");
const std::string unsupported_object_type("Object type is not supported: ");
const std::string unsupported_formatter_type(
    "Formatter type is not supported: ");

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

formatters::formatter_types workflow::
formatter_type_for_object_type(const sml::object_types ot) const {
    switch(ot) {
    case sml::object_types::factory:
    case sml::object_types::user_defined_service:
    case sml::object_types::user_defined_value_object:
    case sml::object_types::entity:
    case sml::object_types::keyed_entity:
    case sml::object_types::versioned_key:
    case sml::object_types::unversioned_key:
    case sml::object_types::visitor:
        return formatters::formatter_types::class_formatter;
        break;

    default:
        BOOST_LOG_SEV(lg, error) << unsupported_object_type << ot;
        BOOST_THROW_EXCEPTION(workflow_error(unsupported_object_type +
                boost::lexical_cast<std::string>(ot)));
    };
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

std::unordered_map<std::string, settings_bundle> workflow::
settings_bundle_for_facet_activty(
    const dogen::formatters::general_settings& gs,
    const sml::module& model_module) const {
    bundler b;
    return b.bundle(registrar().default_facet_settings_by_facet_id(),
        gs, model_module);
}

std::unordered_map<path_spec_key, boost::filesystem::path>
workflow::obtain_relative_file_names_for_key_activity(
    const cpp::registrar& rg, const settings_bundle& sb,
    const sml::model& m) const {

    std::unordered_map<path_spec_key, boost::filesystem::path> r;
    for (const auto& pair : m.objects()) {
        const auto qn(pair.first);
        const auto o(pair.second);

        const auto ft(formatter_type_for_object_type(o.object_type()));
        switch(ft) {
        case formatters::formatter_types::class_formatter:
            for (const auto f : rg.formatter_container().class_formatters()) {
                path_spec_key key(f->formatter_id(), qn);
                r.insert(std::make_pair(key, f->make_file_name(sb, qn)));
            }
            break;

        default:
            BOOST_LOG_SEV(lg, error) << unsupported_formatter_type << ft
                                     << " name: " << o.name();
            BOOST_THROW_EXCEPTION(workflow_error(unsupported_formatter_type +
                    boost::lexical_cast<std::string>(ft)));
        };
    }
    return r;
}

std::unordered_map<path_spec_key, path_spec_details> workflow::
obtain_path_spec_details_for_key_activity(
    const cpp::registrar& rg, const sml::model& m,
    const std::unordered_map<path_spec_key, boost::filesystem::path>&
    relative_file_names_for_key) const {

    std::unordered_map<path_spec_key, path_spec_details> r;
    for (const auto f : rg.formatter_container().class_formatters()) {
        auto b(f->make_path_spec_details_builder());
        auto psd(b->build(m, relative_file_names_for_key));
        r.insert(psd.begin(), psd.end());
    }
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

    registrar().validate();
    const auto& c(registrar().formatter_container());
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(
                                 c.class_formatters().begin(),
                                 c.class_formatters().end())
                             << " registered class formatter(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all class formatter.";
    for (const auto& f : c.class_formatters())
        BOOST_LOG_SEV(lg, debug) << "Id: '" << f->formatter_id() << "'";

    BOOST_LOG_SEV(lg, debug) << "Finished validating c++ backend workflow.";
}

std::forward_list<dogen::formatters::file> workflow::generate(
    const dogen::formatters::general_settings& gs,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started C++ backend.";

    const auto mod(obtain_model_module_activity(m));
    const auto sb(settings_bundle_for_facet_activty(gs, mod));
    // const auto& rg(registrar());
    // const auto rel(obtain_relative_file_names_for_key_activity(rg, sb, m));
    // const auto det(obtain_path_spec_details_for_key_activity(rg, m, rel));

    const formatter_facade ff(registrar(), sb);
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
