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
#include "dogen/split_project/domain/package/a_class.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace split_project {
namespace package {

a_class::a_class(dogen::split_project::versioned_key versioned_key)
    : versioned_key_(versioned_key) { }

void a_class::swap(a_class& other) {
    std::swap(versioned_key_, other.versioned_key_);
}

bool a_class::operator==(const a_class& rhs) const {
    return versioned_key_ == rhs.versioned_key_;
}

a_class& a_class::operator=(a_class other) {
    std::swap(*this, other);
    return *this;
}

} } }