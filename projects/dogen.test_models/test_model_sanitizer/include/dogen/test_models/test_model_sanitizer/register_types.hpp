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
#ifndef DOGEN_TEST_MODELS_TEST_MODEL_SANITIZER_REGISTER_TYPES_HPP
#define DOGEN_TEST_MODELS_TEST_MODEL_SANITIZER_REGISTER_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/boost_model/serialization/registrar_ser.hpp"
#include "dogen/test_models/compressed/serialization/registrar_ser.hpp"
#include "dogen/test_models/disable_cmakelists/serialization/registrar_ser.hpp"
#include "dogen/test_models/disable_facet_folders/registrar_ser.hpp"
#include "dogen/test_models/std_model/serialization/registrar_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/registrar_ser.hpp"
#include "dogen/test_models/cpp_98/serialization/registrar_ser.hpp"
#include "dogen/test_models/enable_facet_serialization/serialization/registrar_ser.hpp"
#include "dogen/test_models/two_layers_with_objects/serialization/registrar_ser.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::test_models::boost_model::register_types<Archive>(ar);
    dogen::test_models::compressed::register_types<Archive>(ar);
    dogen::test_models::disable_cmakelists::register_types<Archive>(ar);
    dogen::test_models::disable_facet_folders::register_types<Archive>(ar);
    dogen::test_models::std_model::register_types<Archive>(ar);
    dogen::test_models::enable_facet_serialization::register_types<Archive>(ar);
    dogen::test_models::two_layers_with_objects::register_types<Archive>(ar);
    dogen::test_models::cpp_model::register_types<Archive>(ar);
    dogen::test_models::cpp_98::register_types<Archive>(ar);
}

#endif
