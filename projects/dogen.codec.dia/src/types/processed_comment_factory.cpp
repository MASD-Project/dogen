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
#include <string_view>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.codec.dia/types/building_error.hpp"
#include "dogen.codec.dia/types/processed_comment_factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("codec.dia.processed_comment_factory"));

constexpr std::string_view empty;
constexpr std::string_view instruction_marker("#DOGEN ");
constexpr std::string_view equals("=");
const std::string dia_comment("masd.codec.dia.comment");

const std::string separator_not_found("Expected separator on KVP.");

}

namespace dogen::codec::dia {

entities::comment processed_comment_factory::make(const std::string& c) {
    entities::comment r;

    if (c.empty())
        return r;

    r.original_content(c);
    std::string line;
    bool previous_line_blank(false);
    bool applicable_to_parent_object(false);
    std::istringstream comments_stream(c);
    std::ostringstream documentation_stream;

    while (std::getline(comments_stream, line)) {
        /*
         * Lines starting with the special market contain KVPs we're
         * interested in.
         */
        if (boost::starts_with(line, instruction_marker)) {
            /*
             * Remove the marker from the line. Only the KVP should
             * remain.
             */
            boost::replace_all(line, instruction_marker, empty);

            /*
             * Ensure the KVP is syntatically correct.
             */
            const auto pos(line.find_first_of(equals));
            if (pos == std::string::npos) {
                BOOST_LOG_SEV(lg, error) << separator_not_found;
                BOOST_THROW_EXCEPTION(building_error(separator_not_found));
            }

            identification::entities::tagged_value tv;
            tv.tag(line.substr(0, pos));
            tv.value(line.substr(pos + 1));
            applicable_to_parent_object |= (tv.tag() == dia_comment);
            r.tagged_values().push_back(tv);
            continue;
        }

        /*
         * Rather clumsy attempt to remove a trailing line from
         * comments. We tried using the indent filter but that doesn't
         * seem to work for some reason.
         */
        if (line.empty() && !previous_line_blank)
            previous_line_blank = true;
        else {
            if (previous_line_blank)
                documentation_stream << std::endl;

            previous_line_blank = false;
            documentation_stream << line << std::endl;
        }
    }

    r.documentation(documentation_stream.str());
    r.applies_to_container(applicable_to_parent_object);
    return r;
}

}
