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
#include "dogen/om/serialization/cmake_add_library_ser.hpp"
#include "dogen/om/serialization/cmake_file_ser.hpp"
#include "dogen/om/serialization/cmake_install_ser.hpp"
#include "dogen/om/serialization/cmake_set_target_properties_ser.hpp"
#include "dogen/om/serialization/cpp_argument_ser.hpp"
#include "dogen/om/serialization/cpp_class_ser.hpp"
#include "dogen/om/serialization/cpp_enumeration_ser.hpp"
#include "dogen/om/serialization/cpp_file_ser.hpp"
#include "dogen/om/serialization/cpp_function_ser.hpp"
#include "dogen/om/serialization/cpp_header_guard_ser.hpp"
#include "dogen/om/serialization/cpp_ifdef_ser.hpp"
#include "dogen/om/serialization/cpp_include_directive_ser.hpp"
#include "dogen/om/serialization/cpp_member_function_ser.hpp"
#include "dogen/om/serialization/cpp_member_variable_ser.hpp"
#include "dogen/om/serialization/cpp_namespace_ser.hpp"
#include "dogen/om/serialization/cpp_pragma_ser.hpp"
#include "dogen/om/serialization/cpp_typedef_ser.hpp"
#include "dogen/om/serialization/cpp_variable_ser.hpp"
#include "dogen/om/serialization/odb_database_option_ser.hpp"
#include "dogen/om/serialization/odb_guard_prefix_option_ser.hpp"
#include "dogen/om/serialization/odb_include_regex_option_ser.hpp"
#include "dogen/om/serialization/odb_options_file_ser.hpp"
#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

namespace dogen {
namespace om {

template<typename Archive>
void register_types(Archive& ar) {
    ar.template register_type<dogen::om::cmake_add_library>();
    ar.template register_type<dogen::om::cmake_file>();
    ar.template register_type<dogen::om::cmake_install>();
    ar.template register_type<dogen::om::cmake_set_target_properties>();
    ar.template register_type<dogen::om::cpp_argument>();
    ar.template register_type<dogen::om::cpp_class>();
    ar.template register_type<dogen::om::cpp_enumeration>();
    ar.template register_type<dogen::om::cpp_file>();
    ar.template register_type<dogen::om::cpp_function>();
    ar.template register_type<dogen::om::cpp_header_guard>();
    ar.template register_type<dogen::om::cpp_ifdef>();
    ar.template register_type<dogen::om::cpp_include_directive>();
    ar.template register_type<dogen::om::cpp_member_function>();
    ar.template register_type<dogen::om::cpp_member_variable>();
    ar.template register_type<dogen::om::cpp_namespace>();
    ar.template register_type<dogen::om::cpp_pragma>();
    ar.template register_type<dogen::om::cpp_typedef>();
    ar.template register_type<dogen::om::cpp_variable>();
    ar.template register_type<dogen::om::odb_database_option>();
    ar.template register_type<dogen::om::odb_guard_prefix_option>();
    ar.template register_type<dogen::om::odb_include_regex_option>();
    ar.template register_type<dogen::om::odb_options_file>();
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