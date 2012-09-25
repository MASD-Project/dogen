/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_COMPRESSED_IO_PACKAGE1_FIRST_CLASS_IO_HPP
#define DOGEN_COMPRESSED_IO_PACKAGE1_FIRST_CLASS_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/compressed/domain/package1/first_class.hpp"

namespace dogen {
namespace compressed {
namespace package1 {

std::ostream&
operator<<(std::ostream& stream,
    dogen::compressed::package1::first_class value);

} } }

#endif
