/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/two_layers_with_objects/domain/versioned_key.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace two_layers_with_objects {

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