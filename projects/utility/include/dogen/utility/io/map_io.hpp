/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_STREAMING_MAP_HPP
#define DOGEN_UTILITY_STREAMING_MAP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <ostream>
#include "dogen/utility/io/pair_io.hpp"

namespace std {

template<typename Key, typename Value>
inline ostream& operator<<(ostream& stream, const map<Key, Value>& map) {
    stream << "[ ";
    for(typename std::map<Key, Value>::const_iterator i(map.begin());
        i != map.end();
        ++i) {
        if (i != map.begin()) stream << ", ";
        stream << (*i);
    }
    stream << " ]";
    return(stream);
}

}

#endif
