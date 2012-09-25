/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DISABLE_CMAKELISTS_IO_UNVERSIONED_KEY_IO_HPP
#define DOGEN_DISABLE_CMAKELISTS_IO_UNVERSIONED_KEY_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/disable_cmakelists/domain/unversioned_key.hpp"

namespace dogen {
namespace disable_cmakelists {

std::ostream&
operator<<(std::ostream& stream,
    dogen::disable_cmakelists::unversioned_key value);

} }

#endif
