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
#include "dogen/cpp_formatters/types/domain_class_implementation.hpp"

namespace dogen {
namespace cpp_formatters {

domain_class_implementation::
domain_class_implementation(std::ostream& stream,
    bool disable_complete_constructor, bool disable_io) :
    class_implementation(stream),
    disable_complete_constructor_(disable_complete_constructor),
    disable_io_(disable_io) { }

void domain_class_implementation::
hand_crafted_constructors(const cpp::formattables::class_info& ci) {
    default_constructor(ci);
    move_constructor(ci);
    if (!disable_complete_constructor_)
        complete_constructor(ci);
}


void domain_class_implementation::
format(const cpp::formattables::class_info& ci) {
    hand_crafted_constructors(ci);
    if (!disable_io_)
        to_stream(ci);
    swap(ci);
    equals_method(ci);
    equals_operator(ci);
    assignment_operator(ci);
    getters_and_setters(ci);
}

} }
