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
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/dynamic/types/value_types.hpp"
#include "dogen/cpp/types/formatters/odb/field_definitions.hpp"

namespace {

dogen::dynamic::field_definition create_odb_pragma() {
    dogen::dynamic::name n;
    n.simple_name("odb_pragma");
    n.complete_name(n.simple_name());

    dogen::dynamic::field_definition r;
    r.name(n);
    r.type(dogen::dynamic::value_types::text_collection);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace odb {

const dynamic::field_definition& field_definitions::odb_pragma() {
    static auto r(create_odb_pragma());
    return r;
}

} } } }
