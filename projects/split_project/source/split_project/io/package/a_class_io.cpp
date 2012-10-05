/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/split_project/io/package/a_class_io.hpp"

namespace dogen {
namespace split_project {
namespace package {

std::ostream& operator<<(std::ostream& stream, a_class value) {
    value.to_stream(stream);
    return(stream);
}

} } }