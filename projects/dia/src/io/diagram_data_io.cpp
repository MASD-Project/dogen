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
#include "dogen/dia/io/attribute_io.hpp"
#include "dogen/dia/io/diagram_data_io.hpp"

namespace dogen {
namespace dia {

std::ostream&
operator<<(std::ostream& stream, dogen::dia::diagram_data diagram_data) {
    stream << "\"diagram_data\": {"
           << "\"attributes\":" << diagram_data.attributes()
           << " }";
    return(stream);
}

} }
