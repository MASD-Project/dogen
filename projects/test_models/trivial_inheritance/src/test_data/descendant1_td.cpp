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
#include "dogen/test_models/trivial_inheritance/test_data/base_td.hpp"
#include "dogen/test_models/trivial_inheritance/test_data/descendant1_td.hpp"
#include "dogen/test_models/trivial_inheritance/test_data/descendant3_td.hpp"

namespace dogen {
namespace test_models {
namespace trivial_inheritance {

void descendant1_generator::
populate(const unsigned int position, result_type& v) {
    dogen::test_models::trivial_inheritance::base_generator::populate(position, v);
}

descendant1_generator::result_type*
descendant1_generator::create_ptr(const unsigned int position) {
    return dogen::test_models::trivial_inheritance::descendant3_generator::create_ptr(position);
}

} } }
