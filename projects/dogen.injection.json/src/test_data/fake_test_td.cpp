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
#include "dogen.injection.json/test_data/fake_test_td.hpp"

namespace dogen::injection::json {

fake_test_generator::fake_test_generator() : position_(0) { }

void fake_test_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

fake_test_generator::result_type
fake_test_generator::create(const unsigned int/*position*/) {
    fake_test r;
    return r;
}

fake_test_generator::result_type*
fake_test_generator::create_ptr(const unsigned int position) {
    fake_test* p = new fake_test();
    fake_test_generator::populate(position, *p);
    return p;
}

fake_test_generator::result_type
fake_test_generator::operator()() {
    return create(position_++);
}

}
