/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_TRIVIAL_INHERITANCE_SERIALIZATION_SECOND_CHILD_WITHOUT_MEMBERS_SER_HPP
#define DOGEN_TRIVIAL_INHERITANCE_SERIALIZATION_SECOND_CHILD_WITHOUT_MEMBERS_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>
#include "dogen/trivial_inheritance/domain/second_child_without_members.hpp"
#include "dogen/trivial_inheritance/serialization/parent_with_members_ser.hpp"
#include "dogen/trivial_inheritance/serialization/versioned_key_ser.hpp"

namespace dogen {
namespace trivial_inheritance {

class second_child_without_members_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::trivial_inheritance::second_child_without_members& value,
        const unsigned int /*version*/) {
        using boost::serialization::base_object;
        archive & base_object<parent_with_members>(value);
    }
};

} }

BOOST_CLASS_EXPORT(dogen::trivial_inheritance::second_child_without_members);

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::trivial_inheritance::second_child_without_members& value,
    const unsigned int version) {
    dogen::trivial_inheritance::second_child_without_members_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
