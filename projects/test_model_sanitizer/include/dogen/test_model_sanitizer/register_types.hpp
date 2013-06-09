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
#ifndef DOGEN_TEST_MODEL_SANITIZER_REGISTER_TYPES_HPP
#define DOGEN_TEST_MODEL_SANITIZER_REGISTER_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/all_primitives/serialization/registrar_ser.hpp"
#include "dogen/boost_model/serialization/registrar_ser.hpp"
#include "dogen/classes_in_a_package/serialization/registrar_ser.hpp"
#include "dogen/classes_inout_package/serialization/registrar_ser.hpp"
#include "dogen/classes_without_package/serialization/registrar_ser.hpp"
#include "dogen/class_in_a_package/serialization/registrar_ser.hpp"
#include "dogen/class_without_package/serialization/registrar_ser.hpp"
#include "dogen/compressed/serialization/registrar_ser.hpp"
#include "dogen/disable_cmakelists/serialization/registrar_ser.hpp"
#include "dogen/disable_facet_folders/registrar_ser.hpp"
#include "dogen/disable_full_ctor/serialization/registrar_ser.hpp"
#include "dogen/dmp/serialization/registrar_ser.hpp"
#include "dogen/enumeration/serialization/registrar_ser.hpp"
#include "dogen/split_project/serialization/registrar_ser.hpp"
#include "dogen/stand_alone_class/serialization/registrar_ser.hpp"
#include "dogen/std_model/serialization/registrar_ser.hpp"
#include "dogen/enable_facet_serialization/serialization/registrar_ser.hpp"
#include "dogen/trivial_association/serialization/registrar_ser.hpp"
#include "dogen/trivial_inheritance/serialization/registrar_ser.hpp"
#include "dogen/two_layers_with_objects/serialization/registrar_ser.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::all_primitives::register_types<Archive>(ar);
    dogen::boost_model::register_types<Archive>(ar);
    dogen::classes_in_a_package::register_types<Archive>(ar);
    dogen::classes_inout_package::register_types<Archive>(ar);
    dogen::classes_without_package::register_types<Archive>(ar);
    dogen::class_in_a_package::register_types<Archive>(ar);
    dogen::class_without_package::register_types<Archive>(ar);
    dogen::compressed::register_types<Archive>(ar);
    dogen::disable_cmakelists::register_types<Archive>(ar);
    dogen::disable_facet_folders::register_types<Archive>(ar);
    dogen::disable_full_ctor::register_types<Archive>(ar);
    dogen::dmp::register_types<Archive>(ar);
    dogen::enumeration::register_types<Archive>(ar);
    dogen::split_project::register_types<Archive>(ar);
    dogen::stand_alone_class::register_types<Archive>(ar);
    dogen::std_model::register_types<Archive>(ar);
    dogen::enable_facet_serialization::register_types<Archive>(ar);
    dogen::trivial_association::register_types<Archive>(ar);
    dogen::trivial_inheritance::register_types<Archive>(ar);
    dogen::two_layers_with_objects::register_types<Archive>(ar);
}

#endif
