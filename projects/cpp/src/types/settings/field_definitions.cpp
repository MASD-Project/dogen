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
#include <boost/make_shared.hpp>
#include "dogen/dynamic/types/text.hpp"
#include "dogen/dynamic/types/boolean.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/settings/field_definitions.hpp"

namespace {

using namespace dogen::dynamic;
using namespace dogen::cpp::formatters;

field_definition create_enabled() {
    field_definition r;
    r.name().simple("enabled");
    r.name().qualified(traits::model_name() + ".enabled");
    r.ownership_hierarchy().model_name(traits::model_name());
    r.type(value_types::boolean);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<boolean>(true));
    return r;
}

field_definition create_split_project() {
    field_definition r;
    r.name().simple("split_project");
    r.name().qualified(traits::model_name() + ".split_project");
    r.ownership_hierarchy().model_name(traits::model_name());
    r.type(value_types::boolean);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<boolean>(false));
    return r;
}

field_definition create_header_file_extension() {
    field_definition r;
    r.name().simple("header_file_extension");
    r.name().qualified(traits::model_name() + ".header_file_extension");
    r.ownership_hierarchy().model_name(traits::model_name());
    r.type(value_types::text);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<text>("hpp"));
    return r;
}

field_definition create_implementation_file_extension() {
    field_definition r;
    r.name().simple("implementation_file_extension");
    r.name().qualified(traits::model_name() + ".implementation_file_extension");
    r.ownership_hierarchy().model_name(traits::model_name());
    r.type(value_types::text);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<text>("cpp"));
    return r;
}

field_definition create_enable_facet_folders() {
    field_definition r;
    r.name().simple("enable_facet_folders");
    r.name().qualified(traits::model_name() + ".enable_facet_folders");
    r.ownership_hierarchy().model_name(traits::model_name());
    r.type(value_types::boolean);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<boolean>(true));
    return r;
}

field_definition create_enable_unique_file_names() {
    field_definition r;
    r.name().simple("enable_unique_file_names");
    r.name().qualified(traits::model_name() + ".enable_unique_file_names");
    r.ownership_hierarchy().model_name(traits::model_name());
    r.type(value_types::boolean);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<boolean>(true));
    return r;
}

field_definition create_type_family() {
    field_definition r;
    r.name().simple("family");
    r.name().qualified(traits::model_name() + ".type.family");
    r.ownership_hierarchy().model_name(traits::model_name());
    r.type(value_types::text);
    r.scope(scope_types::entity);
    return r;
}

field_definition
create_type_requires_manual_default_constructor() {
    field_definition r;
    r.name().simple("requires_manual_default_constructor");
    r.name().qualified(traits::model_name() +
        ".type.requires_manual_default_constructor");
    r.ownership_hierarchy().model_name(traits::model_name());
    r.type(value_types::boolean);
    r.scope(scope_types::entity);
    r.default_value(boost::make_shared<boolean>(false));
    return r;
}

field_definition
create_type_requires_manual_move_constructor() {
    field_definition r;
    r.name().simple("requires_manual_move_constructor");
    r.name().qualified(traits::model_name() +
        ".type.requires_manual_move_constructor");
    r.ownership_hierarchy().model_name(traits::model_name());
    r.type(value_types::boolean);
    r.scope(scope_types::entity);
    r.default_value(boost::make_shared<boolean>(false));
    return r;
}

std::forward_list<field_definition>
create_all_field_definitions() {
    std::forward_list<field_definition> r;

    using fd = dogen::cpp::settings::field_definitions;
    r.push_front(fd::enabled());
    r.push_front(fd::split_project());
    r.push_front(fd::header_file_extension());
    r.push_front(fd::implementation_file_extension());
    r.push_front(fd::enable_facet_folders());
    r.push_front(fd::enable_unique_file_names());

    using type = fd::type;
    r.push_front(type::family());
    r.push_front(type::requires_manual_default_constructor());
    r.push_front(type::requires_manual_move_constructor());

    return r;
}

}

namespace dogen {
namespace cpp {
namespace settings {

const std::forward_list<dynamic::field_definition>&
field_definitions::all_field_definitions() {
    static auto r(create_all_field_definitions());
    return r;
}

const dynamic::field_definition& field_definitions::enabled() {
    static auto r(create_enabled());
    return r;
}

const dynamic::field_definition& field_definitions::split_project() {
    static auto r(create_split_project());
    return r;
}

const dynamic::field_definition& field_definitions::header_file_extension() {
    static auto r(create_header_file_extension());
    return r;
}

const dynamic::field_definition&
field_definitions::implementation_file_extension() {
    static auto r(create_implementation_file_extension());
    return r;
}

const dynamic::field_definition& field_definitions::enable_facet_folders() {
    static auto r(create_enable_facet_folders());
    return r;
}

const dynamic::field_definition& field_definitions::enable_unique_file_names() {
    static auto r(create_enable_unique_file_names());
    return r;
}

const dynamic::field_definition& field_definitions::type::family() {
    static auto r(create_type_family());
    return r;
}

const dynamic::field_definition&
field_definitions::type::requires_manual_default_constructor() {
    static auto r(create_type_requires_manual_default_constructor());
    return r;
}

const dynamic::field_definition&
field_definitions::type::requires_manual_move_constructor() {
    static auto r(create_type_requires_manual_move_constructor());
    return r;
}

} } }
