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
#include "dogen/sml_to_cpp/types/boost_model_helper.hpp" // FIXME: hack
#include "dogen/cpp_formatters/types/includes.hpp"

namespace {

const std::string include("#include ");
const std::string open_system("<");
const std::string close_system(">");
const std::string open_user("\"");
const std::string close_user("\"");

const char angle_bracket('<');
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

}

namespace dogen {
namespace cpp_formatters {

bool include_directive_comparer(
    const std::string& lhs, const std::string& rhs) {
    if (lhs.empty() || rhs.empty())
        return false;

    const bool lhs_has_angle_brackets(lhs[0] == angle_bracket);
    const bool rhs_has_angle_brackets(rhs[0] == angle_bracket);

    if (lhs_has_angle_brackets && !rhs_has_angle_brackets)
        return true;

    if (!lhs_has_angle_brackets && rhs_has_angle_brackets)
        return false;

    if (lhs_has_angle_brackets && rhs_has_angle_brackets) {
        const auto npos(std::string::npos);
        const bool lhs_is_boost(lhs.find_first_of(boost_name) != npos);
        const bool rhs_is_boost(rhs.find_first_of(boost_name) != npos);
        if (!lhs_is_boost && rhs_is_boost)
            return false;

        if (lhs_is_boost && !rhs_is_boost)
            return true;

        // FIXME: hacks for headers that must be last
        const bool lhs_is_gregorian(
            lhs.find_first_of(boost_serialization_gregorian) != npos);
        const bool rhs_is_gregorian(
            rhs.find_first_of(boost_serialization_gregorian) != npos);
        if (lhs_is_gregorian && !rhs_is_gregorian)
            return true;

        if (!lhs_is_gregorian && rhs_is_gregorian)
            return false;
    }

    return lhs.size() < rhs.size();
}

includes::includes(std::ostream& stream, const bool blank_line)
    : stream_(stream), utility_(stream_, indenter_), blank_line_(blank_line) { }

void includes::format(std::list<std::string> v) {
    for (auto i : v)
        stream_ << include << i << std::endl;
}

void includes::format(const cpp::formattables::file_info& f) {
    const auto inc(f.includes());

    if (inc.system().empty() && inc.user().empty())
        return;

    std::list<std::string> combined;
    for (const auto i : inc.system()) {
        std::ostringstream s;
        s << open_system << i.generic_string() << close_system;
        combined.push_back(s.str());
    }

    for (const auto i : inc.user()) {
        std::ostringstream s;
        s << open_user << i.generic_string() << close_user;
        combined.push_back(s.str());
    }

    combined.sort(include_directive_comparer);
    format(combined);

    if (blank_line_)
        utility_.blank_line();
}

} }
