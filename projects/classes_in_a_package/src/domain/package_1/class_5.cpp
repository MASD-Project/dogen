/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/classes_in_a_package/domain/package_1/class_5.hpp"
#include "dogen/classes_in_a_package/io/versioned_key_io.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace classes_in_a_package {
namespace package_1 {

class_5::class_5(dogen::classes_in_a_package::versioned_key versioned_key)
    : versioned_key_(versioned_key) { }

void class_5::to_stream(std::ostream& stream) const {
    using dogen::utility::streaming::jsonify;

    stream << " {"
           << "\"__type__\": " << "\"class_5\"" << ","
           << "\"versioned_key\": " << jsonify(versioned_key_)
           << " }";
}

void class_5::swap(class_5& other) {
    std::swap(versioned_key_, other.versioned_key_);
}

class_5& class_5::operator=(class_5 other) {
    std::swap(*this, other);
    return *this;
}

} } }