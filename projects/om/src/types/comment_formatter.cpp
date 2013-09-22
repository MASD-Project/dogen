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
#include <ostream>
#include <sstream>
#include "dogen/om/types/comment_formatter.hpp"

namespace {

const std::string empty;
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

}

namespace dogen {
namespace om {

comment_formatter::comment_formatter()
    : start_on_first_line_(false),
      use_documentation_tool_markup_(false),
      documenting_previous_identifier_(false),
      style_(comment_styles::c_style),
      last_line_is_blank_(false) { }

comment_formatter::comment_formatter(
    const bool start_on_first_line,
    const bool use_documentation_tool_markup,
    const bool documenting_previous_identifier,
    const comment_styles style,
    const bool last_line_is_blank)
    : start_on_first_line_(start_on_first_line),
      use_documentation_tool_markup_(use_documentation_tool_markup),
      documenting_previous_identifier_(documenting_previous_identifier),
      style_(style),
      last_line_is_blank_(last_line_is_blank) { }

void comment_formatter::add_comment_start_marker(std::ostream& s) const {
    if (style_ == comment_styles::c_style) {
        if (use_documentation_tool_markup_) {
            s << doxygen_c_style_start;
            if (documenting_previous_identifier_)
                s << doxygen_previous_identifier;
        } else
            s << plain_c_style_start;
    } else
        add_comment_middle_marker(s);
}

void comment_formatter::add_comment_middle_marker(std::ostream& s) const {
    if (style_ == comment_styles::c_style)
        s << c_style_middle;
    else if (style_ == comment_styles::cpp_style) {
        if (use_documentation_tool_markup_) {
            s << doxygen_cpp_style;
            if (documenting_previous_identifier_)
                s << doxygen_previous_identifier;
        }
        else
            s << plain_cpp_style;
    } else if (style_ == comment_styles::shell_style) {
        s << shell_style;
    } else if (style_ == comment_styles::sql_style) {
        s << sql_style;
    }
}

void comment_formatter::add_comment_end_marker(std::ostream& s) const {
    if (style_ == comment_styles::c_style)
        s << space << c_style_end << std::endl;
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
    for (const auto& c : content) {
        content_found = content_found || !c.empty();

        if (!is_first_block && line_between_blocks) {
            add_comment_middle_marker(s);
            s << std::endl;
        }

        std::istringstream content_stream(c);
        std::string line;
        while (std::getline(content_stream, line)) {
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
                    !documenting_previous_identifier_)
                    s << brief << space;
                s << line;
            }

            s << std::endl;
            is_first_line = false;
        }
            is_first_block = false;
    }

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

} }
