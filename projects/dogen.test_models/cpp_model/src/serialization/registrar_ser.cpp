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
#include "dogen/test_models/cpp_model/serialization/registrar_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/descendant2_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/descendant3_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/non_final_leaf_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_6/child_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_8/child_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_9/child_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_of_a_child1_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_of_a_child2_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/further_inherited_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_via_settings_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_with_members_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/move_ctor_descendant_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_without_members_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/move_ctor_empty_descendant_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_6/child_via_settings_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_8/child_via_settings_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_9/child_via_settings_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/second_child_without_members_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

template<typename Archive>
void register_types(Archive& ar) {
    ar.template register_type<dogen::test_models::cpp_model::child_of_a_child1>();
    ar.template register_type<dogen::test_models::cpp_model::child_of_a_child2>();
    ar.template register_type<dogen::test_models::cpp_model::child_via_settings>();
    ar.template register_type<dogen::test_models::cpp_model::child_with_members>();
    ar.template register_type<dogen::test_models::cpp_model::child_without_members>();
    ar.template register_type<dogen::test_models::cpp_model::descendant2>();
    ar.template register_type<dogen::test_models::cpp_model::descendant3>();
    ar.template register_type<dogen::test_models::cpp_model::further_inherited>();
    ar.template register_type<dogen::test_models::cpp_model::move_ctor_descendant>();
    ar.template register_type<dogen::test_models::cpp_model::move_ctor_empty_descendant>();
    ar.template register_type<dogen::test_models::cpp_model::non_final_leaf>();
    ar.template register_type<dogen::test_models::cpp_model::package_6::child>();
    ar.template register_type<dogen::test_models::cpp_model::package_6::child_via_settings>();
    ar.template register_type<dogen::test_models::cpp_model::package_8::child>();
    ar.template register_type<dogen::test_models::cpp_model::package_8::child_via_settings>();
    ar.template register_type<dogen::test_models::cpp_model::package_9::child>();
    ar.template register_type<dogen::test_models::cpp_model::package_9::child_via_settings>();
    ar.template register_type<dogen::test_models::cpp_model::second_child_without_members>();
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
