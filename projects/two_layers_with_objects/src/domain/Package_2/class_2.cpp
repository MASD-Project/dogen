/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/two_layers_with_objects/domain/Package_2/class_2.hpp"
#include "dogen/two_layers_with_objects/io/versioned_key_io.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace two_layers_with_objects {
namespace Package_2 {

class_2::class_2(dogen::two_layers_with_objects::versioned_key versioned_key)
    : versioned_key_(versioned_key) { }

void class_2::to_stream(std::ostream& stream) const {
    using dogen::utility::streaming::jsonify;

    stream << " {"
           << "\"__type__\": " << "\"class_2\"" << ","
           << "\"versioned_key\": " << jsonify(versioned_key_)
           << " }";
}

void class_2::swap(class_2& other) {
    std::swap(versioned_key_, other.versioned_key_);
}

class_2& class_2::operator=(class_2 other) {
    std::swap(*this, other);
    return *this;
}

} } }