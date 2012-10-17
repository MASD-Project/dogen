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
#include "dogen/enable_facet_domain/domain/package1/first_class.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace enable_facet_domain {
namespace package1 {

first_class::first_class()
    : public_attribute_(static_cast<int>(0)),
      private_attribute_(static_cast<int>(0)) { }

first_class::first_class(
    int public_attribute,
    int private_attribute,
    dogen::enable_facet_domain::versioned_key versioned_key)
    : public_attribute_(public_attribute),
      private_attribute_(private_attribute),
      versioned_key_(versioned_key) { }

void first_class::swap(first_class& other) {
    std::swap(public_attribute_, other.public_attribute_);
    std::swap(private_attribute_, other.private_attribute_);
    std::swap(versioned_key_, other.versioned_key_);
}

bool first_class::operator==(const first_class& rhs) const {
    return public_attribute_ == rhs.public_attribute_ &&
        private_attribute_ == rhs.private_attribute_ &&
        versioned_key_ == rhs.versioned_key_;
}

first_class& first_class::operator=(first_class other) {
    std::swap(*this, other);
    return *this;
}

} } }