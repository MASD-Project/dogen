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
#ifndef DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_HASH_ALL_HASH_HPP
#define DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_HASH_ALL_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/trivial_inheritance/hash/base_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/pkg1/child_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/pkg3/child_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/pkg4/child_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/descendant1_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/descendant2_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/descendant3_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/pkg1/parent_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/pkg2/parent_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/move_ctor_base_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/non_final_leaf_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/parent_outside_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/non_final_orphan_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/child_of_a_child1_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/child_of_a_child2_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/child_via_settings_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/child_with_members_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/parent_with_members_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/move_ctor_descendant_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/child_without_members_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/parent_without_members_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/pkg1/child_via_settings_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/pkg3/child_via_settings_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/pkg4/child_via_settings_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/third_child_with_members_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/move_ctor_empty_descendant_hash.hpp"
#include "dogen/test_models/trivial_inheritance/hash/second_child_without_members_hash.hpp"

#endif
