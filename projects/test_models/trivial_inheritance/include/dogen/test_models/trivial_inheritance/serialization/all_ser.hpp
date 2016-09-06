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
#ifndef DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_SERIALIZATION_ALL_SER_HPP
#define DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_SERIALIZATION_ALL_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/trivial_inheritance/serialization/base_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/registrar_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg1/child_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg3/child_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg4/child_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/descendant1_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/descendant2_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/descendant3_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg1/parent_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg2/parent_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/move_ctor_base_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/parent_outside_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/child_of_a_child1_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/child_of_a_child2_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/child_via_settings_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/child_with_members_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/parent_with_members_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/move_ctor_descendant_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/child_without_members_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/parent_without_members_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg1/child_via_settings_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg3/child_via_settings_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg4/child_via_settings_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/third_child_with_members_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/move_ctor_empty_descendant_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/second_child_without_members_ser.hpp"

#endif
