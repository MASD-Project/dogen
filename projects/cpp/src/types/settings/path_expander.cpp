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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/dynamic/expansion/types/options_copier.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/dynamic/expansion/types/root_object_copier.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"
#include "dogen/cpp/io/formatters/file_types_io.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/settings/path_settings_factory.hpp"
#include "dogen/cpp/types/settings/path_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.path_expander"));

const std::string underscore("_");
const std::string dot(".");
const std::string unsupported_file_type("File type not supported: ");

const std::string expander_not_setup(
    "Attempt to expand without setting up expander");
const std::string no_fields_for_formatter(
    "Could not find any fields for formatter: ");
const std::string field_definition_not_found(
    "Could not find expected field definition: ");
const std::string no_path_settings_for_formatter(
    "Could not find any path settings for formatter: ");

}

namespace dogen {
namespace cpp {
namespace settings {

std::string path_expander::static_name() {
    static std::string name("cpp.path_expander");
    return name;
}

path_expander::path_expander() { }
path_expander::~path_expander() noexcept { }

void path_expander::setup_formatter_fields(
    const dynamic::schema::repository& rp,
    const std::string& formatter_name,
    formatter_properties& fp) const {

    const auto i(rp.field_definitions_by_formatter_name().find(formatter_name));
    if (i == rp.field_definitions_by_facet_name().end()) {
        BOOST_LOG_SEV(lg, error) << no_fields_for_formatter << formatter_name;
        BOOST_THROW_EXCEPTION(dynamic::expansion::expansion_error(
                no_fields_for_formatter + formatter_name));
    }

    bool found_file_path(false);

    for (const auto fd : i->second) {
        if (fd.name().simple() == traits::file_path()) {
            fp.file_path = fd;
            found_file_path = true;
        } else if (fd.name().simple() == traits::inclusion_path())
            fp.inclusion_path = fd;
    }

    if (!found_file_path) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found
                                 << traits::file_path() << " for formatter: "
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(
            dynamic::expansion::expansion_error(
                field_definition_not_found + traits::file_path()));
    }
}

path_expander::formatter_properties
path_expander::make_formatter_properties(
    const dynamic::schema::repository& rp,
    const formatters::formatter_interface& f) const {

    formatter_properties r;
    r.formatter_name = f.formatter_name();
    setup_formatter_fields(rp, f.formatter_name(), r);

    return r;
}

std::unordered_map<std::string, path_expander::formatter_properties>
path_expander::make_formatter_properties(
    const dynamic::schema::repository& rp) const {
    const auto& c(formatters::workflow::registrar().formatter_container());
    std::unordered_map<std::string, formatter_properties> r;

    for (const auto& f : c.all_formatters()) {
        // formatter names are known to be unique
        r[f->formatter_name()] = make_formatter_properties(rp, *f);
    }
    return r;
}

void path_expander::ensure_is_setup() const {
    if (!factory_) {
        BOOST_LOG_SEV(lg, error) << expander_not_setup;

        using dynamic::expansion::expansion_error;
        BOOST_THROW_EXCEPTION(expansion_error(expander_not_setup));
    }
}

boost::filesystem::path path_expander::
make_file_path(const global_path_settings& gps, const sml::qname& qn) const {
    BOOST_LOG_SEV(lg, debug) << "Creating file path for: "
                             << sml::string_converter::convert(qn);

    boost::filesystem::path r;

    const auto ft(gps.file_type());
    switch (ft) {
    case formatters::file_types::cpp_header:
        if (gps.split_project())
            r = gps.include_directory_path();
        else {
            r = gps.project_directory_path() / qn.model_name();
            r /= gps.include_directory_name();
        }
        break;

    case formatters::file_types::cpp_implementation:
        if (gps.split_project())
            r = gps.source_directory_path();
        else {
            r = gps.project_directory_path() / qn.model_name();
            r /= gps.source_directory_name();
        }
        break;

    default:
        BOOST_LOG_SEV(lg, error) << unsupported_file_type << ft;

        using dynamic::expansion::expansion_error;
        BOOST_THROW_EXCEPTION(expansion_error(unsupported_file_type +
                boost::lexical_cast<std::string>(ft)));
    }

    r /= make_inclusion_path(gps, qn);

    BOOST_LOG_SEV(lg, debug) << "File path: " << r;
    BOOST_LOG_SEV(lg, debug) << "Done creating file path for: "
                             << sml::string_converter::convert(qn);
    return r;
}

boost::filesystem::path path_expander::
make_inclusion_path(const global_path_settings& gps,
    const sml::qname& qn) const {
    BOOST_LOG_SEV(lg, debug) << "Creating inclusion path for: "
                             << sml::string_converter::convert(qn);

    boost::filesystem::path r;

    if (gps.split_project()) {
        for(auto n : qn.external_module_path())
            r /= n;

        r /= qn.model_name();
    } else if (gps.file_type() == formatters::file_types::cpp_header) {
        for(auto n : qn.external_module_path())
            r /= n;
        r /= qn.model_name();
    }

    if (!gps.facet_directory().empty())
        r /= gps.facet_directory();

    for(auto n : qn.module_path())
        r /= n;

    std::ostringstream stream;
    stream << qn.simple_name();

    if (!gps.formatter_postfix().empty())
        stream << underscore << gps.formatter_postfix();

    if (!gps.facet_postfix().empty())
        stream << underscore << gps.facet_postfix();

    stream << dot << gps.extension();
    r /= stream.str();

    BOOST_LOG_SEV(lg, debug) << "Inclusion path: " << r;
    BOOST_LOG_SEV(lg, debug) << "Done creating inclusion path for: "
                             << sml::string_converter::convert(qn);

    return r;
}

std::string path_expander::name() const {
    return static_name();
}

const std::forward_list<std::string>& path_expander::dependencies() const {
    using namespace dynamic::expansion;
    static std::forward_list<std::string> r {
        options_copier::static_name(),
        root_object_copier::static_name(),
    };

    return r;
}

void path_expander::setup(const dynamic::expansion::expansion_context& ec) {
    formatter_properties_ = make_formatter_properties(ec.repository());
    factory_ = std::make_shared<path_settings_factory>(
        ec.cpp_options(),
        ec.repository());
}

void path_expander::expand(const sml::qname& /*qn*/,
    const dynamic::schema::scope_types& /*st*/,
    dynamic::schema::object& /*o*/) const {

    ensure_is_setup();
    // const auto lps(factory_->make_local_settings(o));
    // global_path_settings gps;
    // for (const auto& pair : formatter_properties_) {
    //     const auto& fp(pair.second);
    //     const auto i(lps.find(fp.formatter_name));
    //     if (i == lps.end()) {
    //         BOOST_LOG_SEV(lg, error) << no_path_settings_for_formatter
    //                                  << fp.formatter_name;
    //         BOOST_THROW_EXCEPTION(dynamic::expansion::expansion_error(
    //                 no_path_settings_for_formatter + fp.formatter_name));
    //     }


    //     dynamic::schema::field_instance_factory f;
    //     const auto file_path(make_file_path(gps, qn));
    //     o.fields()[fp.file_path.name().qualified()] = f.make_text(file_path);

    //     if (fp.inclusion_path) {
    //         // FIXME missing delimiter
    //         // FIXME path override
    //         const auto inclusion_path(make_inclusion_path(gps, i->second, qn));
    //         o.fields()[fp.inclusion_path->name().qualified()] =
    //             f.make_text(inclusion_path);
    //     }
    // }
}

} } }
