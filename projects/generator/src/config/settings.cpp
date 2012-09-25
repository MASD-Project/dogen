/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/generator/config/settings.hpp"

namespace dogen {
namespace generator {
namespace config {

std::ostream&
operator<<(std::ostream& stream, settings value) {
    stream << "\"settings\": { "
           << value.modeling() << ", "
           << value.cpp() << ", "
           << value.sql() << ", "
           << value.troubleshooting() << ", "
           << value.output()
           << " }";

    return stream;
}

} } }
