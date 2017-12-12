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
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include "dogen/test_models/northwind/serialization/employees_ser.hpp"
#include "dogen/test_models/northwind/serialization/employee_id_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::test_models::northwind::employees& v,
    const unsigned int /*version*/) {
    ar << make_nvp("employee_id", v.employee_id_);
    ar << make_nvp("last_name", v.last_name_);
    ar << make_nvp("first_name", v.first_name_);
    ar << make_nvp("title", v.title_);
    ar << make_nvp("title_of_courtesy", v.title_of_courtesy_);
    ar << make_nvp("birth_date", v.birth_date_);
    ar << make_nvp("hire_date", v.hire_date_);
    ar << make_nvp("address", v.address_);
    ar << make_nvp("city", v.city_);
    ar << make_nvp("region", v.region_);
    ar << make_nvp("postal_code", v.postal_code_);
    ar << make_nvp("country", v.country_);
    ar << make_nvp("home_phone", v.home_phone_);
    ar << make_nvp("extension", v.extension_);
    ar << make_nvp("photo", v.photo_);
    ar << make_nvp("notes", v.notes_);
    ar << make_nvp("reports_to", v.reports_to_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::test_models::northwind::employees& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("employee_id", v.employee_id_);
    ar >> make_nvp("last_name", v.last_name_);
    ar >> make_nvp("first_name", v.first_name_);
    ar >> make_nvp("title", v.title_);
    ar >> make_nvp("title_of_courtesy", v.title_of_courtesy_);
    ar >> make_nvp("birth_date", v.birth_date_);
    ar >> make_nvp("hire_date", v.hire_date_);
    ar >> make_nvp("address", v.address_);
    ar >> make_nvp("city", v.city_);
    ar >> make_nvp("region", v.region_);
    ar >> make_nvp("postal_code", v.postal_code_);
    ar >> make_nvp("country", v.country_);
    ar >> make_nvp("home_phone", v.home_phone_);
    ar >> make_nvp("extension", v.extension_);
    ar >> make_nvp("photo", v.photo_);
    ar >> make_nvp("notes", v.notes_);
    ar >> make_nvp("reports_to", v.reports_to_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::test_models::northwind::employees& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::test_models::northwind::employees& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::test_models::northwind::employees& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::test_models::northwind::employees& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::test_models::northwind::employees& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::test_models::northwind::employees& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::test_models::northwind::employees& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::test_models::northwind::employees& v, unsigned int version);

} }
