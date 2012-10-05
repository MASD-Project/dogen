/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DMP_IO_VERSIONED_KEY_IO_HPP
#define DOGEN_DMP_IO_VERSIONED_KEY_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/dmp/domain/versioned_key.hpp"

namespace dogen {
namespace dmp {

std::ostream&
operator<<(std::ostream& stream,
    dogen::dmp::versioned_key value);

} }

#endif
