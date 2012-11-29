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
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "dogen/trivial_inheritance/serialization/child_of_a_child1_ser.hpp"
#include "dogen/trivial_inheritance/serialization/child_of_a_child2_ser.hpp"
#include "dogen/trivial_inheritance/serialization/child_with_members_ser.hpp"
#include "dogen/trivial_inheritance/serialization/child_without_members_ser.hpp"
#include "dogen/trivial_inheritance/serialization/pkg1/child_ser.hpp"
#include "dogen/trivial_inheritance/serialization/pkg3/child_ser.hpp"
#include "dogen/trivial_inheritance/serialization/pkg4/child_ser.hpp"
#include "dogen/trivial_inheritance/serialization/second_child_without_members_ser.hpp"
#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

namespace dogen {
namespace trivial_inheritance {

template<typename Archive>
void register_types(Archive& ar) {
    ar.template register_type<dogen::trivial_inheritance::child_of_a_child1>();
    ar.template register_type<dogen::trivial_inheritance::child_of_a_child2>();
    ar.template register_type<dogen::trivial_inheritance::child_with_members>();
    ar.template register_type<dogen::trivial_inheritance::child_without_members>();
    ar.template register_type<dogen::trivial_inheritance::pkg1::child>();
    ar.template register_type<dogen::trivial_inheritance::pkg3::child>();
    ar.template register_type<dogen::trivial_inheritance::pkg4::child>();
    ar.template register_type<dogen::trivial_inheritance::second_child_without_members>();
}

template void register_types(boost::archive::polymorphic_oarchive& ar);
template void register_types(boost::archive::polymorphic_iarchive& ar);

template void register_types(boost::archive::text_oarchive& ar);
template void register_types(boost::archive::text_iarchive& ar);

template void register_types(boost::archive::binary_oarchive& ar);
template void register_types(boost::archive::binary_iarchive& ar);

template void register_types(boost::archive::xml_oarchive& ar);
template void register_types(boost::archive::xml_iarchive& ar);

#ifdef __linux__
template void register_types(eos::portable_oarchive& ar);
template void register_types(eos::portable_iarchive& ar);
#endif

} }