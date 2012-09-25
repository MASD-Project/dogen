/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/disable_complete_constructor/domain/unversioned_key.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace disable_complete_constructor {

unversioned_key::unversioned_key()
    : id_(static_cast<unsigned int>(0)) { }

void unversioned_key::to_stream(std::ostream& stream) const {
    using dogen::utility::streaming::jsonify;

    stream << " {"
           << "\"__type__\": " << "\"unversioned_key\"" << ","
           << "\"id\": " << jsonify(id_)
           << " }";
}

void unversioned_key::swap(unversioned_key& other) {
    std::swap(id_, other.id_);
}

unversioned_key& unversioned_key::operator=(unversioned_key other) {
    std::swap(*this, other);
    return *this;
}

} }