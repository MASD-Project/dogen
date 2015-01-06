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
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/dynamic/types/value_types.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/dia_to_sml/types/initializer.hpp"

namespace dogen {
namespace dia_to_sml {

dynamic::field_definition create_comment() {
    dynamic::name n;
    n.simple_name("comment");
    n.owner("dia");
    n.complete_name("dia.comment");

    dynamic::field_definition r;
    r.name(n);
    r.type(dynamic::value_types::boolean);
    r.scope(dynamic::scope_types::not_applicable);
    return r;
}

dynamic::field_definition create_is_final() {
    dynamic::name n;
    n.simple_name("is_final");
    n.owner("dia");
    n.complete_name("dia.is_final");

    dynamic::field_definition r;
    r.name(n);
    r.type(dynamic::value_types::boolean);
    r.scope(dynamic::scope_types::entity);
    return r;
}

dynamic::field_definition create_identity_attribute() {
    dynamic::name n;
    n.simple_name("identity_attribute");
    n.owner("dia");
    n.complete_name("dia.identity_attribute");

    dynamic::field_definition r;
    r.name(n);
    r.type(dynamic::value_types::boolean);
    r.scope(dynamic::scope_types::property);
    return r;
}

void initializer::initialize() {
    auto& reg(dynamic::workflow::registrar());
    reg.register_field_definition(create_comment());
    reg.register_field_definition(create_is_final());
    reg.register_field_definition(create_identity_attribute());
}

} }
