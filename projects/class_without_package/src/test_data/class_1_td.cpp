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
#include "dogen/class_without_package/test_data/class_1_td.hpp"
#include "dogen/class_without_package/test_data/versioned_key_td.hpp"

namespace dogen {
namespace class_without_package {
namespace detail {

class_1_generator::value_type
class_1_generator::next_term(const unsigned int position) {
    class_1 r;

    if (position == 0) {
        r.an_attribute(static_cast<int>(0));
    } else if (position == 1) {
        r.an_attribute(static_cast<int>(30));
    } else if (position == 2) {
        r.an_attribute(static_cast<int>(60));
    }

    return r;
}

unsigned int class_1_generator::length() const { return(3); }

} } }
