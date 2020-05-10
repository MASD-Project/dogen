/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <ostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/io/formatters/comment_style_io.hpp"
#include "dogen.utility/types/formatters/formatting_error.hpp"
#include "dogen.utility/types/formatters/comment_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("utility.formatters.comment_formatter"));

const std::string empty;
const std::string xml_style_start("<!-- ");
const std::string xml_style_middle("   -");
const std::string xml_style_end("-->");
const std::string plain_c_style_start("/*");
const std::string c_style_middle(" *");
const std::string doxygen_c_style_start("/**");
const std::string c_style_end("*/");
const std::string plain_cpp_style("//");
const std::string doxygen_cpp_style("///");
const std::string doxygen_previous_identifier("<");
const std::string shell_style("#");
const std::string sql_style("--");
const std::string space(" ");
const std::string brief("@brief");
const std::string block_start("@{");
const std::string block_end("@}");

const std::string unsupported_style("Style is not supported: ");

}

namespace dogen::utility::formatters {

comment_formatter::comment_formatter()
    : start_on_first_line_(false),
      use_documentation_tool_markup_(false),
      documenting_previous_identifier_(false),
      style_(comment_style::c_style),
      last_line_is_blank_(false) { }

comment_formatter::comment_formatter(
    const bool start_on_first_line,
    const bool use_documentation_tool_markup,
    const bool documenting_previous_identifier,
    const comment_style style,
    const bool last_line_is_blank)
    : start_on_first_line_(start_on_first_line),
      use_documentation_tool_markup_(use_documentation_tool_markup),
      documenting_previous_identifier_(documenting_previous_identifier),
      style_(style),
      last_line_is_blank_(last_line_is_blank) {
    validate();
}

void comment_formatter::validate() const {
    bool is_syle_supported(
        style_ == comment_style::xml_style ||
        style_ == comment_style::c_style ||
        style_ == comment_style::shell_style ||
        style_ == comment_style::sql_style ||
        style_ == comment_style::csharp_style ||
        style_ == comment_style::cpp_style);

    if (!is_syle_supported) {
        const auto s(boost::lexical_cast<std::string>(style_));
        BOOST_LOG_SEV(lg, error) << unsupported_style << s;
        BOOST_THROW_EXCEPTION(formatting_error(unsupported_style + s));
    }
}

void comment_formatter::add_start_overview(std::ostream& s) const {
    if (style_ == comment_style::c_style ||
        style_ == comment_style::cpp_style)
        s << brief << space;
    else if (style_ == comment_style::csharp_style) {
        s << "<summary>" << std::endl;
        add_comment_middle_marker(s);
        s << space;
    }
}

void comment_formatter::
add_end_overview(std::ostream& s, bool add_new_line) const {
    if (style_ == comment_style::csharp_style) {
        if (add_new_line)
            add_comment_middle_marker(s);

        s  << space << "</summary>";
        if (add_new_line)
            s << std::endl;
    }
}

void comment_formatter::add_start_body(std::ostream& s) const {
    if (style_ == comment_style::csharp_style) {
        s << "<remarks>" << std::endl;
        add_comment_middle_marker(s);
        s << space;
    }
}

void comment_formatter::add_end_body(std::ostream& s) const {
    if (style_ == comment_style::csharp_style) {
        add_comment_middle_marker(s);
        s << space << "</remarks>" << std::endl;
    }
}

void comment_formatter::add_comment_start_marker(std::ostream& s) const {
    if (style_ == comment_style::xml_style) {
        s << xml_style_start;
        return;
    } else if (style_ != comment_style::c_style) {
        add_comment_middle_marker(s);
        return;
    }

    if (use_documentation_tool_markup_) {
        s << doxygen_c_style_start;
        if (documenting_previous_identifier_)
            s << doxygen_previous_identifier;
    } else
        s << plain_c_style_start;
}

void comment_formatter::add_comment_middle_marker(std::ostream& s) const {
    switch(style_) {
    case comment_style::xml_style:
        s << xml_style_middle;
        break;
    case comment_style::c_style:
        s << c_style_middle;
        break;
    case comment_style::cpp_style:
        if (use_documentation_tool_markup_) {
            s << doxygen_cpp_style;
            if (documenting_previous_identifier_)
                s << doxygen_previous_identifier;
        } else
            s << plain_cpp_style;
        break;
    case comment_style::shell_style:
        s << shell_style;
        break;
    case comment_style::sql_style:
        s << sql_style;
        break;
    case comment_style::csharp_style:
        if (use_documentation_tool_markup_) {
            s << doxygen_cpp_style;
        } else
            s << plain_cpp_style;
        break;
    default:
        const auto s(boost::lexical_cast<std::string>(style_));
        BOOST_LOG_SEV(lg, error) << unsupported_style << s;
        BOOST_THROW_EXCEPTION(formatting_error(unsupported_style + s));
    }
}

void comment_formatter::add_comment_end_marker(std::ostream& s) const {
    if (style_ == comment_style::xml_style) {
        s << xml_style_end << std::endl;
    } else if (style_ == comment_style::c_style)
        s << space << c_style_end << std::endl;
}

void comment_formatter::format_doxygen_block(std::ostream& s,
    const std::string& block, const std::string& content) const {
    if (!use_documentation_tool_markup_)
        return;

    std::string trimmed(boost::algorithm::trim_copy(content));
    if (trimmed.empty())
        return;

    if (style_ == comment_style::c_style)
        s << doxygen_c_style_start << block << c_style_end;
    else
        s << doxygen_cpp_style << block;
}

void comment_formatter::
format(std::ostream& s, const std::string& content) const {
    format(s, std::list<std::string> { content });
}

void comment_formatter::
format(std::ostream& s, const std::list<std::string>& content,
    const bool line_between_blocks) const {
    add_comment_start_marker(s);

    bool is_first_line(true);
    bool is_first_block(true);
    bool content_found(false);
    bool in_overview(true);
    bool in_body(false);
    bool needs_start_body(false);
    bool needs_end_body(false);
    bool needs_end_overview(false);
    for (const auto& c : content) {
        content_found = content_found || !c.empty();

        if (!is_first_block && line_between_blocks) {
            add_comment_middle_marker(s);
            s << std::endl;
        }

        std::string line;
        std::istringstream content_stream(c);
        while (std::getline(content_stream, line)) {
            boost::algorithm::trim_right(line);
            if (is_first_line) {
                if (!start_on_first_line_) {
                    s << std::endl;
                    add_comment_middle_marker(s);
                }
            } else
                add_comment_middle_marker(s);

            if (!line.empty()) {
                s << space;
                if (is_first_line && is_first_block &&
                    use_documentation_tool_markup_ &&
                    !documenting_previous_identifier_) {
                    add_start_overview(s);
                    needs_end_overview = true;
                } else if (in_body && needs_start_body) {
                    add_start_body(s);
                    needs_start_body = false;
                    needs_end_body = true;
                }
                s << line;
            } else if (!is_first_line && use_documentation_tool_markup_ &&
                in_overview) {
                add_end_overview(s);
                needs_end_overview = false;
                in_overview = false;
                in_body = true;
                needs_start_body = true;
            }

            // FIXME: massive hack: we assume that documenting
            // previous identifier actually means documenting
            // identifier inline - that is, it always has just one
            // line.
            if (!documenting_previous_identifier_)
                s << std::endl;

            is_first_line = false;
        }
        is_first_block = false;
    }

    if (needs_end_overview)
        add_end_overview(s, true);
    else if (needs_end_body)
        add_end_body(s);

    if (!content_found) {
        s << std::endl;

        add_comment_middle_marker(s);
        s << std::endl;
    }

    if (last_line_is_blank_) {
        add_comment_middle_marker(s);
        s << std::endl;
    }
    add_comment_end_marker(s);
}

void comment_formatter::format_doxygen_start_block(std::ostream& s,
    const std::string& content) const {
    format_doxygen_block(s, block_start, content);
}

void comment_formatter::format_doxygen_end_block(std::ostream& s,
    const std::string& content) const {
    format_doxygen_block(s, block_end, content);
}

}
