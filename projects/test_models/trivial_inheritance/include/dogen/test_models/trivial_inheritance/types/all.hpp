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
#ifndef DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_TYPES_ALL_HPP
#define DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/trivial_inheritance/types/base.hpp"
#include "dogen/test_models/trivial_inheritance/types/pkg1/child.hpp"
#include "dogen/test_models/trivial_inheritance/types/pkg3/child.hpp"
#include "dogen/test_models/trivial_inheritance/types/pkg4/child.hpp"
#include "dogen/test_models/trivial_inheritance/types/descendant1.hpp"
#include "dogen/test_models/trivial_inheritance/types/descendant2.hpp"
#include "dogen/test_models/trivial_inheritance/types/descendant3.hpp"
#include "dogen/test_models/trivial_inheritance/types/pkg1/parent.hpp"
#include "dogen/test_models/trivial_inheritance/types/pkg2/parent.hpp"
#include "dogen/test_models/trivial_inheritance/types/base_visitor.hpp"
#include "dogen/test_models/trivial_inheritance/types/move_ctor_base.hpp"
#include "dogen/test_models/trivial_inheritance/types/non_final_leaf.hpp"
#include "dogen/test_models/trivial_inheritance/types/parent_outside.hpp"
#include "dogen/test_models/trivial_inheritance/types/non_final_orphan.hpp"
#include "dogen/test_models/trivial_inheritance/types/child_of_a_child1.hpp"
#include "dogen/test_models/trivial_inheritance/types/child_of_a_child2.hpp"
#include "dogen/test_models/trivial_inheritance/types/child_via_settings.hpp"
#include "dogen/test_models/trivial_inheritance/types/child_with_members.hpp"
#include "dogen/test_models/trivial_inheritance/types/parent_with_members.hpp"
#include "dogen/test_models/trivial_inheritance/types/trivial_inheritance.hpp"
#include "dogen/test_models/trivial_inheritance/types/move_ctor_descendant.hpp"
#include "dogen/test_models/trivial_inheritance/types/child_without_members.hpp"
#include "dogen/test_models/trivial_inheritance/types/parent_without_members.hpp"
#include "dogen/test_models/trivial_inheritance/types/pkg1/child_via_settings.hpp"
#include "dogen/test_models/trivial_inheritance/types/pkg3/child_via_settings.hpp"
#include "dogen/test_models/trivial_inheritance/types/pkg4/child_via_settings.hpp"
#include "dogen/test_models/trivial_inheritance/types/third_child_with_members.hpp"
#include "dogen/test_models/trivial_inheritance/types/move_ctor_empty_descendant.hpp"
#include "dogen/test_models/trivial_inheritance/types/second_child_without_members.hpp"

#endif
