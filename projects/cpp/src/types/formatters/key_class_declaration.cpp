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
#include <ostream>
#include "dogen/cpp/types/formatters/key_class_declaration.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

key_class_declaration::
key_class_declaration(std::ostream& stream,
    const bool disable_complete_constructor, const bool disable_io,
    const bool disable_serialization)
    : class_declaration(stream, disable_serialization),
      disable_complete_constructor_(disable_complete_constructor),
      disable_io_(disable_io) {}

void key_class_declaration::
hand_crafted_constructors(const class_info& ci) {
    default_constructor(ci);
    destructor(ci);
    if (!disable_complete_constructor_)
        complete_constructor(ci);
}

void key_class_declaration::format(const class_info& ci) {
    open_class(ci);
    {
        positive_indenter_scope s(indenter_);
        compiler_generated_constuctors(ci);
        hand_crafted_constructors(ci);
        friends(ci);
        if (!disable_io_)
            to_stream(ci);
        getters_and_setters(ci);
        equality(ci);
        swap_and_assignment(ci);
        member_variables(ci);
    }
    close_class();
}

} } }
