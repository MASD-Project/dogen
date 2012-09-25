/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_TWO_LAYERS_WITH_OBJECTS_IO_PACKAGE_1_CLASS_1_IO_HPP
#define DOGEN_TWO_LAYERS_WITH_OBJECTS_IO_PACKAGE_1_CLASS_1_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/two_layers_with_objects/domain/package_1/class_1.hpp"

namespace dogen {
namespace two_layers_with_objects {
namespace package_1 {

std::ostream&
operator<<(std::ostream& stream,
    dogen::two_layers_with_objects::package_1::class_1 value);

} } }

#endif
