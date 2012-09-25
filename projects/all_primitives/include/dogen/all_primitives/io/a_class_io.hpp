/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_ALL_PRIMITIVES_IO_A_CLASS_IO_HPP
#define DOGEN_ALL_PRIMITIVES_IO_A_CLASS_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/all_primitives/domain/a_class.hpp"

namespace dogen {
namespace all_primitives {

std::ostream&
operator<<(std::ostream& stream,
    dogen::all_primitives::a_class value);

} }

#endif
