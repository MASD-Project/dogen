/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_STREAMING_SET_HPP
#define DOGEN_UTILITY_STREAMING_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <ostream>
#include "dogen/utility/io/jsonify_io.hpp"

namespace std {

template<typename Key>
inline ostream& operator<<(ostream& stream, const set<Key>& value) {
    stream << "[ ";
    for(typename std::set<Key>::const_iterator i(value.begin());
        i != value.end();
        ++i) {
        if (i != value.begin()) stream << ", ";
        stream << dogen::utility::streaming::jsonify(*i);
    }
    stream << " ]";
    return(stream);
}

}

#endif
