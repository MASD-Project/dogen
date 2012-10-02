/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_STAND_ALONE_CLASS_IO_UNVERSIONED_KEY_IO_HPP
#define DOGEN_STAND_ALONE_CLASS_IO_UNVERSIONED_KEY_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/stand_alone_class/domain/unversioned_key.hpp"

namespace dogen {
namespace stand_alone_class {

std::ostream&
operator<<(std::ostream& stream,
    dogen::stand_alone_class::unversioned_key value);

} }

#endif
