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

namespace dogen {
namespace dynamic {
namespace expansion {

options_copier::~options_copier() noexcept { }

std::string options_copier::static_name() {
    static std::string name("options_copier");
    return name;
}

std::string options_copier::name() const {
    return static_name();
}

const std::forward_list<std::string>&
options_copier::dependencies() const {
    static std::forward_list<std::string> r;
    return r;
}

void options_copier::setup(const expansion_context& /*ec*/) {
}

void options_copier::expand(const sml::qname& /*qn*/,
    const schema::scope_types& /*st*/, schema::object& /*o*/) const {
}

} } }
