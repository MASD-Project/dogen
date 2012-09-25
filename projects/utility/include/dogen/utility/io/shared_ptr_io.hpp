/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_STREAMING_SHARED_PTR_HPP
#define DOGEN_UTILITY_STREAMING_SHARED_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include <ostream>
#include "dogen/utility/io/jsonify_io.hpp"

namespace boost {

template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const shared_ptr<T>& pointer) {
    using dogen::utility::streaming::jsonify;
    if (pointer)
        stream << *pointer;
    else
        stream << "\"shared_ptr\": \"empty shared pointer\"";
    return(stream);
}

}

#endif
