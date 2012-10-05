/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SPLIT_PROJECT_SERIALIZATION_PACKAGE_A_CLASS_SER_HPP
#define DOGEN_SPLIT_PROJECT_SERIALIZATION_PACKAGE_A_CLASS_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/nvp.hpp>
#include "dogen/split_project/domain/package/a_class.hpp"
#include "dogen/split_project/serialization/versioned_key_ser.hpp"

namespace dogen {
namespace split_project {
namespace package {

class a_class_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::split_project::package::a_class& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;

        archive & make_nvp("versioned_key", value.versioned_key_);
    }
};

} } }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::split_project::package::a_class& value,
    const unsigned int version) {
    dogen::split_project::package::a_class_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
