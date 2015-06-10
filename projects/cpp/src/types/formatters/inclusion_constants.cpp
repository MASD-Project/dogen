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
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

std::string inclusion_constants::std::string() {
    static ::std::string r("<string>");
    return r;
}

std::string inclusion_constants::std::iosfwd() {
    static ::std::string r("<iosfwd>");
    return r;
}

std::string inclusion_constants::std::algorithm() {
    static ::std::string r("<algorithm>");
    return r;
}

std::string inclusion_constants::std::ostream() {
    static ::std::string r("<ostream>");
    return r;
}

std::string inclusion_constants::std::functional() {
    static ::std::string r("<functional>");
    return r;
}

std::string inclusion_constants::boost::algorithm::string() {
    static ::std::string r("<boost/algorithm/string.hpp>");
    return r;
}

std::string inclusion_constants::boost::io::ios_state() {
    static ::std::string r("<boost/io/ios_state.hpp>");
    return r;
}

std::string inclusion_constants::boost::serialization::nvp() {
    static ::std::string r("<boost/serialization/nvp.hpp>");
    return r;
}

std::string inclusion_constants::boost::exception::info() {
    static ::std::string r("<boost/exception/info.hpp>");
    return r;
}

} } }
