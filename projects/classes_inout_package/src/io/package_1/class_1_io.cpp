/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/classes_inout_package/io/package_1/class_1_io.hpp"

namespace dogen {
namespace classes_inout_package {
namespace package_1 {

std::ostream& operator<<(std::ostream& stream, class_1 value) {
    value.to_stream(stream);
    return(stream);
}

} } }
