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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/io/object_types_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/io/global_settings_io.hpp"
#include "dogen/cpp/io/file_settings_io.hpp"
#include "dogen/cpp/io/formatters/formatter_types_io.hpp"
#include "dogen/cpp/types/meta_data/cpp_settings_factory.hpp"
#include "dogen/cpp/types/meta_data/facet_settings_factory.hpp"
#include "dogen/cpp/types/global_settings_factory.hpp"
#include "dogen/cpp/types/formatters/facet_factory.hpp"
#include "dogen/cpp/types/formatters/container_splitter.hpp"
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
const std::string duplicate_formatter_id("Formatter id already inserted: ");
const std::string formatter_not_found("Formatter not found: ");

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

    case sml::object_types::exception:
        return formatters::formatter_types::exception_formatter;
        break;

    default:
        BOOST_LOG_SEV(lg, error) << unsupported_object_type << ot;
        BOOST_THROW_EXCEPTION(workflow_error(unsupported_object_type +
                boost::lexical_cast<std::string>(ot)));
    };
}

std::forward_list<dogen::formatters::file> workflow::format_entity(
    const formatters::workflow& fw, const entity& e) const {
    return fw.format(e);
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
            const auto n(sml::string_converter::convert(mod.name()));
            BOOST_LOG_SEV(lg, error) << multiple_generatable_model_modules << n;
            BOOST_THROW_EXCEPTION(workflow_error(
                    multiple_generatable_model_modules + n));
        }
        r = pair.second;
        found = true;
    }

    if (!found) {
        const auto n(sml::string_converter::convert(r.name()));
        BOOST_LOG_SEV(lg, error) << model_modules_not_found << n;
        BOOST_THROW_EXCEPTION(workflow_error(model_modules_not_found + n));
    }
    return r;
}

std::unordered_map<std::string, global_settings> workflow::
global_settings_for_facet_activty(
    const dogen::formatters::general_settings& gs,
    const sml::module& model_module) const {
    BOOST_LOG_SEV(lg, debug) << "Creating global settings by facet.";
    global_settings_factory f;
    const auto& defaults(registrar().default_facet_settings_by_facet_id());
    const auto r(f.build(defaults, gs, model_module));
    BOOST_LOG_SEV(lg, debug) << "Global settings: " << r;
    BOOST_LOG_SEV(lg, debug) << "Finsihed creating global settings by facet.";
    return r;
}

std::unordered_map<std::string, formatters::container> workflow::
formatter_container_for_facet_activty(
    const formatters::container& c) const {
    formatters::container_splitter s;
    return s.split_by_facet(c);
}

std::forward_list<formatters::facet> workflow::create_facets_activty(
    const std::unordered_map<std::string, formatters::container>&
    formatters_by_facet,
    const std::unordered_map<std::string, global_settings>&
    global_settings_for_facet) const {

    formatters::facet_factory f;
    return f.build(formatters_by_facet, global_settings_for_facet);
}

workflow::includes_builder_by_formatter_id
workflow::create_includes_builder_by_formatter_id_activity(
    const formatters::container& c) const {
    BOOST_LOG_SEV(lg, debug) << "Creating a map of includes builders by id.";
    workflow::includes_builder_by_formatter_id r;
    for (const auto f : c.class_formatters()) {
        auto b(f->make_includes_builder());
        const auto pair(r.insert(std::make_pair(f->formatter_id(), b)));
        if (!pair.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_id
                                     << f->formatter_id();
            BOOST_THROW_EXCEPTION(workflow_error(duplicate_formatter_id +
                    f->formatter_id()));
        }
    }

    BOOST_LOG_SEV(lg, debug)
        << "Finished creating a map of includes builders by id.";
    return r;
}

std::unordered_map<sml::qname, workflow::path_by_formatter_type>
workflow::obtain_relative_file_names_for_key_activity(
    const std::forward_list<formatters::facet>& facets,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining relative file names.";

    std::unordered_map<sml::qname, path_by_formatter_type> r;
    for (const auto& pair : m.objects()) {
        const auto qn(pair.first);
        const auto o(pair.second);

        const auto ng(sml::generation_types::no_generation);
        if (o.generation_type() == ng)
            continue;

        const auto ft(formatter_type_for_object_type(o.object_type()));
        switch(ft) {
        case formatters::formatter_types::class_formatter:
            for (const auto fct : facets) {
                for (const auto fmt : fct.container().class_formatters()) {
                    const auto& id(fmt->formatter_id());
                    const auto& gs(fct.global_settings());
                    const auto& fn(fmt->make_file_name(gs, qn));
                    r[qn].insert(std::make_pair(id, fn));
                }
            }
            break;

        case formatters::formatter_types::exception_formatter:
            // FIXME
            break;

        default: {
            const auto n(sml::string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << unsupported_formatter_type << ft
                                     << " name: " << n;
            BOOST_THROW_EXCEPTION(workflow_error(unsupported_formatter_type +
                    boost::lexical_cast<std::string>(ft)));
        } };
    }

    BOOST_LOG_SEV(lg, debug) << "Relative file names: " << r;
    BOOST_LOG_SEV(lg, debug) << "Finished obtaining relative file names.";
    return r;
}

std::unordered_map<sml::qname,
                   workflow::file_settings_by_formatter_type> workflow::
obtain_file_settings_activity(
    const includes_builder_by_formatter_id& includes_builders,
    const sml::model& m,
    const std::unordered_map<sml::qname, path_by_formatter_type>&
    relative_file_names_by_formatter_by_qname) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining file settings.";

    std::unordered_map<sml::qname,
                       workflow::file_settings_by_formatter_type> r;

    for (const auto pair : relative_file_names_by_formatter_by_qname) {
        const auto& qn(pair.first);
        workflow::file_settings_by_formatter_type fs;
        for (const auto other_pair : pair.second) {
            file_settings psd;
            psd.relative_path(other_pair.second);

            const auto& formatter_id(other_pair.first);
            const auto i(includes_builders.find(formatter_id));
            if (i == includes_builders.end()) {
                BOOST_LOG_SEV(lg, error) << formatter_not_found << formatter_id;
                BOOST_THROW_EXCEPTION(workflow_error(formatter_not_found +
                        formatter_id));
            }

            const auto& b(*(i->second));
            auto inc(b.build(m, qn, relative_file_names_by_formatter_by_qname));
            psd.includes(inc);
            fs[formatter_id] = psd;
        }
        r[qn] = fs;
    }

    BOOST_LOG_SEV(lg, debug) << "File settings names: " << r;
    BOOST_LOG_SEV(lg, debug) << "Finished obtaining file settings.";
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
    const auto glob(global_settings_for_facet_activty(gs, mod));

    const auto& c(registrar().formatter_container());
    const auto fc(formatter_container_for_facet_activty(c));
    const auto facets(create_facets_activty(fc, glob));
    const auto rel(obtain_relative_file_names_for_key_activity(facets, m));

    const auto builders(create_includes_builder_by_formatter_id_activity(c));
    const auto det(obtain_file_settings_activity(builders, m, rel));

    const formatters::workflow fw(facets);
    std::forward_list<dogen::formatters::file> r;
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(det, m, fw, m.modules()));
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(det, m, fw, m.concepts()));
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(det, m, fw, m.primitives()));
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(det, m, fw, m.enumerations()));
    r.splice_after(r.before_begin(),
        create_files_from_sml_container_activity(det, m, fw, m.objects()));

    BOOST_LOG_SEV(lg, debug) << "Finished C++ backend.";
    return r;
}

} }
