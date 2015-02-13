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

namespace {

using dogen::cpp::formattables::inclusion;
using dogen::cpp::formattables::inclusion_delimiter_types;

inclusion create_std_iosfwd() {
    inclusion r;
    r.no_inclusion_required(false);
    r.inclusion_path("iosfwd");
    r.inclusion_delimiter_type(inclusion_delimiter_types::angle_brackets);
    return r;
}

inclusion create_std_algorithm() {
    inclusion r;
    r.no_inclusion_required(false);
    r.inclusion_path("algorithm");
    r.inclusion_delimiter_type(inclusion_delimiter_types::angle_brackets);
    return r;
}

inclusion create_std_ostream() {
    inclusion r;
    r.no_inclusion_required(false);
    r.inclusion_path("ostream");
    r.inclusion_delimiter_type(inclusion_delimiter_types::angle_brackets);
    return r;
}

inclusion create_std_functional() {
    inclusion r;
    r.no_inclusion_required(false);
    r.inclusion_path("functional");
    r.inclusion_delimiter_type(inclusion_delimiter_types::angle_brackets);
    return r;
}

inclusion create_boost_nvp() {
    inclusion r;
    r.no_inclusion_required(false);
    r.inclusion_path("boost/serialization/nvp.hpp");
    r.inclusion_delimiter_type(inclusion_delimiter_types::angle_brackets);
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formatters {

formattables::inclusion inclusion_constants::std::iosfwd() {
    static auto r(create_std_iosfwd());
    return r;
}

formattables::inclusion inclusion_constants::std::algorithm() {
    static auto r(create_std_algorithm());
    return r;
}

formattables::inclusion inclusion_constants::std::ostream() {
    static auto r(create_std_ostream());
    return r;
}

formattables::inclusion inclusion_constants::std::functional() {
    static auto r(create_std_functional());
    return r;
}

formattables::inclusion inclusion_constants::boost::nvp() {
    static auto r(create_boost_nvp());
    return r;
}

} } }
