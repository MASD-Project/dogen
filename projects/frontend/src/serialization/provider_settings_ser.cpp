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
#include "dogen/frontend/serialization/provider_settings_ser.hpp"
#include "dogen/utility/serialization/path.hpp"


namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::frontend::provider_settings& v,
    const unsigned int /*version*/) {
    ar << make_nvp("save_pre_processed_input", v.save_pre_processed_input_);
    ar << make_nvp("pre_processed_input_path", v.pre_processed_input_path_.generic_string());
    ar << make_nvp("disable_model_module", v.disable_model_module_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::frontend::provider_settings& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("save_pre_processed_input", v.save_pre_processed_input_);
    std::string pre_processed_input_path_tmp;
    ar >> make_nvp("pre_processed_input_path", pre_processed_input_path_tmp);
    v.pre_processed_input_path_ = pre_processed_input_path_tmp;
    ar >> make_nvp("disable_model_module", v.disable_model_module_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::frontend::provider_settings& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::frontend::provider_settings& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::frontend::provider_settings& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::frontend::provider_settings& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::frontend::provider_settings& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::frontend::provider_settings& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::frontend::provider_settings& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::frontend::provider_settings& v, unsigned int version);

} }