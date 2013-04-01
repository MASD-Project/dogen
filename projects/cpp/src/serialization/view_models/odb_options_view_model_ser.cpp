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
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include "dogen/cpp/serialization/view_models/odb_options_view_model_ser.hpp"

#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::cpp::view_models::odb_options_view_model& v,
    const unsigned int /*version*/) {
    ar << make_nvp("model_name", v.model_name_);
    ar << make_nvp("product_name", v.product_name_);
    ar << make_nvp("file_path", v.file_path_.generic_string());
    ar << make_nvp("file_name", v.file_name_);
    ar << make_nvp("odb_folder", v.odb_folder_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::cpp::view_models::odb_options_view_model& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("model_name", v.model_name_);
    ar >> make_nvp("product_name", v.product_name_);
    std::string file_path_tmp;
    ar >> make_nvp("file_path", file_path_tmp);
    v.file_path_ = file_path_tmp;
    ar >> make_nvp("file_name", v.file_name_);
    ar >> make_nvp("odb_folder", v.odb_folder_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);

#ifdef __linux__
template void save(eos::portable_oarchive& ar, const dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);
template void load(eos::portable_iarchive& ar, dogen::cpp::view_models::odb_options_view_model& v, unsigned int version);
#endif

} }