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
#include "dogen/yarn/serialization/registrar_ser.hpp"
#include "dogen.options/serialization/registrar_ser.hpp"
#include "dogen.probing/serialization/registrar_ser.hpp"
#include "dogen.formatters/serialization/registrar_ser.hpp"
#include "dogen.annotations/serialization/registrar_ser.hpp"
#include "dogen.quilt.csharp/serialization/registrar_ser.hpp"
#include "dogen.quilt.csharp/serialization/fabric/assistant_ser.hpp"
#include "dogen.quilt.csharp/serialization/fabric/assembly_info_ser.hpp"
#include "dogen.quilt.csharp/serialization/fabric/visual_studio_project_ser.hpp"
#include "dogen.quilt.csharp/serialization/fabric/visual_studio_solution_ser.hpp"

namespace dogen {
namespace quilt {
namespace csharp {

template<typename Archive>
void register_types(Archive& ar) {
    dogen::annotations::register_types(ar);
    dogen::probing::register_types(ar);
    dogen::formatters::register_types(ar);
    dogen::options::register_types(ar);
    dogen::yarn::register_types(ar);

    ar.template register_type<dogen::quilt::csharp::fabric::assembly_info>();
    ar.template register_type<dogen::quilt::csharp::fabric::assistant>();
    ar.template register_type<dogen::quilt::csharp::fabric::visual_studio_project>();
    ar.template register_type<dogen::quilt::csharp::fabric::visual_studio_solution>();
}

template void register_types(boost::archive::polymorphic_oarchive& ar);
template void register_types(boost::archive::polymorphic_iarchive& ar);

template void register_types(boost::archive::text_oarchive& ar);
template void register_types(boost::archive::text_iarchive& ar);

template void register_types(boost::archive::binary_oarchive& ar);
template void register_types(boost::archive::binary_iarchive& ar);

template void register_types(boost::archive::xml_oarchive& ar);
template void register_types(boost::archive::xml_iarchive& ar);

} } }
