/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_PROTOTYPE_SERIALIZATION_REPOSITORY_SER_HPP
#define DOGEN_PROTOTYPE_SERIALIZATION_REPOSITORY_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/access.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include "dogen/utility/serialization/unordered_map.hpp"
#include "dogen/prototype/serialization/currency_ser.hpp"
#include "dogen/prototype/serialization/unversioned_key_ser.hpp"
#include "dogen/prototype/domain/repository.hpp"

namespace dogen {
namespace prototype {

class repository_serializer {
public:
    template<typename Archive>
    void serialize(Archive& ar, dogen::prototype::repository& v,
        const unsigned int /*version*/) {
        ar & v.currencies_;
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & ar, dogen::prototype::repository& v,
    const unsigned int version) {
    dogen::prototype::repository_serializer serializer;
    serializer.serialize<Archive>(ar, v, version);
}

} }

#endif
