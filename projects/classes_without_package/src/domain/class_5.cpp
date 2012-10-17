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
#include "dogen/classes_without_package/domain/class_5.hpp"
#include "dogen/classes_without_package/io/versioned_key_io.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace classes_without_package {

class_5::class_5(dogen::classes_without_package::versioned_key versioned_key)
    : versioned_key_(versioned_key) { }

void class_5::to_stream(std::ostream& stream) const {

    stream << " { "
           << "\"__type__\": " << "\"class_5\"" << ", "
           << "\"versioned_key\": " << versioned_key_
           << " }";
}

void class_5::swap(class_5& other) {
    std::swap(versioned_key_, other.versioned_key_);
}

bool class_5::operator==(const class_5& rhs) const {
    return versioned_key_ == rhs.versioned_key_;
}

class_5& class_5::operator=(class_5 other) {
    std::swap(*this, other);
    return *this;
}

} }