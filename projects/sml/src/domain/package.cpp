/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/sml/domain/package.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"

namespace dogen {
namespace sml {

bool package::operator==(const package& rhs) const {
    return name_ == rhs.name_;
}

void package::to_stream(std::ostream& stream) const {
    stream << "\"package\": {" << name() << " }";
}

} }
