/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SPLIT_PROJECT_IO_PACKAGE_A_CLASS_IO_HPP
#define DOGEN_SPLIT_PROJECT_IO_PACKAGE_A_CLASS_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/split_project/domain/package/a_class.hpp"

namespace dogen {
namespace split_project {
namespace package {

std::ostream&
operator<<(std::ostream& stream,
    dogen::split_project::package::a_class value);

} } }

#endif
