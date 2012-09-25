/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_SERIALIZATION_ARCHIVE_TYPES_HPP
#define DOGEN_UTILITY_SERIALIZATION_ARCHIVE_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>

namespace dogen {
namespace utility {
namespace serialization {

/**
 * @brief Boost serialisation archive types.
 */
enum class archive_types : unsigned int {
    invalid = 0,
    xml = 1, ///< Boost XML archive
    text = 2, ///< Boost plain-text archive
    binary = 3 ///<  Boost binary archive
};

std::ostream& operator<<(std::ostream& stream, archive_types value);

} } }

#endif
