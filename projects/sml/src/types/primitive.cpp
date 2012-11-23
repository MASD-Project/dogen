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
#include "dogen/sml/types/primitive.hpp"

namespace dogen {
namespace sml {

primitive::primitive()
    : generate_(static_cast<bool>(0)) { }

primitive::primitive(
    const dogen::sml::qualified_name& name,
    const bool generate,
    const std::string& documentation)
    : name_(name),
      generate_(generate),
      documentation_(documentation) { }

void primitive::swap(primitive& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(generate_, other.generate_);
    swap(documentation_, other.documentation_);
}

bool primitive::operator==(const primitive& rhs) const {
    return name_ == rhs.name_ &&
        generate_ == rhs.generate_ &&
        documentation_ == rhs.documentation_;
}

primitive& primitive::operator=(primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }