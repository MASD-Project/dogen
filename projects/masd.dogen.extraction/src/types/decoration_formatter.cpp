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
#include <sstream>
#include <ostream>
#include "masd.dogen.extraction/types/comment_formatter.hpp"
#include "masd.dogen.extraction/types/modeline_formatter.hpp"
#include "masd.dogen.extraction/types/decoration_formatter.hpp"

namespace {

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);

}

namespace masd::dogen::extraction {

void decoration_formatter::
add_modeline(std::list<std::string>& content, const modeline& m) const {
    std::ostringstream s;
    modeline_formatter f;
    f.format(s, m);
    content.push_back(s.str());
}

void decoration_formatter::
add_marker(std::list<std::string>& content,
    const std::string& marker) const {
    if (marker.empty())
        return;

    content.push_back(marker);
}

void decoration_formatter::
add_licence(std::list<std::string>& content, const licence& l) const {
    std::ostringstream s;
    for (const auto h : l.copyright_notices())
        s << h << std::endl;

    const auto notices(s.str());
    if (!notices.empty())
        content.push_back(notices);

    if (!l.text().empty())
        content.push_back(l.text());
}

void decoration_formatter::format_preamble(
    std::ostream& s, const comment_styles& single_line_cs,
    const comment_styles& multi_line_cs,
    const decoration_properties& dc) const {

    if (single_line_cs == comment_styles::xml_style) {
        /*
         * If we're in XML, add the XML declaration.
         */
        s << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    }

    bool is_top(false);
    const auto top(modeline_locations::top);
    bool has_modeline(dc.modeline());
    std::list<std::string> content;
    if (has_modeline) {
        is_top = dc.modeline()->location() == top;

        if (is_top)
            add_modeline(content, *dc.modeline());
    }

    add_marker(content, dc.code_generation_marker());
    if (dc.licence())
        add_licence(content, *dc.licence());

    if (content.empty())
        return;

    if (has_modeline && is_top && content.size() == 1) {
        comment_formatter cf(
            start_on_first_line,
            !use_documentation_tool_markup,
            !documenting_previous_identifier,
            single_line_cs,
            !last_line_is_blank);

        cf.format(s, content, !line_between_blocks);
    } else {
        comment_formatter cf(
            is_top ? start_on_first_line : !start_on_first_line,
            !use_documentation_tool_markup,
            !documenting_previous_identifier,
            multi_line_cs,
            last_line_is_blank);

        cf.format(s, content, line_between_blocks);
    }
}

void decoration_formatter::
format_preamble(std::ostream& s, const comment_styles& cs,
    const decoration_properties& dc) const {
    format_preamble(s, cs, cs, dc);
}

void decoration_formatter::format_postamble(std::ostream& s,
    const comment_styles& cs, const decoration_properties& dc) const {
    if (!dc.modeline())
        return;

    const auto m(*dc.modeline());
    if (m.location() == modeline_locations::bottom) {
        std::list<std::string> content;
        add_modeline(content, m);

        comment_formatter cf(
            !start_on_first_line,
            !use_documentation_tool_markup,
            !documenting_previous_identifier,
            cs,
            !last_line_is_blank);

        cf.format(s, content);
    }
}

}
