/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Dogen Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/utility/io/shared_ptr_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/dia/io/attribute_io.hpp"
#include "dogen/dia/io/composite_io.hpp"

namespace dogen {
namespace dia {

std::ostream&
operator<<(std::ostream& stream, dogen::dia::composite composite) {
    stream << "\"composite\": {"
           << " \"type\": \"" << composite.type() << "\", "
           << "\"value\":" << composite.value() << ", "
           << composite.inner_composite()
           << " }";
    return(stream);
}

} }
