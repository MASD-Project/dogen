/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_STREAMING_HEX_DUMPER_HPP
#define DOGEN_UTILITY_STREAMING_HEX_DUMPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>

namespace dogen {
namespace utility {
namespace streaming {

void
hex_dumper(std::ostream& stream, const char* buffer, const unsigned int size);

} } }

#endif
