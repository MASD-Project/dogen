/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_HASH_COMBINE_HPP
#define DOGEN_UTILITY_HASH_COMBINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>

namespace dogen {
namespace utility {
namespace hash {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

} } }

#endif
