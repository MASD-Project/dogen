/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_ENABLE_FACET_IO_IO_PACKAGE1_FIRST_CLASS_IO_HPP
#define DOGEN_ENABLE_FACET_IO_IO_PACKAGE1_FIRST_CLASS_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/enable_facet_io/domain/package1/first_class.hpp"

namespace dogen {
namespace enable_facet_io {
namespace package1 {

std::ostream&
operator<<(std::ostream& stream,
    dogen::enable_facet_io::package1::first_class value);

} } }

#endif
