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
#include "dogen/stereotypes/test_data/versioned_td.hpp"



namespace dogen {
namespace stereotypes {

versioned_generator::versioned_generator() : position_(0) { }

void versioned_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

versioned_generator::result_type
versioned_generator::create(const unsigned int/*position*/) {
    versioned r;
    return r;
}
versioned_generator::result_type*
versioned_generator::create_ptr(const unsigned int position) {
    versioned* p = new versioned();
    versioned_generator::populate(position, *p);
    return p;
}

versioned_generator::result_type
versioned_generator::operator()() {
    return create(position_++);
}

} }
