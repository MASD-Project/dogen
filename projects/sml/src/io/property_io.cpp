/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"
#include "dogen/sml/io/property_io.hpp"

namespace dogen {
namespace sml {

std::ostream& operator<<(std::ostream& stream, dogen::sml::property property) {
    stream << "\"property\": {"
           << "\"name\": \"" << property.name() << "\","
           << property.type_name() << ","
           << "\"default_value\": \"" << property.default_value() << "\""
           << " }";
    return(stream);
}

} }
