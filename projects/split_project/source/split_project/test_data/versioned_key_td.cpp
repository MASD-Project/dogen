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
#include "dogen/split_project/test_data/versioned_key_td.hpp"

namespace dogen {
namespace split_project {
namespace detail {

versioned_key_generator::value_type
versioned_key_generator::next_term(const unsigned int position) {
    versioned_key r;

    if (position == 0) {
        r.id(static_cast<unsigned int>(0));
        r.version(static_cast<unsigned int>(1));
    } else if (position == 1) {
        r.id(static_cast<unsigned int>(30));
        r.version(static_cast<unsigned int>(31));
    } else if (position == 2) {
        r.id(static_cast<unsigned int>(60));
        r.version(static_cast<unsigned int>(61));
    }

    return r;
}

unsigned int versioned_key_generator::length() const { return(3); }

} } }
