/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASSES_WITHOUT_PACKAGE_IO_CLASS_1_IO_HPP
#define DOGEN_CLASSES_WITHOUT_PACKAGE_IO_CLASS_1_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/classes_without_package/domain/class_1.hpp"

namespace dogen {
namespace classes_without_package {

std::ostream&
operator<<(std::ostream& stream,
    dogen::classes_without_package::class_1 value);

} }

#endif
