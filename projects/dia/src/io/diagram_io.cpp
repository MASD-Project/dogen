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
#include "dogen/dia/domain/diagram.hpp"
#include "dogen/dia/io/diagram_data_io.hpp"
#include "dogen/dia/io/layer_io.hpp"
#include "dogen/dia/io/diagram_io.hpp"

namespace dogen {
namespace dia {

std::ostream& operator<<(std::ostream& stream, dogen::dia::diagram diagram) {
    stream << "\"diagram\": {"
           << diagram.diagram_data() << ","
           << "\"layers\":" << diagram.layers()
           << " }";
    return(stream);
}

} }
