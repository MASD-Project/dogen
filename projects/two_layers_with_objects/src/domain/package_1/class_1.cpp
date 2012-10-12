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
#include "dogen/two_layers_with_objects/domain/package_1/class_1.hpp"
#include "dogen/two_layers_with_objects/io/versioned_key_io.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace two_layers_with_objects {
namespace package_1 {

class_1::class_1(dogen::two_layers_with_objects::versioned_key versioned_key)
    : versioned_key_(versioned_key) { }

void class_1::to_stream(std::ostream& stream) const {
    using dogen::utility::streaming::jsonify;

    stream << " {"
           << "\"__type__\": " << "\"class_1\"" << ","
           << "\"versioned_key\": " << jsonify(versioned_key_)
           << " }";
}

void class_1::swap(class_1& other) {
    std::swap(versioned_key_, other.versioned_key_);
}

bool class_1::operator==(const class_1& rhs) const {
    return versioned_key_ == rhs.versioned_key_;
}

class_1& class_1::operator=(class_1 other) {
    std::swap(*this, other);
    return *this;
}

} } }