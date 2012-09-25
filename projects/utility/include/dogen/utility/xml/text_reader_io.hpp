/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_XML_TEXT_READER_IO_HPP
#define DOGEN_UTILITY_XML_TEXT_READER_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/utility/xml/text_reader.hpp"

namespace dogen {
namespace utility {
namespace xml {

std::ostream& operator<<(std::ostream& stream, const text_reader& value);

} } }

#endif
