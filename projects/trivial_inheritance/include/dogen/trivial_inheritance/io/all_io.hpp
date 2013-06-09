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
#include "dogen/trivial_inheritance/io/base_io.hpp"
#include "dogen/trivial_inheritance/io/child_of_a_child1_io.hpp"
#include "dogen/trivial_inheritance/io/child_of_a_child2_io.hpp"
#include "dogen/trivial_inheritance/io/child_with_members_io.hpp"
#include "dogen/trivial_inheritance/io/child_without_members_io.hpp"
#include "dogen/trivial_inheritance/io/descendant1_io.hpp"
#include "dogen/trivial_inheritance/io/descendant2_io.hpp"
#include "dogen/trivial_inheritance/io/descendant3_io.hpp"
#include "dogen/trivial_inheritance/io/move_ctor_base_io.hpp"
#include "dogen/trivial_inheritance/io/move_ctor_descendant_io.hpp"
#include "dogen/trivial_inheritance/io/move_ctor_empty_descendant_io.hpp"
#include "dogen/trivial_inheritance/io/parent_outside_io.hpp"
#include "dogen/trivial_inheritance/io/parent_with_members_io.hpp"
#include "dogen/trivial_inheritance/io/parent_without_members_io.hpp"
#include "dogen/trivial_inheritance/io/pkg1/child_io.hpp"
#include "dogen/trivial_inheritance/io/pkg1/parent_io.hpp"
#include "dogen/trivial_inheritance/io/pkg2/parent_io.hpp"
#include "dogen/trivial_inheritance/io/pkg3/child_io.hpp"
#include "dogen/trivial_inheritance/io/pkg4/child_io.hpp"
#include "dogen/trivial_inheritance/io/second_child_without_members_io.hpp"
#include "dogen/trivial_inheritance/io/third_child_with_members_io.hpp"
