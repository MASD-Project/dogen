/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/dia/domain/layer.hpp"

namespace dogen {
namespace dia {

bool layer::operator==(const dogen::dia::layer& value) const {
    return
        objects_ == value.objects() &&
        name_ == value.name() &&
        visible_ == value.visible() &&
        active_ == value.active();
}

} }
