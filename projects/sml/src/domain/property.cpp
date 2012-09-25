/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/sml/domain/qualified_name.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"

namespace dogen {
namespace sml {

bool property::operator==(const property& rhs) const {
    return
        name_ == rhs.name_ &&
        type_name_ == rhs.type_name_ &&
        default_value_ == rhs.default_value_;
}

void property::to_stream(std::ostream& stream) const {
    stream << "\"property\": {"
           << "\"name\":\"" << name() << "\","
           << "\"qualified_name\":" << type_name() << ","
           << "\"default_value\":\"" << default_value() << "\","
           << "}";
}

} }
