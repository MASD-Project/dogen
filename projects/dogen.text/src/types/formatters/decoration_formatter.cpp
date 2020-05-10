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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.logical/io/entities/decoration/modeline_io.hpp"
#include "dogen.utility/io/formatters/comment_style_io.hpp"
#include "dogen.utility/types/formatters/comment_formatter.hpp"
#include "dogen.text/types/formatters/modeline_formatter.hpp"
#include "dogen.text/types/formatters/generation_marker_formatter.hpp"
#include "dogen.text/types/formatters/decoration_formatter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("text.decoration_formatter"));

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);

const std::string xml_declaration("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");

}

namespace dogen::text::formatters {

void decoration_formatter::
add_modeline(std::list<std::string>& content,
    const boost::shared_ptr<logical::entities::decoration::modeline> ml
    ) const {
    if (!ml) {
        BOOST_LOG_SEV(lg, trace) << "Modeline is empty.";
        return;
    }

    std::ostringstream s;
    modeline_formatter f;
    f.format(s, *ml);
    content.push_back(s.str());
}

void decoration_formatter::
add_marker(std::list<std::string>& content,
    const std::string& generation_timestamp,
    const std::string& origin_shah1_hash, const boost::shared_ptr<
    logical::entities::decoration::generation_marker> gm) const {
    if (!gm) {
        BOOST_LOG_SEV(lg, trace) << "Generation marker is empty.";
        return;
    }

    std::ostringstream s;
    generation_marker_formatter f;
    f.format(s, generation_timestamp, origin_shah1_hash, *gm);
    content.push_back(s.str());
}

void decoration_formatter::
add_copyright_notices(std::list<std::string>& content,
    std::list<std::string> copyright_notices) const {
    BOOST_LOG_SEV(lg, trace) << "Copyriht notices: " << copyright_notices;

    if (copyright_notices.empty())
        return;

    std::ostringstream s;
    for (const auto& cn : copyright_notices)
        s << cn << std::endl;

    content.push_back(s.str());
}

void decoration_formatter::add_licence(std::list<std::string>& content,
    const std::string& licence) const {
    if (!licence.empty())
        content.push_back(licence);
}

void decoration_formatter::format_preamble(
    std::ostream& s, const utility::formatters::comment_style& single_line_cs,
    const utility::formatters::comment_style& multi_line_cs, const std::string& licence_text,
    const std::list<std::string>& copyright_notices,
    const std::string& generation_timestamp,
    const std::string& origin_shah1_hash,
    const boost::shared_ptr<logical::entities::decoration::modeline> ml,
    const boost::shared_ptr<
    logical::entities::decoration::generation_marker> gm) const {

    if (single_line_cs == utility::formatters::comment_style::xml_style) {
        /*
         * If we're in XML, add the XML declaration.
         */
        s << xml_declaration << std::endl;
    }

    const auto top(logical::entities::decoration::modeline_location::top);
    const bool has_modeline((bool)ml);
    const bool is_top(has_modeline && ml->location() == top);
    std::list<std::string> content;
    if (is_top)
        add_modeline(content, ml);

    add_marker(content, generation_timestamp, origin_shah1_hash, gm);
    add_copyright_notices(content, copyright_notices);
    add_licence(content, licence_text);

    if (content.empty())
        return;

    if (has_modeline && is_top && content.size() == 1) {
        utility::formatters::comment_formatter cf(
            start_on_first_line,
            !use_documentation_tool_markup,
            !documenting_previous_identifier,
            single_line_cs,
            !last_line_is_blank);

        cf.format(s, content, !line_between_blocks);
    } else {
        utility::formatters::comment_formatter cf(
            is_top ? start_on_first_line : !start_on_first_line,
            !use_documentation_tool_markup,
            !documenting_previous_identifier,
            multi_line_cs,
            last_line_is_blank);

        cf.format(s, content, line_between_blocks);
    }
}

void decoration_formatter::
format_preamble(std::ostream& s, const utility::formatters::comment_style& cs,
    const std::string& licence_text,
    const std::list<std::string>& copyright_notices,
    const std::string& generation_timestamp,
    const std::string& origin_shah1_hash,
    const boost::shared_ptr<logical::entities::decoration::modeline> ml,
    const boost::shared_ptr<
    logical::entities::decoration::generation_marker> gm) const {

    BOOST_LOG_SEV(lg, trace) << "Comment style: " << cs;
    format_preamble(s, cs, cs, licence_text, copyright_notices,
        generation_timestamp, origin_shah1_hash, ml, gm);
}

void decoration_formatter::
format_postamble(std::ostream& s, const utility::formatters::comment_style& cs,
    const boost::shared_ptr<logical::entities::decoration::modeline> ml) const {

    if (!ml) {
        BOOST_LOG_SEV(lg, trace) << "Modeline is empty.";
        return;
    }

    using logical::entities::decoration::modeline_location;
    if (ml->location() == modeline_location::bottom) {
        std::list<std::string> content;
        add_modeline(content, ml);

        utility::formatters::comment_formatter cf(
            !start_on_first_line,
            !use_documentation_tool_markup,
            !documenting_previous_identifier,
            cs,
            !last_line_is_blank);

        cf.format(s, content);
    }
}

}
