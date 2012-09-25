/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/compressed/io/unversioned_key_io.hpp"

namespace dogen {
namespace compressed {

std::ostream& operator<<(std::ostream& stream, unversioned_key value) {
    value.to_stream(stream);
    return(stream);
}

} }