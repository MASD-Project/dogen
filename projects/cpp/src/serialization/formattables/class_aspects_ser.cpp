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
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/cpp/serialization/formattables/class_aspects_ser.hpp"


namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::cpp::formattables::class_aspects& v,
    const unsigned int /*version*/) {
    ar << make_nvp("enable_complete_constructor", v.enable_complete_constructor_);
    ar << make_nvp("generate_defaulted_functions", v.generate_defaulted_functions_);
    ar << make_nvp("generate_explicit_default_constructor", v.generate_explicit_default_constructor_);
    ar << make_nvp("generate_explicit_move_constructor", v.generate_explicit_move_constructor_);
    ar << make_nvp("generate_explicit_destructor", v.generate_explicit_destructor_);
    ar << make_nvp("destructor_is_pure_virtual", v.destructor_is_pure_virtual_);
    ar << make_nvp("generate_explicit_assignment_operator", v.generate_explicit_assignment_operator_);
    ar << make_nvp("generate_complete_constructor", v.generate_complete_constructor_);
    ar << make_nvp("generate_equality", v.generate_equality_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::cpp::formattables::class_aspects& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("enable_complete_constructor", v.enable_complete_constructor_);
    ar >> make_nvp("generate_defaulted_functions", v.generate_defaulted_functions_);
    ar >> make_nvp("generate_explicit_default_constructor", v.generate_explicit_default_constructor_);
    ar >> make_nvp("generate_explicit_move_constructor", v.generate_explicit_move_constructor_);
    ar >> make_nvp("generate_explicit_destructor", v.generate_explicit_destructor_);
    ar >> make_nvp("destructor_is_pure_virtual", v.destructor_is_pure_virtual_);
    ar >> make_nvp("generate_explicit_assignment_operator", v.generate_explicit_assignment_operator_);
    ar >> make_nvp("generate_complete_constructor", v.generate_complete_constructor_);
    ar >> make_nvp("generate_equality", v.generate_equality_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::cpp::formattables::class_aspects& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::cpp::formattables::class_aspects& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::cpp::formattables::class_aspects& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::cpp::formattables::class_aspects& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::cpp::formattables::class_aspects& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::cpp::formattables::class_aspects& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::cpp::formattables::class_aspects& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::cpp::formattables::class_aspects& v, unsigned int version);

} }