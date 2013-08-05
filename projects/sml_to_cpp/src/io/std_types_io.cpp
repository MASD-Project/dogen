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
#include <stdexcept>
#include "dogen/sml_to_cpp/io/std_types_io.hpp"

namespace dogen {
namespace sml_to_cpp {

std::ostream& operator<<(std::ostream& s, const std_types& v) {
    s << "{ " << "\"__type__\": " << "\"std_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case std_types::invalid:
        attr = "\"invalid\"";
        break;
    case std_types::string:
        attr = "\"string\"";
        break;
    case std_types::int8_t:
        attr = "\"int8_t\"";
        break;
    case std_types::int16_t:
        attr = "\"int16_t\"";
        break;
    case std_types::int32_t:
        attr = "\"int32_t\"";
        break;
    case std_types::int64_t:
        attr = "\"int64_t\"";
        break;
    case std_types::uint8_t:
        attr = "\"uint8_t\"";
        break;
    case std_types::uint16_t:
        attr = "\"uint16_t\"";
        break;
    case std_types::uint32_t:
        attr = "\"uint32_t\"";
        break;
    case std_types::uint64_t:
        attr = "\"uint64_t\"";
        break;
    case std_types::array:
        attr = "\"array\"";
        break;
    case std_types::forward_list:
        attr = "\"forward_list\"";
        break;
    case std_types::vector:
        attr = "\"vector\"";
        break;
    case std_types::set:
        attr = "\"set\"";
        break;
    case std_types::multiset:
        attr = "\"multiset\"";
        break;
    case std_types::map:
        attr = "\"map\"";
        break;
    case std_types::multimap:
        attr = "\"multimap\"";
        break;
    case std_types::deque:
        attr = "\"deque\"";
        break;
    case std_types::list:
        attr = "\"list\"";
        break;
    case std_types::unordered_map:
        attr = "\"unordered_map\"";
        break;
    case std_types::unordered_set:
        attr = "\"unordered_set\"";
        break;
    case std_types::algorithm:
        attr = "\"algorithm\"";
        break;
    case std_types::ostream:
        attr = "\"ostream\"";
        break;
    case std_types::iosfwd:
        attr = "\"iosfwd\"";
        break;
    case std_types::sstream:
        attr = "\"sstream\"";
        break;
    case std_types::stdexcept:
        attr = "\"stdexcept\"";
        break;
    case std_types::functional:
        attr = "\"functional\"";
        break;
    case std_types::pair:
        attr = "\"pair\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for std_types");
    }
    s << attr << " }";
    return s;
}

} }