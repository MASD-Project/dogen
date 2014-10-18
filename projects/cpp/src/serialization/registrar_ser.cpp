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
#include "dogen/config/serialization/registrar_ser.hpp"
#include "dogen/cpp/serialization/class_info_ser.hpp"
#include "dogen/cpp/serialization/concept_ser.hpp"
#include "dogen/cpp/serialization/enum_info_ser.hpp"
#include "dogen/cpp/serialization/exception_info_ser.hpp"
#include "dogen/cpp/serialization/namespace_info_ser.hpp"
#include "dogen/cpp/serialization/new_class_info_ser.hpp"
#include "dogen/cpp/serialization/primitive_ser.hpp"
#include "dogen/cpp/serialization/registrar_info_ser.hpp"
#include "dogen/cpp/serialization/visitor_info_ser.hpp"
#include "dogen/sml/serialization/registrar_ser.hpp"

namespace dogen {
namespace cpp {

template<typename Archive>
void register_types(Archive& ar) {
    sml::register_types(ar);
    config::register_types(ar);

    ar.template register_type<dogen::cpp::class_info>();
    ar.template register_type<dogen::cpp::concept>();
    ar.template register_type<dogen::cpp::enum_info>();
    ar.template register_type<dogen::cpp::exception_info>();
    ar.template register_type<dogen::cpp::namespace_info>();
    ar.template register_type<dogen::cpp::new_class_info>();
    ar.template register_type<dogen::cpp::primitive>();
    ar.template register_type<dogen::cpp::registrar_info>();
    ar.template register_type<dogen::cpp::visitor_info>();
}

template void register_types(boost::archive::polymorphic_oarchive& ar);
template void register_types(boost::archive::polymorphic_iarchive& ar);

template void register_types(boost::archive::text_oarchive& ar);
template void register_types(boost::archive::text_iarchive& ar);

template void register_types(boost::archive::binary_oarchive& ar);
template void register_types(boost::archive::binary_iarchive& ar);

template void register_types(boost::archive::xml_oarchive& ar);
template void register_types(boost::archive::xml_iarchive& ar);


} }