/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_STREAMING_PAIR_HPP
#define DOGEN_UTILITY_STREAMING_PAIR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include <utility>
#include "dogen/utility/io/jsonify_io.hpp"

namespace std {

template<typename Key, typename Value>
inline ostream& operator<<(ostream& stream, const pair<Key, Value>& pair) {
    using dogen::utility::streaming::jsonify;
    stream << "{ \"key\": " << jsonify(pair.first)
           << ", \"value\": " << jsonify(pair.second) << " }";
    return(stream);
}

}

#endif
