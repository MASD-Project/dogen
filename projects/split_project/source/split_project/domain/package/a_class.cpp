/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/split_project/domain/package/a_class.hpp"
#include "dogen/split_project/io/versioned_key_io.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace split_project {
namespace package {

a_class::a_class(dogen::split_project::versioned_key versioned_key)
    : versioned_key_(versioned_key) { }

void a_class::to_stream(std::ostream& stream) const {
    using dogen::utility::streaming::jsonify;

    stream << " {"
           << "\"__type__\": " << "\"a_class\"" << ","
           << "\"versioned_key\": " << jsonify(versioned_key_)
           << " }";
}

void a_class::swap(a_class& other) {
    std::swap(versioned_key_, other.versioned_key_);
}

a_class& a_class::operator=(a_class other) {
    std::swap(*this, other);
    return *this;
}

} } }