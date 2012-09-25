/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASS_WITHOUT_PACKAGE_AND_ATTRIBUTES_IO_CLASS_1_IO_HPP
#define DOGEN_CLASS_WITHOUT_PACKAGE_AND_ATTRIBUTES_IO_CLASS_1_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/class_without_package_and_attributes/domain/class_1.hpp"

namespace dogen {
namespace class_without_package_and_attributes {

std::ostream&
operator<<(std::ostream& stream,
    dogen::class_without_package_and_attributes::class_1 value);

} }

#endif
