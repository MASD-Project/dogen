/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/enable_facet_io/io/package1/first_class_io.hpp"

namespace dogen {
namespace enable_facet_io {
namespace package1 {

std::ostream& operator<<(std::ostream& stream, first_class value) {
    value.to_stream(stream);
    return(stream);
}

} } }