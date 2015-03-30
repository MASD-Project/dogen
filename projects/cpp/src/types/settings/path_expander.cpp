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
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/dynamic/expansion/types/options_copier.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"
#include "dogen/cpp/io/formatters/file_types_io.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/settings/path_settings_factory.hpp"
#include "dogen/cpp/types/settings/path_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.path_expander"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");
const std::string unsupported_file_type("File type not supported: ");

const std::string expander_not_setup(
    "Attempt to expand without setting up expander");
const std::string no_fields_for_formatter(
    "Could not find any fields for formatter: ");
const std::string field_definition_not_found(
    "Could not find expected field definition: ");
const std::string missing_path_settings(
    "Could not find any path settings for formatter: ");
const std::string model_module_not_found("Model module not found for model: ");

}

namespace dogen {
namespace cpp {
namespace settings {

std::string path_expander::static_name() {
    static std::string name("cpp.path_expander");
    return name;
}

path_expander::path_expander() : requires_file_path_expansion_(false) { }
path_expander::~path_expander() noexcept { }

void path_expander::setup_formatter_fields(
    const dynamic::schema::repository& rp,
    const std::string& formatter_name,
    formatter_properties& fp) const {

    const auto i(rp.field_definitions_by_formatter_name().find(formatter_name));
    if (i == rp.field_definitions_by_formatter_name().end()) {
        BOOST_LOG_SEV(lg, error) << no_fields_for_formatter << formatter_name;
        BOOST_THROW_EXCEPTION(dynamic::expansion::expansion_error(
                no_fields_for_formatter + formatter_name));
    }

    bool found_file_path(false), found_inclusion_path(false),
        found_header_guard(false);

    for (const auto fd : i->second) {
        if (fd.name().simple() == traits::file_path()) {
            fp.file_path = fd;
            found_file_path = true;
        } else if (fd.name().simple() == traits::inclusion_directive()) {
            fp.inclusion_directive = fd;
            found_inclusion_path = true;
        } else if (fd.name().simple() == traits::header_guard()) {
            fp.header_guard = fd;
            found_header_guard = true;
        }
    }

    if (!found_file_path) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found
                                 << traits::file_path() << " for formatter: "
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(
            dynamic::expansion::expansion_error(
                field_definition_not_found + traits::file_path()));
    }

    if (!found_inclusion_path) {
        BOOST_LOG_SEV(lg, debug) << "Formatter does not support inclusion: "
                                 << formatter_name;
    }

    if (!found_header_guard) {
        BOOST_LOG_SEV(lg, debug) << "Formatter does not support header guards: "
                                 << formatter_name;
    }
}

path_expander::formatter_properties
path_expander::make_formatter_properties(
    const dynamic::schema::repository& rp,
    const std::string& formatter_name,
    const std::unordered_map<std::string, path_settings>& ps) const {

    const auto i(ps.find(formatter_name));
    if (i == ps.end()) {
        BOOST_LOG_SEV(lg, error) << missing_path_settings << formatter_name;

        using dynamic::expansion::expansion_error;
        BOOST_THROW_EXCEPTION(
            expansion_error(missing_path_settings + formatter_name));
    }

    formatter_properties r;
    r.settings = i->second;
    r.formatter_name = formatter_name;
    setup_formatter_fields(rp, formatter_name, r);

    return r;
}

std::unordered_map<std::string, path_expander::formatter_properties>
path_expander::make_formatter_properties(const dynamic::schema::repository& rp,
    const dynamic::schema::object& root) const {
    const auto& c(formatters::workflow::registrar().formatter_container());
    std::unordered_map<std::string, formatter_properties> r;

    const auto ps(factory_->make(root));
    for (const auto& f : c.all_formatters()) {
        const auto oh(f->ownership_hierarchy());
        const auto& fn(oh.formatter_name());
        r[fn] = make_formatter_properties(rp, fn, ps);
    }
    return r;
}

void path_expander::ensure_is_setup() const {
    if (factory_)
        return;

    BOOST_LOG_SEV(lg, error) << expander_not_setup;
    using dynamic::expansion::expansion_error;
    BOOST_THROW_EXCEPTION(expansion_error(expander_not_setup));
}

dynamic::schema::object path_expander::
obtain_root_object(const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining model's root object.";

    const auto i(m.modules().find(m.name()));
    if (i == m.modules().end()) {
        const auto n(sml::string_converter::convert(m.name()));
        BOOST_LOG_SEV(lg, error) << model_module_not_found << n;

        using dynamic::expansion::expansion_error;
        BOOST_THROW_EXCEPTION(expansion_error(model_module_not_found + n));
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained model's root object.";
    return i->second.extensions();
}

boost::filesystem::path path_expander::
make_inclusion_path(const path_settings& ps, const sml::qname& qn) const {
    BOOST_LOG_SEV(lg, debug) << "Creating inclusion path for: "
                             << sml::string_converter::convert(qn);

    boost::filesystem::path r;

    if (ps.split_project()) {
        for(auto n : qn.external_module_path())
            r /= n;

        r /= qn.model_name();
    } else if (ps.file_type() == formatters::file_types::cpp_header) {
        for(auto n : qn.external_module_path())
            r /= n;
        r /= qn.model_name();
    }

    if (!ps.facet_directory().empty())
        r /= ps.facet_directory();

    for(auto n : qn.module_path())
        r /= n;

    std::ostringstream stream;
    stream << qn.simple_name();

    if (!ps.formatter_postfix().empty())
        stream << underscore << ps.formatter_postfix();

    if (!ps.facet_postfix().empty())
        stream << underscore << ps.facet_postfix();

    stream << dot << ps.extension();
    r /= stream.str();

    BOOST_LOG_SEV(lg, debug) << "Done creating inclusion path. Result: " << r;
    return r;
}

boost::filesystem::path path_expander::
make_file_path(const path_settings& ps,
    const boost::filesystem::path& inclusion_path,
    const sml::qname& qn) const {
    BOOST_LOG_SEV(lg, debug) << "Creating file path for: "
                             << sml::string_converter::convert(qn);

    boost::filesystem::path r;

    const auto ft(ps.file_type());
    switch (ft) {
    case formatters::file_types::cpp_header:
        if (ps.split_project())
            r = ps.include_directory_path();
        else {
            r = ps.project_directory_path() / qn.model_name();
            r /= ps.include_directory_name();
        }
        break;

    case formatters::file_types::cpp_implementation:
        if (ps.split_project())
            r = ps.source_directory_path();
        else {
            r = ps.project_directory_path() / qn.model_name();
            r /= ps.source_directory_name();
        }
        break;

    default:
        BOOST_LOG_SEV(lg, error) << unsupported_file_type << ft;

        using dynamic::expansion::expansion_error;
        BOOST_THROW_EXCEPTION(expansion_error(unsupported_file_type +
                boost::lexical_cast<std::string>(ft)));
    }

    r /= inclusion_path;

    BOOST_LOG_SEV(lg, debug) << "Done creating file path. Result: " << r;
    return r;
}

std::string path_expander::
to_inclusion_directive(const boost::filesystem::path& p) const {
    std::ostringstream ss;
    ss << double_quote << p.generic_string() << double_quote;
    return ss.str();

}

std::string path_expander::
to_header_guard_name(const boost::filesystem::path& p) const {
    bool is_first(true);
    std::ostringstream ss;
    for (const auto& token : p) {
        std::string s(token.string());
        boost::replace_all(s, dot, separator);
        boost::to_upper(s);
        ss << (is_first ? empty : separator) << s;
        is_first = false;
    }
    return ss.str();
}

void path_expander::expand_file_path(const formatter_properties& fp,
    const boost::filesystem::path& file_path,
    dynamic::schema::object& o) const {

    if (!requires_file_path_expansion_)
        return;

    dynamic::schema::field_instance_factory f;
    o.fields()[fp.file_path.name().qualified()] = f.make_text(file_path);
}

void path_expander::expand_header_guard(const formatter_properties& fp,
    const boost::filesystem::path& inclusion_path,
    dynamic::schema::object& o) const {

    const bool header_guard_not_supported(!fp.header_guard);
    if (header_guard_not_supported)
        return;

    using namespace dynamic::schema;
    const field_selector fs(o);
    const bool override_found(fs.has_field(*fp.header_guard));
    if (override_found) {
        BOOST_LOG_SEV(lg, debug) << "Header guard has been overriden: "
                                 << fp.formatter_name;
        return;
    }

    dynamic::schema::field_instance_factory f;
    const auto n(fp.header_guard->name().qualified());
    o.fields()[n] = f.make_text(to_header_guard_name(inclusion_path));
}

void path_expander::expand_include_directive(const formatter_properties& fp,
    const boost::filesystem::path& inclusion_path,
    dynamic::schema::object& o) const {

    const bool inclusion_directive_not_supported(!fp.inclusion_directive);
    if (inclusion_directive_not_supported)
        return;

    using namespace dynamic::schema;
    const field_selector fs(o);
    const bool override_found(fs.has_field(*fp.inclusion_directive));
    if (override_found) {
        BOOST_LOG_SEV(lg, debug) << "Include directive has been overriden: "
                                 << fp.formatter_name;
        return;
    }

    dynamic::schema::field_instance_factory f;
    const auto n(fp.inclusion_directive->name().qualified());
    o.fields()[n] = f.make_text(to_inclusion_directive(inclusion_path));
}

std::string path_expander::name() const {
    return static_name();
}

const std::forward_list<std::string>& path_expander::dependencies() const {
    using namespace dynamic::expansion;
    static std::forward_list<std::string> r { options_copier::static_name() };

    return r;
}

void path_expander::setup(const dynamic::expansion::expansion_context& ec) {
    requires_file_path_expansion_ = ec.model().is_target();
    factory_ = std::make_shared<path_settings_factory>(
        ec.cpp_options(), ec.repository());
    const auto root(obtain_root_object(ec.model()));
    formatter_properties_ = make_formatter_properties(ec.repository(), root);
}

void path_expander::expand(const sml::qname& qn,
    const dynamic::schema::scope_types& /*st*/,
    dynamic::schema::object& o) const {

    ensure_is_setup();
    for (const auto& pair : formatter_properties_) {
        const auto& fp(pair.second);
        const auto inclusion_path(make_inclusion_path(fp.settings, qn));
        const auto file_path(make_file_path(fp.settings, inclusion_path, qn));

        expand_file_path(fp, file_path, o);
        expand_header_guard(fp, inclusion_path, o);
        expand_include_directive(fp, inclusion_path, o);
    }
}

} } }
