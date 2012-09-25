/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_STREAMING_OPTIONAL_HPP
#define DOGEN_UTILITY_STREAMING_OPTIONAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include <boost/optional.hpp>
#include "dogen/utility/io/jsonify_io.hpp"

namespace std {

template<typename T>
inline ostream&
operator<<(ostream& stream, const boost::optional<T>& optional) {
    using dogen::utility::streaming::jsonify;
    if (optional)
        return stream << *optional;

    return stream << "\"optional\" : \"empty\"";
}

}

#endif
