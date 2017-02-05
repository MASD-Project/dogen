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
#include "dogen/yarn/types/decomposer.hpp"

namespace dogen {
namespace yarn {

void decomposer::add_name(const std::string& owner, const name& n) {
    std::pair<std::string, name> pair;
    pair.first = owner;
    pair.second = n;
    result_.names().push_back(pair);
}

void decomposer::add_name_tree(const std::string& owner, const name_tree& nt) {
    std::pair<std::string, name_tree> pair;
    pair.first = owner;
    pair.second = nt;
    result_.name_trees().push_back(pair);
}

void decomposer::
add_names(const std::string& owner, const std::list<name>& names) {
    for (const auto& n : names)
        add_name(owner, n);
}

void decomposer::
process_attributes(const std::string& owner, const std::list<attribute>& attrs) {
    for (const auto& attr : attrs) {
        add_name(owner, attr.name());
        add_name_tree(owner, attr.parsed_type());
    }
}

void decomposer::process_element(const element& e) {
    add_name(e.name().id(), e.name());
}

void decomposer::decompose(const yarn::concept& c) {
    process_element(c);
    process_attributes(c.name().id(), c.local_attributes());
}

void decomposer::decompose(const yarn::module& m) {
    /*
     * The global module represents the unnamed global
     * namespace. There can only be one of these and it is generated
     * internally by Dogen so there is nothing to validate.
     */
    if (m.is_global_module())
        return;

    process_element(m);
}

void decomposer::decompose(const yarn::enumeration& e) {
    process_element(e);
    for (const auto& en : e.enumerators())
        add_name(e.name().id(), en.name());
}

void decomposer::decompose(const yarn::exception& e) {
    process_element(e);
}

void decomposer::decompose(const yarn::object& o) {
    process_element(o);
    process_attributes(o.name().id(), o.local_attributes());
}

void decomposer::decompose(const yarn::builtin& b) {
    process_element(b);
}

const decomposition_result&  decomposer::result() const {
    return result_;
}

} }
