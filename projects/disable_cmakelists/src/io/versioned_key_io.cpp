/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/disable_cmakelists/io/versioned_key_io.hpp"

namespace dogen {
namespace disable_cmakelists {

std::ostream& operator<<(std::ostream& stream, versioned_key value) {
    value.to_stream(stream);
    return(stream);
}

} }