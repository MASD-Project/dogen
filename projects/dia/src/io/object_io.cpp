/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/utility/io/optional_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/dia/io/object_io.hpp"
#include "dogen/dia/io/attribute_io.hpp"
#include "dogen/dia/io/child_node_io.hpp"

namespace dogen {
namespace dia {

std::ostream&
operator<<(std::ostream& stream, dogen::dia::object object) {
    stream << "\"object\": {"
           << " \"type\": \"" << object.type() << "\","
           << " \"version\": \"" << object.version() << "\","
           << " \"id\": \"" << object.id() << "\", "
           << " \"attributes\":" << object.attributes() << ","
           << object.child_node()
           << " }";
    return(stream);
}

} }
