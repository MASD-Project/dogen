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
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/dynamic/types/value_types.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/odb/traits.hpp"
#include "dogen/cpp/types/formatters/odb/field_definitions.hpp"

namespace {

using namespace dogen::dynamic;
using namespace dogen::cpp::formatters::odb;

field_definition create_enabled() {
    field_definition r;
    r.name().simple("enabled");
    r.name().qualified(traits::facet_name() + "." + r.name().simple());
    r.ownership_hierarchy().model_name(
        dogen::cpp::formatters::traits::model_name());
    r.ownership_hierarchy().facet_name(traits::facet_name());
    r.type(value_types::boolean);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<boolean>(true));
    return r;
}

field_definition create_directory() {
    field_definition r;
    r.name().simple("directory");
    r.name().qualified(traits::facet_name() + "." + r.name().simple());
    r.ownership_hierarchy().model_name(
        dogen::cpp::formatters::traits::model_name());
    r.ownership_hierarchy().facet_name(traits::facet_name());
    r.type(value_types::text);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<text>("odb"));
    return r;
}

field_definition create_postfix() {
    field_definition r;
    r.name().simple("postfix");
    r.name().qualified(traits::facet_name() + "." + r.name().simple());
    r.ownership_hierarchy().model_name(
        dogen::cpp::formatters::traits::model_name());
    r.ownership_hierarchy().facet_name(traits::facet_name());
    r.type(value_types::text);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<text>("odb"));
    return r;
}

field_definition create_class_header_formatter_enabled() {
    field_definition r;
    r.name().simple("enabled");
    r.name().qualified(traits::class_header_formatter_name() +
        "." + r.name().simple());
    r.ownership_hierarchy().model_name(
        dogen::cpp::formatters::traits::model_name());
    r.ownership_hierarchy().facet_name(traits::facet_name());
    r.ownership_hierarchy().formatter_name(
        traits::class_header_formatter_name());
    r.type(value_types::boolean);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<boolean>(true));
    return r;
}

field_definition create_class_header_formatter_postfix() {
    field_definition r;
    r.name().simple("postfix");
    r.name().qualified(traits::class_header_formatter_name() +
        "." + r.name().simple());
    r.ownership_hierarchy().model_name(
        dogen::cpp::formatters::traits::model_name());
    r.ownership_hierarchy().facet_name(traits::facet_name());
    r.ownership_hierarchy().formatter_name(
        traits::class_header_formatter_name());
    r.type(value_types::text);
    r.scope(scope_types::root_module);
    r.default_value(boost::make_shared<text>(""));
    return r;
}

dogen::dynamic::field_definition create_odb_pragma() {
    dogen::dynamic::field_definition r;
    r.name().simple("odb_pragma");
    r.name().qualified(r.name().simple());
    r.ownership_hierarchy().model_name(
        dogen::cpp::formatters::traits::model_name());
    r.ownership_hierarchy().facet_name(traits::facet_name());
    r.type(dogen::dynamic::value_types::text_collection);
    r.scope(dogen::dynamic::scope_types::any);
    return r;
}

std::forward_list<dogen::dynamic::field_definition>
create_all_field_definitions() {
    using dogen::dynamic::field_definition;
    std::forward_list<field_definition> r;

    using fd = dogen::cpp::formatters::odb::field_definitions;
    r.push_front(fd::enabled());
    r.push_front(fd::directory());
    r.push_front(fd::postfix());

    using chf = fd::class_header_formatter;
    r.push_front(chf::enabled());
    r.push_front(chf::postfix());
    r.push_front(fd::odb_pragma());
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace odb {

const std::forward_list<dynamic::field_definition>&
field_definitions::all_field_definitions() {
    static auto r(create_all_field_definitions());
    return r;
}

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
