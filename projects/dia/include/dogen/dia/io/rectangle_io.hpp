/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_IO_RECTANGLE_IO_HPP
#define DOGEN_DIA_IO_RECTANGLE_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/dia/domain/rectangle.hpp"

namespace dogen {
namespace dia {

std::ostream&
operator<<(std::ostream& stream, dogen::dia::rectangle rectangle);

} }

#endif
