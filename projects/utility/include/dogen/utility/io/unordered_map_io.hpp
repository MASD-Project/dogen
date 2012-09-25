/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_IO_MAP_HPP
#define DOGEN_UTILITY_IO_MAP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include <unordered_map>
#include "dogen/utility/io/pair_io.hpp"

namespace std {

template<typename Key, typename Value>
inline ostream&
operator<<(ostream& stream, const unordered_map<Key, Value>& map) {
    stream << "[ ";
    for(auto i(map.begin()); i != map.end(); ++i) {
        if (i != map.begin())
            stream << ", ";
        stream << (*i);
    }
    stream << " ]";
    return(stream);
}

}

#endif
