/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/two_layers_with_objects/io/Package_2/class_2_io.hpp"

namespace dogen {
namespace two_layers_with_objects {
namespace Package_2 {

std::ostream& operator<<(std::ostream& stream, class_2 value) {
    value.to_stream(stream);
    return(stream);
}

} } }