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
#include "dogen/test_models/std_model/test_data/enum_with_std_builtin_td.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

enum_with_std_builtin_generator::enum_with_std_builtin_generator() : position_(0) { }
void enum_with_std_builtin_generator::
populate(const unsigned int position, result_type& v) {
    v = static_cast<enum_with_std_builtin>(position % 3);
}

enum_with_std_builtin_generator::result_type
enum_with_std_builtin_generator::create(const unsigned int  position) {
    result_type r;
    enum_with_std_builtin_generator::populate(position, r);
    return r;
}

enum_with_std_builtin_generator::result_type
enum_with_std_builtin_generator::operator()() {
    return create(position_++);
}

} } }
