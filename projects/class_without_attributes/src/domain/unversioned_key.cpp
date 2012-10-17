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
#include "dogen/class_without_attributes/domain/unversioned_key.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace class_without_attributes {

unversioned_key::unversioned_key()
    : id_(static_cast<unsigned int>(0)) { }

unversioned_key::unversioned_key(unsigned int id)
    : id_(id) { }

void unversioned_key::swap(unversioned_key& other) {
    std::swap(id_, other.id_);
}

bool unversioned_key::operator==(const unversioned_key& rhs) const {
    return id_ == rhs.id_;
}

unversioned_key& unversioned_key::operator=(unversioned_key other) {
    std::swap(*this, other);
    return *this;
}

} }