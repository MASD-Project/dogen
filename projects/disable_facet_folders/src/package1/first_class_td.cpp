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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen/disable_facet_folders/package1/first_class_td.hpp"
#include "dogen/disable_facet_folders/versioned_key_td.hpp"

namespace dogen {
namespace disable_facet_folders {
namespace package1 {
namespace detail {

first_class_generator::value_type
first_class_generator::next_term(const unsigned int position) {
    first_class r;

    if (position == 0) {
        r.public_attribute(static_cast<int>(0));
        r.private_attribute(static_cast<int>(1));
    } else if (position == 1) {
        r.public_attribute(static_cast<int>(30));
        r.private_attribute(static_cast<int>(31));
    } else if (position == 2) {
        r.public_attribute(static_cast<int>(60));
        r.private_attribute(static_cast<int>(61));
    }

    return r;
}

unsigned int first_class_generator::length() const { return(3); }

} } } }
