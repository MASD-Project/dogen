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
#include <iostream>
#include "dogen/cpp/types/formatters/key_class_implementation.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

key_class_implementation::
key_class_implementation(std::ostream& stream,
    bool disable_complete_constructor, bool disable_io) :
    class_implementation(stream),
    disable_complete_constructor_(disable_complete_constructor),
    disable_io_(disable_io) { }

void key_class_implementation::
hand_crafted_constructors(const class_info& vm) {
    default_constructor(vm);
    if (!disable_complete_constructor_)
        complete_constructor(vm);
}

void key_class_implementation::format(const class_info& vm) {
    hand_crafted_constructors(vm);
    if (!disable_io_)
        to_stream(vm);
    swap(vm);
    equals_operator(vm);
    assignment_operator(vm);
    getters_and_setters(vm);
}

} } }
