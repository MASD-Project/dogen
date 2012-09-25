/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DISABLE_CMAKELISTS_IO_PACKAGE1_FIRST_CLASS_IO_HPP
#define DOGEN_DISABLE_CMAKELISTS_IO_PACKAGE1_FIRST_CLASS_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/disable_cmakelists/domain/package1/first_class.hpp"

namespace dogen {
namespace disable_cmakelists {
namespace package1 {

std::ostream&
operator<<(std::ostream& stream,
    dogen::disable_cmakelists::package1::first_class value);

} } }

#endif
