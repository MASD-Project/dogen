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
const std::string model_name("cpp");
const std::string facet_name("odb");
const std::string class_header_formatter_name("class_header_formatter");
const std::string class_implementation_formatter_name(
    "class_implementation_formatter");
const std::string enumeration_header_formatter_name(
    "enumeration_header_formatter");
const std::string enumeration_implementation_formatter_name(
    "enumeration_implementation_formatter");

dogen::dynamic::field_definition create_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.odb.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_directory() {
    dogen::dynamic::field_definition r;
    r.name().simple("directory");
    r.name().qualified("cpp.odb.directory");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.odb.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_class_header_formatter_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.odb.class_header_formatter.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_header_formatter_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_class_header_formatter_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.odb.class_header_formatter.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_header_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_odb_pragma() {
    dogen::dynamic::field_definition r;
    r.name().simple("odb_pragma");
    r.name().qualified(r.name().simple());
    r.ownership_hierarchy().model("cpp");
    r.ownership_hierarchy().facet("odb");
    r.type(dogen::dynamic::value_types::text_collection);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace odb {

const dynamic::field_definition& field_definitions::enabled() {
    static auto r(create_enabled());
    return r;
}

const dynamic::field_definition& field_definitions::directory() {
    static auto r(create_directory());
    return r;
}

const dynamic::field_definition& field_definitions::postfix() {
    static auto r(create_postfix());
    return r;
}

const dynamic::field_definition&
field_definitions::class_header_formatter::enabled() {
    static auto r(create_class_header_formatter_enabled());
    return r;
}

const dynamic::field_definition&
field_definitions::class_header_formatter::postfix() {
    static auto r(create_class_header_formatter_postfix());
    return r;
}

const dynamic::field_definition& field_definitions::odb_pragma() {
    static auto r(create_odb_pragma());
    return r;
}

} } } }
