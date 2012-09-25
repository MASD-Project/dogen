/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_SERIALIZATION_STRING_HPP
#define DOGEN_DIA_SERIALIZATION_STRING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include "dogen/dia/domain/string.hpp"

namespace dogen {
namespace dia {
namespace serialization {
namespace detail {

class string_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::dia::string& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;
        archive & make_nvp("value", value.value_);
    }
};

} } } }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::dia::string& value,
    const unsigned int version) {
    dogen::dia::serialization::detail::string_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
