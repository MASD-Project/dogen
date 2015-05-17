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
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/comment_formatter.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/formatting_assistant.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.formatting_assistant"));

const std::string empty;
const std::string by_ref_text = "&";
const std::string void_keyword_text = "void";
const std::string final_keyword_text = "final ";
const std::string member_variable_postfix("_");

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool documenting_previous_identifier(true);

const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");
const std::string header_guard_not_set(
    "Header guard for formatter is not set. Formatter: ");
const std::string formatter_properties_missing(
    "Could not find formatter properties for formatter: ");

}

namespace dogen {
namespace cpp {
namespace formatters {

std::string formatting_assistant::
make_final_keyword_text(const formattables::class_info& c) {
    return c.is_final() ? final_keyword_text : empty;
}

std::string formatting_assistant::
make_by_ref_text(const formattables::property_info& p) {
    return p.type().is_primitive() ? empty : by_ref_text;
}

std::string formatting_assistant::
make_parameter_separator_text(const unsigned int number_of_parameters,
    const unsigned int parameter_position) {
    if (parameter_position == number_of_parameters - 1)
        return ");";
    if (parameter_position == 0 && number_of_parameters == 1)
        return empty;
    return ",";
}

std::string formatting_assistant::
make_setter_return_type(const std::string& containing_type_name,
    const formattables::property_info& p) {
    std::ostringstream s;
    if (p.is_fluent())
        s << containing_type_name << by_ref_text;
    else
        s << void_keyword_text;

    return s.str();
}

formatting_assistant::formatting_assistant(const formattables::entity& e,
    const dynamic::ownership_hierarchy& oh,
    const formatters::file_types ft) :
    entity_(e), ownership_hierarchy_(oh),
    formatter_properties_(obtain_formatter_properties(oh.formatter_name())),
    file_type_(ft) {

    dogen::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);
    validate();
}

formattables::formatter_properties formatting_assistant::
obtain_formatter_properties(const std::string& formatter_name) const {
    const auto& fn(formatter_name);
    const auto i(entity_.formatter_properties().find(fn));
    if (i == entity_.formatter_properties().end()) {
        BOOST_LOG_SEV(lg, error) << formatter_properties_missing << fn;
        BOOST_THROW_EXCEPTION(
            formatting_error(formatter_properties_missing + fn));
    }
    return i->second;
}

std::string formatting_assistant::make_member_variable_name(
    const formattables::property_info& p) const {
    return p.name() + member_variable_postfix;
}

bool formatting_assistant::
is_formatter_enabled(const std::string& formatter_name) const {
    const auto fp(obtain_formatter_properties(formatter_name));
    return fp.enabled();
}

bool formatting_assistant::
is_facet_integrated(const std::string& facet_name) const {
    const auto& f(formatter_properties_.integrated_facets());
    const auto i(f.find(facet_name));
    return i != f.end();
}

bool formatting_assistant::is_serialization_enabled() const {
    using formatters::serialization::traits;
    return is_formatter_enabled(traits::class_header_formatter_name());
}

bool formatting_assistant::is_io_enabled() const {
    using formatters::io::traits;
    return is_formatter_enabled(traits::class_header_formatter_name());
}

bool formatting_assistant::is_io_integrated() const {
    using formatters::io::traits;
    return is_facet_integrated(traits::facet_name());
}

bool formatting_assistant::is_complete_constructor_disabled() const {
    return entity_.settings().aspect_settings().disable_complete_constructor();
}

void formatting_assistant::validate() const {
    const auto& fn(ownership_hierarchy_.formatter_name());
    const auto& fp(formatter_properties_);
    if (fp.file_path().empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(file_path_not_set + fn));
    }

    if (file_type_ == file_types::cpp_header) {
        if (!fp.header_guard() || fp.header_guard()->empty()) {
            BOOST_LOG_SEV(lg, error) << header_guard_not_set << fn;
            BOOST_THROW_EXCEPTION(formatting_error(header_guard_not_set + fn));
        }
    }
}

dogen::formatters::cpp::scoped_boilerplate_formatter
formatting_assistant::make_scoped_boilerplate_formatter() {
    const auto& fp(formatter_properties_);
    const auto gs(entity_.settings().general_settings());
    return dogen::formatters::cpp::scoped_boilerplate_formatter(
        stream(), gs, fp.inclusion_dependencies(), *fp.header_guard());
}

dogen::formatters::cpp::scoped_namespace_formatter
formatting_assistant::make_scoped_namespace_formatter() {
    return dogen::formatters::cpp::scoped_namespace_formatter(
        stream(), entity_.namespaces(),
        false/*create_anonymous_namespace*/,
        true/*add_new_line*/);
}

std::ostream& formatting_assistant::stream() {
    return filtering_stream_;
}

dogen::formatters::file formatting_assistant::make_file() const {
    dogen::formatters::file r;
    r.content(stream_.str());
    r.path(formatter_properties_.file_path());
    return r;
}

void formatting_assistant::comment(const std::string& c) {
    if (c.empty())
        return;

    dogen::formatters::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::c_style,
        !last_line_is_blank);
    f.format(stream(), c);
}

void formatting_assistant::
comment_start_property(const formattables::property_info& p) {
    if (p.documentation().empty())
        return;

    {
        dogen::formatters::positive_indenter_scope pis(stream());
        dogen::formatters::comment_formatter f(
            !start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            dogen::formatters::comment_styles::c_style,
            !last_line_is_blank);

        f.format(stream(), p.documentation());
        if (!p.is_immutable()) {
            f.format_doxygen_start_block(stream(), p.documentation());
            stream() << std::endl;
        }
    }
}

void formatting_assistant::
comment_end_property(const formattables::property_info& p) {
    if (p.documentation().empty())
        return;

    {
        dogen::formatters::positive_indenter_scope pis(stream());
        dogen::formatters::comment_formatter f(
            start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            dogen::formatters::comment_styles::c_style,
            !last_line_is_blank);

        if (!p.is_immutable()) {
            f.format_doxygen_end_block(stream(), p.documentation());
            stream() << std::endl;
        }
    }
}

void formatting_assistant::comment_inline(const std::string& c) {
    if (c.empty())
        return;

    dogen::formatters::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        documenting_previous_identifier,
        dogen::formatters::comment_styles::cpp_style,
        !last_line_is_blank);

    f.format(stream(), c);
}

} } }
