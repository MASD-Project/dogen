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
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/settings/selector.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/formatting_assistant.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.formatting_assistant"));

const std::string empty;
const std::string by_ref_text = "&";
const std::string final_keyword_text = "final ";

const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");
const std::string header_guard_not_set(
    "Header guard for formatter is not set. Formatter: ");

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

formatting_assistant::formatting_assistant(const formattables::entity& e,
    const dynamic::schema::ownership_hierarchy& oh,
    const formatters::file_types ft) :
    entity_(e), ownership_hierarchy_(oh),
    formatter_settings_(formatter_settings()), file_type_(ft) {

    dogen::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);
    validate();
}

settings::formatter_settings formatting_assistant::formatter_settings() const {
    const settings::selector s(entity_.settings());
    const auto& fn(ownership_hierarchy_.formatter_name());
    return s.formatter_settings_for_formatter(fn);
}

void formatting_assistant::validate() const {
    const auto& fn(ownership_hierarchy_.formatter_name());
    const auto& fs(formatter_settings_);
    if (fs.file_path().empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(file_path_not_set + fn));
    }

    if (file_type_ == file_types::cpp_header) {
        if (!fs.header_guard() || fs.header_guard()->empty()) {
            BOOST_LOG_SEV(lg, error) << header_guard_not_set << fn;
            BOOST_THROW_EXCEPTION(formatting_error(header_guard_not_set + fn));
        }
    }
}

dogen::formatters::cpp::scoped_boilerplate_formatter
formatting_assistant::make_scoped_boilerplate_formatter() {
    const auto& fs(formatter_settings_);
    const auto gs(entity_.settings().general_settings());
    return dogen::formatters::cpp::scoped_boilerplate_formatter(
        filtering_stream_, gs, fs.inclusion_dependencies(), *fs.header_guard());
}

dogen::formatters::cpp::scoped_namespace_formatter
formatting_assistant::make_scoped_namespace_formatter() {
    return dogen::formatters::cpp::scoped_namespace_formatter(
        filtering_stream_, entity_.namespaces(),
        false/*create_anonymous_namespace*/,
        true/*add_new_line*/);
}

std::ostream& formatting_assistant::stream() {
    return filtering_stream_;
}

dogen::formatters::file formatting_assistant::make_file() const {
    dogen::formatters::file r;
    r.content(stream_.str());
    r.path(formatter_settings_.file_path());
    return r;
}

} } }
