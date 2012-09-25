/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/class_without_package/domain/class_1.hpp"
#include "dogen/class_without_package/io/versioned_key_io.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace class_without_package {

class_1::class_1()
    : an_attribute_(static_cast<int>(0)) { }

class_1::class_1(
    int an_attribute,
    dogen::class_without_package::versioned_key versioned_key)
    : an_attribute_(an_attribute),
      versioned_key_(versioned_key) { }

void class_1::to_stream(std::ostream& stream) const {
    using dogen::utility::streaming::jsonify;

    stream << " {"
           << "\"__type__\": " << "\"class_1\"" << ","
           << "\"an_attribute\": " << jsonify(an_attribute_) << ","
           << "\"versioned_key\": " << jsonify(versioned_key_)
           << " }";
}

void class_1::swap(class_1& other) {
    std::swap(an_attribute_, other.an_attribute_);
    std::swap(versioned_key_, other.versioned_key_);
}

class_1& class_1::operator=(class_1 other) {
    std::swap(*this, other);
    return *this;
}

} }