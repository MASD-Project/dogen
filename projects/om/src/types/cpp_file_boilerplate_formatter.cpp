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
#include <ostream>
#include "dogen/om/types/modeline_formatter.hpp"
#include "dogen/om/types/comment_formatter.hpp"
#include "dogen/om/types/cpp_file_boilerplate_formatter.hpp"

namespace {

const std::string blank_line;
const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);

}

namespace dogen {
namespace om {

void cpp_file_boilerplate_formatter::
add_modeline(std::list<std::string>& content, const modeline& m) const {
    std::ostringstream s;
    modeline_formatter f;
    f.format(s, m);
    content.push_back(s.str());
}

void cpp_file_boilerplate_formatter::add_marker(std::list<std::string>& content,
    const std::string& marker) const {
    if (marker.empty())
        return;

    content.push_back(blank_line);
    content.push_back(marker);
}

void cpp_file_boilerplate_formatter::
add_licence(std::list<std::string>& content, const licence& l) const {
    const auto ch(l.copyright_holders());
    if (!ch.empty()) {
        content.push_back(blank_line);
        content.insert(content.end(), ch.begin(), ch.end());
    }

    if (!l.text().empty()) {
        content.push_back(blank_line);
        content.push_back(l.text());
    }
}

void cpp_file_boilerplate_formatter::
format_begin(std::ostream& s, const licence& l, const modeline& m,
    const std::string& marker, const cpp_includes& /*i*/,
    const boost::filesystem::path /*relative_file_name*/) const {

    comment_formatter cf(
        start_on_first_line,
        !use_documentation_tool_markup,
        !documenting_previous_identifier,
        comment_styles::c_style,
        last_line_is_blank);

    std::list<std::string> content;
    if (m.location() == modeline_locations::top)
        add_modeline(content, m);

    add_marker(content, marker);
    add_licence(content, l);

    cf.format(s, content);
}

void cpp_file_boilerplate_formatter::
format_end(std::ostream& /*s*/, const modeline& /*m*/) const {
}

} }
