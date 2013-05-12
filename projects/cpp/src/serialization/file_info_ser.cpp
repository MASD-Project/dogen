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
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/string.hpp>
#include "dogen/config/serialization/cpp_facet_types_ser.hpp"
#include "dogen/cpp/serialization/aspect_types_ser.hpp"
#include "dogen/cpp/serialization/class_info_ser.hpp"
#include "dogen/cpp/serialization/enumeration_info_ser.hpp"
#include "dogen/cpp/serialization/exception_info_ser.hpp"
#include "dogen/cpp/serialization/file_info_ser.hpp"
#include "dogen/cpp/serialization/file_types_ser.hpp"
#include "dogen/cpp/serialization/namespace_info_ser.hpp"
#include "dogen/cpp/serialization/registrar_info_ser.hpp"
#include "dogen/cpp/serialization/visitor_info_ser.hpp"
#include "dogen/sml/serialization/category_types_ser.hpp"
#include "dogen/sml/serialization/meta_types_ser.hpp"

#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::cpp::file_info& v,
    const unsigned int /*version*/) {
    ar << make_nvp("facet_type", v.facet_type_);
    ar << make_nvp("file_type", v.file_type_);
    ar << make_nvp("aspect_type", v.aspect_type_);
    ar << make_nvp("category_type", v.category_type_);
    ar << make_nvp("meta_type", v.meta_type_);
    ar << make_nvp("class_info", v.class_info_);
    ar << make_nvp("enumeration_info", v.enumeration_info_);
    ar << make_nvp("exception_info", v.exception_info_);
    ar << make_nvp("registrar_info", v.registrar_info_);
    ar << make_nvp("header_guard", v.header_guard_);
    ar << make_nvp("system_includes", v.system_includes_);
    ar << make_nvp("user_includes", v.user_includes_);
    ar << make_nvp("file_path", v.file_path_.generic_string());
    ar << make_nvp("namespace_info", v.namespace_info_);
    ar << make_nvp("visitor_info", v.visitor_info_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::cpp::file_info& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("facet_type", v.facet_type_);
    ar >> make_nvp("file_type", v.file_type_);
    ar >> make_nvp("aspect_type", v.aspect_type_);
    ar >> make_nvp("category_type", v.category_type_);
    ar >> make_nvp("meta_type", v.meta_type_);
    ar >> make_nvp("class_info", v.class_info_);
    ar >> make_nvp("enumeration_info", v.enumeration_info_);
    ar >> make_nvp("exception_info", v.exception_info_);
    ar >> make_nvp("registrar_info", v.registrar_info_);
    ar >> make_nvp("header_guard", v.header_guard_);
    ar >> make_nvp("system_includes", v.system_includes_);
    ar >> make_nvp("user_includes", v.user_includes_);
    std::string file_path_tmp;
    ar >> make_nvp("file_path", file_path_tmp);
    v.file_path_ = file_path_tmp;
    ar >> make_nvp("namespace_info", v.namespace_info_);
    ar >> make_nvp("visitor_info", v.visitor_info_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::cpp::file_info& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::cpp::file_info& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::cpp::file_info& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::cpp::file_info& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::cpp::file_info& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::cpp::file_info& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::cpp::file_info& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::cpp::file_info& v, unsigned int version);

#ifdef __linux__
template void save(eos::portable_oarchive& ar, const dogen::cpp::file_info& v, unsigned int version);
template void load(eos::portable_iarchive& ar, dogen::cpp::file_info& v, unsigned int version);
#endif

} }