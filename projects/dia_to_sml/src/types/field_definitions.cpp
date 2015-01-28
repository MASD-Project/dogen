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
#include "dogen/dia_to_sml/types/field_definitions.hpp"

namespace {

const std::string model_name("dia");

dogen::dynamic::field_definition create_comment() {
    dogen::dynamic::field_definition r;
    r.name().simple("comment");
    r.name().qualified("dia.comment");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::not_applicable);
    return r;
}

dogen::dynamic::field_definition create_identity_attribute() {
    dogen::dynamic::field_definition r;
    r.name().simple("identity_attribute");
    r.name().qualified("dia.identity_attribute");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::property);
    return r;
}

std::forward_list<dogen::dynamic::field_definition>
create_all_field_definitions() {
    using dogen::dynamic::field_definition;
    std::forward_list<field_definition> r;

    using dogen::dia_to_sml::field_definitions;
    r.push_front(field_definitions::comment());
    r.push_front(field_definitions::identity_attribute());
    return r;
}

}

namespace dogen {
namespace dia_to_sml {

const std::forward_list<dynamic::field_definition>&
field_definitions::all_field_definitions() {
    static auto r(create_all_field_definitions());
    return r;
}

const dynamic::field_definition& field_definitions::comment() {
    static auto r(create_comment());
    return r;
}

const dynamic::field_definition& field_definitions::identity_attribute() {
    static auto r(create_identity_attribute());
    return r;
}

} }
