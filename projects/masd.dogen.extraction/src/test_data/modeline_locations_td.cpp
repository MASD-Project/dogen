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
#include "masd.dogen.extraction/test_data/modeline_locations_td.hpp"

namespace masd::dogen::extraction {

modeline_locations_generator::modeline_locations_generator() : position_(0) { }
void modeline_locations_generator::
populate(const unsigned int position, result_type& v) {
    v = static_cast<modeline_locations>(position % 3);
}

modeline_locations_generator::result_type
modeline_locations_generator::create(const unsigned int  position) {
    result_type r;
    modeline_locations_generator::populate(position, r);
    return r;
}

modeline_locations_generator::result_type
modeline_locations_generator::operator()() {
    return create(position_++);
}

}
