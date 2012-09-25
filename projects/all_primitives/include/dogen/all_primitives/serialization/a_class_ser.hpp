/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_ALL_PRIMITIVES_SERIALIZATION_A_CLASS_SER_HPP
#define DOGEN_ALL_PRIMITIVES_SERIALIZATION_A_CLASS_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/nvp.hpp>
#include "dogen/all_primitives/domain/a_class.hpp"
#include "dogen/all_primitives/serialization/versioned_key_ser.hpp"

namespace dogen {
namespace all_primitives {

class a_class_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::all_primitives::a_class& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;

        archive & make_nvp("bool_property", value.bool_property_);
        archive & make_nvp("char_property", value.char_property_);
        archive & make_nvp("uchar_property", value.uchar_property_);
        archive & make_nvp("int_property", value.int_property_);
        archive & make_nvp("uint_property", value.uint_property_);
        archive & make_nvp("long_property", value.long_property_);
        archive & make_nvp("ulong_property", value.ulong_property_);
        archive & make_nvp("long_long_property", value.long_long_property_);
        archive & make_nvp("ulong_long_property", value.ulong_long_property_);
        archive & make_nvp("short_property", value.short_property_);
        archive & make_nvp("ushort_property", value.ushort_property_);
        archive & make_nvp("versioned_key", value.versioned_key_);
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::all_primitives::a_class& value,
    const unsigned int version) {
    dogen::all_primitives::a_class_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
