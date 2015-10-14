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
#include <boost/throw_exception.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include "dogen/dia/serialization/registrar_ser.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/dia/test/diagram_serialization_helper.hpp"

namespace dogen {
namespace dia {
namespace test {

void diagram_serialization_helper::to_xml(std::ostream& s, const diagram& d) {
    boost::archive::xml_oarchive a(s);
    dogen::dia::register_types(a);
    a & boost::serialization::make_nvp("entity", d);
}

diagram diagram_serialization_helper::from_xml(std::istream& s) {
    boost::archive::xml_iarchive a(s);
    dogen::dia::register_types(a);
    diagram r;
    a & boost::serialization::make_nvp("entity", r);
    return r;
}

} } }
