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
#include <ostream>
#include "dogen/trivial_inheritance/domain/versioned_key.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace trivial_inheritance {

versioned_key::versioned_key()
    : id_(static_cast<unsigned int>(0)),
      version_(static_cast<unsigned int>(0)) { }

versioned_key::versioned_key(
    unsigned int id,
    unsigned int version)
    : id_(id),
      version_(version) { }

void versioned_key::to_stream(std::ostream& stream) const {
    using dogen::utility::streaming::jsonify;

    stream << " {"
           << "\"__type__\": " << "\"versioned_key\"" << ","
           << "\"id\": " << jsonify(id_) << ","
           << "\"version\": " << jsonify(version_)
           << " }";
}

unversioned_key versioned_key::to_unversioned() const {
    return unversioned_key(id());
}

void versioned_key::swap(versioned_key& other) {
    std::swap(id_, other.id_);
    std::swap(version_, other.version_);
}

versioned_key& versioned_key::operator=(versioned_key other) {
    std::swap(*this, other);
    return *this;
}

} }