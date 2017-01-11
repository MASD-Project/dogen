/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/decomposer.hpp"

namespace dogen {
namespace yarn {

void decomposer::add_name(const name& n) {
    result_.names().push_back(n);
}

void decomposer::add_name_tree(const name_tree& nt) {
    result_.name_trees().push_back(nt);
}

void decomposer::add_names(const std::list<name>& names) {
    for (const auto& n : names)
        add_name(n);
}

void decomposer::process_attributes(const std::list<attribute>& attrs) {
    for (const auto& attr : attrs) {
        add_name(attr.name());
        add_name_tree(attr.parsed_type());
    }
}

void decomposer::process_element(const element& e) {
    add_name(e.name());
}

void decomposer::visit(const yarn::concept& c) {
    process_element(c);
    process_attributes(c.local_attributes());
}

void decomposer::visit(const yarn::module& m) {
    /*
     * The global module represents the unnamed global
     * namespace. There can only be one of these and it is generated
     * internally by Dogen so there is nothing to validate.
     */
    if (m.is_global_module())
        return;

    add_name(m.name());
}

void decomposer::visit(const yarn::enumeration& e) {
    process_element(e);
    for (const auto& en : e.enumerators())
        add_name(en.name());
}

void decomposer::visit(const yarn::exception& e) {
    process_element(e);
}

void decomposer::visit(const yarn::object& o) {
    process_element(o);
    process_attributes(o.local_attributes());

    if (o.is_abstract())
        result_.abstract_elements().insert(o.name().id());
}

void decomposer::visit(const yarn::primitive& p) {
    process_element(p);
}

const decomposition_result&  decomposer::result() const {
    return result_;
}

} }
