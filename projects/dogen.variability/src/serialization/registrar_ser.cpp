/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.variability/serialization/registrar_ser.hpp"
#include "dogen.variability/serialization/entities/text_ser.hpp"
#include "dogen.variability/serialization/entities/number_ser.hpp"
#include "dogen.variability/serialization/entities/boolean_ser.hpp"
#include "dogen.variability/serialization/entities/feature_ser.hpp"
#include "dogen.variability/serialization/entities/profile_ser.hpp"
#include "dogen.variability/serialization/entities/configuration_ser.hpp"
#include "dogen.variability/serialization/entities/key_value_pair_ser.hpp"
#include "dogen.variability/serialization/entities/comma_separated_ser.hpp"
#include "dogen.variability/serialization/entities/text_collection_ser.hpp"
#include "dogen.variability/serialization/entities/feature_template_ser.hpp"
#include "dogen.variability/serialization/entities/profile_template_ser.hpp"
#include "dogen.variability/serialization/entities/configuration_point_ser.hpp"
#include "dogen.variability/serialization/entities/comma_separated_collection_ser.hpp"
#include "dogen.variability/serialization/entities/configuration_point_template_ser.hpp"

namespace dogen::variability {

template<typename Archive>
void registrar::register_types(Archive& ar) {
    ar.template register_type<dogen::variability::entities::boolean>();
    ar.template register_type<dogen::variability::entities::comma_separated>();
    ar.template register_type<dogen::variability::entities::comma_separated_collection>();
    ar.template register_type<dogen::variability::entities::configuration>();
    ar.template register_type<dogen::variability::entities::configuration_point>();
    ar.template register_type<dogen::variability::entities::configuration_point_template>();
    ar.template register_type<dogen::variability::entities::feature>();
    ar.template register_type<dogen::variability::entities::feature_template>();
    ar.template register_type<dogen::variability::entities::key_value_pair>();
    ar.template register_type<dogen::variability::entities::number>();
    ar.template register_type<dogen::variability::entities::profile>();
    ar.template register_type<dogen::variability::entities::profile_template>();
    ar.template register_type<dogen::variability::entities::text>();
    ar.template register_type<dogen::variability::entities::text_collection>();
}

template void registrar::register_types(boost::archive::polymorphic_oarchive& ar);
template void registrar::register_types(boost::archive::polymorphic_iarchive& ar);

template void registrar::register_types(boost::archive::text_oarchive& ar);
template void registrar::register_types(boost::archive::text_iarchive& ar);

template void registrar::register_types(boost::archive::binary_oarchive& ar);
template void registrar::register_types(boost::archive::binary_iarchive& ar);

template void registrar::register_types(boost::archive::xml_oarchive& ar);
template void registrar::register_types(boost::archive::xml_iarchive& ar);

}
