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
#include "dogen/yarn/test_data/element_td.hpp"
#include "dogen/yarn/test_data/visitor_td.hpp"

namespace dogen {
namespace yarn {

visitor_generator::visitor_generator() : position_(0) { }

void visitor_generator::
populate(const unsigned int position, result_type& v) {
    dogen::yarn::element_generator::populate(position, v);
}

visitor_generator::result_type
visitor_generator::create(const unsigned int position) {
    visitor r;
    visitor_generator::populate(position, r);
    return r;
}

visitor_generator::result_type*
visitor_generator::create_ptr(const unsigned int position) {
    visitor* p = new visitor();
    visitor_generator::populate(position, *p);
    return p;
}

visitor_generator::result_type
visitor_generator::operator()() {
    return create(position_++);
}

} }
