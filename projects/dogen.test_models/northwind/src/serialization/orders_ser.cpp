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
#include "dogen/test_models/northwind/serialization/orders_ser.hpp"
#include "dogen/test_models/northwind/serialization/order_id_ser.hpp"
#include "dogen/test_models/northwind/serialization/customer_id_ser.hpp"
#include "dogen/test_models/northwind/serialization/employee_id_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::test_models::northwind::orders& v,
    const unsigned int /*version*/) {
    ar << make_nvp("order_id", v.order_id_);
    ar << make_nvp("customer_id", v.customer_id_);
    ar << make_nvp("employee_id", v.employee_id_);
    ar << make_nvp("order_date", v.order_date_);
    ar << make_nvp("required_date", v.required_date_);
    ar << make_nvp("shipped_date", v.shipped_date_);
    ar << make_nvp("ship_via", v.ship_via_);
    ar << make_nvp("freight", v.freight_);
    ar << make_nvp("ship_name", v.ship_name_);
    ar << make_nvp("ship_address", v.ship_address_);
    ar << make_nvp("ship_city", v.ship_city_);
    ar << make_nvp("ship_region", v.ship_region_);
    ar << make_nvp("ship_postal_code", v.ship_postal_code_);
    ar << make_nvp("ship_country", v.ship_country_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::test_models::northwind::orders& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("order_id", v.order_id_);
    ar >> make_nvp("customer_id", v.customer_id_);
    ar >> make_nvp("employee_id", v.employee_id_);
    ar >> make_nvp("order_date", v.order_date_);
    ar >> make_nvp("required_date", v.required_date_);
    ar >> make_nvp("shipped_date", v.shipped_date_);
    ar >> make_nvp("ship_via", v.ship_via_);
    ar >> make_nvp("freight", v.freight_);
    ar >> make_nvp("ship_name", v.ship_name_);
    ar >> make_nvp("ship_address", v.ship_address_);
    ar >> make_nvp("ship_city", v.ship_city_);
    ar >> make_nvp("ship_region", v.ship_region_);
    ar >> make_nvp("ship_postal_code", v.ship_postal_code_);
    ar >> make_nvp("ship_country", v.ship_country_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::test_models::northwind::orders& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::test_models::northwind::orders& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::test_models::northwind::orders& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::test_models::northwind::orders& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::test_models::northwind::orders& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::test_models::northwind::orders& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::test_models::northwind::orders& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::test_models::northwind::orders& v, unsigned int version);

} }
