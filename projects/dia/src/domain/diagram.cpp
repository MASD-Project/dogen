/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/dia/domain/diagram.hpp"

namespace dogen {
namespace dia {

bool diagram::operator==(const dogen::dia::diagram& value) const {
    return
        diagram_data_ == value.diagram_data() &&
        layers_ == value.layers();
}

} }
