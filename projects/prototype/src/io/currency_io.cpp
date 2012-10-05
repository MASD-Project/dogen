/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/prototype/io/versioned_key_io.hpp"
#include "dogen/prototype/io/currency_io.hpp"

namespace dogen {
namespace prototype {

std::ostream& operator<<(std::ostream& stream, const currency& value) {
    value.to_stream(stream);
    return(stream);
}

} }
