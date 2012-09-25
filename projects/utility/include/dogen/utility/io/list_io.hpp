/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_STREAMING_LIST_HPP
#define DOGEN_UTILITY_STREAMING_LIST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <ostream>
#include "dogen/utility/io/jsonify_io.hpp"

namespace std {

template<typename Containee>
inline ostream& operator<<(ostream& stream, const list<Containee>& list) {
    stream << "[ ";
    for(typename std::list<Containee>::const_iterator i(list.begin());
        i != list.end();
        ++i) {
        if (i != list.begin()) stream << ", ";
        stream << dogen::utility::streaming::jsonify(*i);
    }
    stream << " ]";
    return(stream);
}

}

#endif
