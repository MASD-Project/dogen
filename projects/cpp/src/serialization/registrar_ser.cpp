/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/tack/serialization/registrar_ser.hpp"
#include "dogen/dynamic/serialization/registrar_ser.hpp"
#include "dogen/cpp/serialization/settings/odb_settings_ser.hpp"
#include "dogen/cpp/serialization/formattables/enum_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/class_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/concept_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/visitor_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/exception_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/includers_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/namespace_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/primitive_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/registrar_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/cmakelists_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/odb_options_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/forward_declarations_info_ser.hpp"

namespace dogen {
namespace cpp {

template<typename Archive>
void register_types(Archive& ar) {
    dogen::tack::register_types(ar);
    dogen::dynamic::register_types(ar);

    ar.template register_type<dogen::cpp::formattables::class_info>();
    ar.template register_type<dogen::cpp::formattables::cmakelists_info>();
    ar.template register_type<dogen::cpp::formattables::concept_info>();
    ar.template register_type<dogen::cpp::formattables::enum_info>();
    ar.template register_type<dogen::cpp::formattables::exception_info>();
    ar.template register_type<dogen::cpp::formattables::forward_declarations_info>();
    ar.template register_type<dogen::cpp::formattables::includers_info>();
    ar.template register_type<dogen::cpp::formattables::namespace_info>();
    ar.template register_type<dogen::cpp::formattables::odb_options_info>();
    ar.template register_type<dogen::cpp::formattables::primitive_info>();
    ar.template register_type<dogen::cpp::formattables::registrar_info>();
    ar.template register_type<dogen::cpp::formattables::visitor_info>();
    ar.template register_type<dogen::cpp::settings::odb_settings>();
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
