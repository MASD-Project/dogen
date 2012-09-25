/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
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

first_class& first_class::operator=(first_class other) {
    std::swap(*this, other);
    return *this;
}

} } }