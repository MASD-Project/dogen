/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/dia/io/string_io.hpp"

namespace dogen {
namespace dia {

std::ostream&
operator<<(std::ostream& stream, dogen::dia::string string) {
    stream << "\"string\": {"
           << " \"value\": \"" << string.value() << "\""
           << " }";
    return(stream);
}

} }
