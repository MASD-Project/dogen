/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/classes_without_package/domain/class_3.hpp"
#include "dogen/classes_without_package/io/versioned_key_io.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace classes_without_package {

class_3::class_3(dogen::classes_without_package::versioned_key versioned_key)
    : versioned_key_(versioned_key) { }

void class_3::to_stream(std::ostream& stream) const {
    using dogen::utility::streaming::jsonify;

    stream << " {"
           << "\"__type__\": " << "\"class_3\"" << ","
           << "\"versioned_key\": " << jsonify(versioned_key_)
           << " }";
}

void class_3::swap(class_3& other) {
    std::swap(versioned_key_, other.versioned_key_);
}

class_3& class_3::operator=(class_3 other) {
    std::swap(*this, other);
    return *this;
}

} }