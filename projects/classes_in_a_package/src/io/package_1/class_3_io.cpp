/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/classes_in_a_package/io/package_1/class_3_io.hpp"

namespace dogen {
namespace classes_in_a_package {
namespace package_1 {

std::ostream& operator<<(std::ostream& stream, class_3 value) {
    value.to_stream(stream);
    return(stream);
}

} } }