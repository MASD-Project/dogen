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
#include "dogen/formatters/types/field_definitions.hpp"

namespace {

const std::string model_name("formatters");

dogen::dynamic::field_definition create_copyright_notices() {
    dogen::dynamic::field_definition r;
    r.name().simple("copyright_notice");
    r.name().qualified(r.name().simple());
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::text_collection);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_licence_name() {
    dogen::dynamic::field_definition r;
    r.name().simple("licence_name");
    r.name().qualified(r.name().simple());
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_modeline_group_name() {
    dogen::dynamic::field_definition r;
    r.name().simple("modeline_group_name");
    r.name().qualified(r.name().simple());
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_generate_preamble() {
    dogen::dynamic::field_definition r;
    r.name().simple("generate_preamble");
    r.name().qualified("code_generation_marker.generate_preamble");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_add_date_time() {
    dogen::dynamic::field_definition r;
    r.name().simple("add_date_time");
    r.name().qualified("code_generation_marker.add_date_time");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_add_warning() {
    dogen::dynamic::field_definition r;
    r.name().simple("add_warning");
    r.name().qualified("code_generation_marker.add_warning");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

dogen::dynamic::field_definition create_message() {
    dogen::dynamic::field_definition r;
    r.name().simple("message");
    r.name().qualified("code_generation_marker.message");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

}

namespace dogen {
namespace formatters {

const dynamic::field_definition& field_definitions::copyright_notices() {
    static auto r(create_copyright_notices());
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

} }
