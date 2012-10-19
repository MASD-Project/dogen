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
#include "dogen/prototype/test_data/unversioned_key_td.hpp"

namespace dogen {
namespace prototype {

namespace detail {

unversioned_key_generator::result_type
unversioned_key_generator::next_term(const unsigned int position) {
    unversioned_key r;

    if (position == 0) {
        r.id(static_cast<unsigned int>(0));
    } else if (position == 1) {
        r.id(static_cast<unsigned int>(30));
    } else if (position == 2) {
        r.id(static_cast<unsigned int>(60));
    }

    return r;
}

unsigned int unversioned_key_generator::length() const { return(3); }

} } }
