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
#include "dogen/formatters/types/meta_data/field_definitions.hpp"

namespace {

dogen::dynamic::field_definition create_copyright_holder() {
    dogen::dynamic::name n;
    // n.simple_name("copyright_holder");
    // FIXME: hack to match existing definitions
    n.simple_name("copyright");
    n.complete_name(n.simple_name());

    dogen::dynamic::field_definition r;
    r.name(n);
    r.type(dogen::dynamic::value_types::text_collection);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_licence_name() {
    dogen::dynamic::name n;
    // n.simple_name("licence_name");
    // FIXME: hack to match existing definitions
    n.simple_name("licence");
    n.complete_name(n.simple_name());

    dogen::dynamic::field_definition r;
    r.name(n);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_modeline_group_name() {
    dogen::dynamic::name n;
    // n.simple_name("modeline_group_name");
    // FIXME: hack to match existing definitions
    n.simple_name("modeline_group");
    n.complete_name(n.simple_name());

    dogen::dynamic::field_definition r;
    r.name(n);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_generate_preamble() {
    dogen::dynamic::name n;
    n.simple_name("generate_preamble");
    n.owner("code_generation_marker");
    n.complete_name("code_generation_marker.generate_preamble");

    dogen::dynamic::field_definition r;
    r.name(n);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_add_date_time() {
    dogen::dynamic::name n;
    n.simple_name("add_date_time");
    n.owner("code_generation_marker");
    n.complete_name("code_generation_marker.add_date_time");

    dogen::dynamic::field_definition r;
    r.name(n);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_add_warning() {
    dogen::dynamic::name n;
    n.simple_name("add_warning");
    n.owner("code_generation_marker");
    n.complete_name("code_generation_marker.add_warning");

    dogen::dynamic::field_definition r;
    r.name(n);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_message() {
    dogen::dynamic::name n;
    n.simple_name("message");
    n.owner("code_generation_marker");
    n.complete_name("code_generation_marker.message");

    dogen::dynamic::field_definition r;
    r.name(n);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

}

namespace dogen {
namespace formatters {
namespace meta_data {

const dynamic::field_definition& field_definitions::copyright_holder() {
    static auto r(create_copyright_holder());
    return r;
}

const dynamic::field_definition& field_definitions::licence_name() {
    static auto r(create_licence_name());
    return r;
}

const dynamic::field_definition& field_definitions::modeline_group_name() {
    static auto r(create_modeline_group_name());
    return r;
}

const dynamic::field_definition& field_definitions::generate_preamble() {
    static auto r(create_generate_preamble());
    return r;
}

const dynamic::field_definition&
field_definitions::code_generation_marker::add_date_time() {
    static auto r(create_add_date_time());
    return r;
}

const dynamic::field_definition&
field_definitions::code_generation_marker::add_warning() {
    static auto r(create_add_warning());
    return r;
}

const dynamic::field_definition&
field_definitions::code_generation_marker::message() {
    static auto r(create_message());
    return r;
}

} } }
