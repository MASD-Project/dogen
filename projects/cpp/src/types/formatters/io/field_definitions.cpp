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
#include "dogen/cpp/types/formatters/io/field_definitions.hpp"

namespace {

const std::string model_name("cpp");
const std::string facet_name("io");
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
    r.name().qualified("cpp.io.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_directory() {
    dogen::dynamic::field_definition r;
    r.name().simple("directory");
    r.name().qualified("cpp.io.directory");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.io.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_class_header_formatter_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.io.class_header_formatter.enabled");
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
    r.name().qualified("cpp.io.class_header_formatter.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_header_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_class_header_formatter_file_name() {
    dogen::dynamic::field_definition r;
    r.name().simple("file_name");
    r.name().qualified("cpp.io.class_header_formatter.file_name");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_header_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition
create_class_implementation_formatter_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.io.class_implementation_formatter.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_implementation_formatter_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition
create_class_implementation_formatter_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.io.class_implementation_formatter.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_implementation_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition
create_enumeration_header_formatter_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.io.enumeration_header_formatter.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(enumeration_header_formatter_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition
create_enumeration_header_formatter_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.io.enumeration_header_formatter.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(enumeration_header_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition
create_enumeration_implementation_formatter_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.io.enumeration_implementation_formatter.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(
        enumeration_implementation_formatter_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition
create_enumeration_implementation_formatter_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.io.enumeration_implementation_formatter.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(
        enumeration_implementation_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace io {

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

const dynamic::field_definition&
field_definitions::class_header_formatter::file_name() {
    static auto r(create_class_header_formatter_file_name());
    return r;
}

const dynamic::field_definition&
field_definitions::class_implementation_formatter::enabled() {
    static auto r(create_class_implementation_formatter_enabled());
    return r;
}

const dynamic::field_definition&
field_definitions::class_implementation_formatter::postfix() {
    static auto r(create_class_implementation_formatter_postfix());
    return r;
}

const dynamic::field_definition&
field_definitions::enumeration_header_formatter::enabled() {
    static auto r(create_enumeration_header_formatter_enabled());
    return r;
}

const dynamic::field_definition&
field_definitions::enumeration_header_formatter::postfix() {
    static auto r(create_enumeration_header_formatter_postfix());
    return r;
}

const dynamic::field_definition&
field_definitions::enumeration_implementation_formatter::enabled() {
    static auto r(create_enumeration_implementation_formatter_enabled());
    return r;
}

const dynamic::field_definition&
field_definitions::enumeration_implementation_formatter::postfix() {
    static auto r(create_enumeration_implementation_formatter_postfix());
    return r;
}

} } } }
