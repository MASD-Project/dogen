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
#include "dogen/test_models/cpp_model/test_data/test_all_knobs_td.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

test_all_knobs_generator::test_all_knobs_generator() : position_(0) { }
void test_all_knobs_generator::
populate(const unsigned int position, result_type& v) {
    v = static_cast<test_all_knobs>(position % 2);
}

test_all_knobs_generator::result_type
test_all_knobs_generator::create(const unsigned int  position) {
    result_type r;
    test_all_knobs_generator::populate(position, r);
    return r;
}

test_all_knobs_generator::result_type
test_all_knobs_generator::operator()() {
    return create(position_++);
}

} } }
