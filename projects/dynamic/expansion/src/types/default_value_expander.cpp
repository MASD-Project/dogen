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
#include <string>
#include "dogen/dynamic/expansion/types/options_copier.hpp"
#include "dogen/dynamic/expansion/types/default_value_expander.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

default_value_expander::~default_value_expander() noexcept { }

std::string default_value_expander::static_name() {
    static std::string name("default_value_expander");
    return name;
}

std::string default_value_expander::name() const {
    return static_name();
}

const std::forward_list<std::string>&
default_value_expander::dependencies() const {
    static std::forward_list<std::string> r { options_copier::static_name() };
    return r;
}

void default_value_expander::setup(expansion_context& /*ec*/) {
}

void default_value_expander::expand(const sml::qname& /*qn*/,
    const schema::scope_types& /*st*/, schema::object& /*o*/) const {
}

} } }
