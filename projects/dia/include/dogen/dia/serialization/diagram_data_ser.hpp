/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_SERIALIZATION_DIAGRAM_DATA_HPP
#define DOGEN_DIA_SERIALIZATION_DIAGRAM_DATA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include "dogen/dia/domain/diagram_data.hpp"
#include "dogen/dia/serialization/attribute_ser.hpp"

namespace dogen {
namespace dia {
namespace serialization {
namespace detail {

class diagram_data_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::dia::diagram_data& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;
        archive & make_nvp("attributes", value.attributes_);
    }
};

} } } }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::dia::diagram_data& value,
    const unsigned int version) {
    dogen::dia::serialization::detail::diagram_data_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
