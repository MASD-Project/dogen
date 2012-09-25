/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_STREAMING_VECTOR_HPP
#define DOGEN_UTILITY_STREAMING_VECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <ostream>
#include "dogen/utility/io/jsonify_io.hpp"

namespace std {

template<typename Containee>
inline ostream& operator<<(ostream& stream, const vector<Containee>& vector) {
    stream << "[ ";
    for(typename std::vector<Containee>::const_iterator i(vector.begin());
        i != vector.end();
        ++i) {
        if (i != vector.begin()) stream << ", ";
        stream << dogen::utility::streaming::jsonify(*i);
    }
    stream << " ]";
    return(stream);
}

}

#endif
