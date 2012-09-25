/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_SERIALIZATION_CHILD_NODE_HPP
#define DOGEN_DIA_SERIALIZATION_CHILD_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include "dogen/dia/domain/child_node.hpp"

namespace dogen {
namespace dia {
namespace serialization {
namespace detail {

class child_node_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::dia::child_node& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;
        archive & make_nvp("parent", value.parent_);
    }
};

} } } }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::dia::child_node& value,
    const unsigned int version) {
    dogen::dia::serialization::detail::child_node_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
