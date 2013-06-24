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
#include "dogen/stereotypes/io/aggregate_root_io.hpp"
#include "dogen/stereotypes/io/base_concept_model_io.hpp"
#include "dogen/stereotypes/io/composite_identity_io.hpp"
#include "dogen/stereotypes/io/composite_identity_unversioned_key_io.hpp"
#include "dogen/stereotypes/io/composite_identity_ver_io.hpp"
#include "dogen/stereotypes/io/composite_identity_ver_unversioned_key_io.hpp"
#include "dogen/stereotypes/io/composite_identity_ver_versioned_key_io.hpp"
#include "dogen/stereotypes/io/entity_io.hpp"
#include "dogen/stereotypes/io/fluent_io.hpp"
#include "dogen/stereotypes/io/identity_and_other_io.hpp"
#include "dogen/stereotypes/io/identity_and_other_unversioned_key_io.hpp"
#include "dogen/stereotypes/io/identity_and_other_ver_io.hpp"
#include "dogen/stereotypes/io/identity_and_other_ver_unversioned_key_io.hpp"
#include "dogen/stereotypes/io/identity_and_other_ver_versioned_key_io.hpp"
#include "dogen/stereotypes/io/identity_pod_io.hpp"
#include "dogen/stereotypes/io/identity_pod_unversioned_key_io.hpp"
#include "dogen/stereotypes/io/identity_pod_versioned_key_io.hpp"
#include "dogen/stereotypes/io/immutable_four_io.hpp"
#include "dogen/stereotypes/io/immutable_one_non_primitive_io.hpp"
#include "dogen/stereotypes/io/immutable_one_primitive_io.hpp"
#include "dogen/stereotypes/io/immutable_two_io.hpp"
#include "dogen/stereotypes/io/immutable_zero_io.hpp"
#include "dogen/stereotypes/io/just_identity_io.hpp"
#include "dogen/stereotypes/io/just_identity_unversioned_key_io.hpp"
#include "dogen/stereotypes/io/just_identity_ver_io.hpp"
#include "dogen/stereotypes/io/just_identity_ver_unversioned_key_io.hpp"
#include "dogen/stereotypes/io/just_identity_ver_versioned_key_io.hpp"
#include "dogen/stereotypes/io/pkg1/keyed_in_package_io.hpp"
#include "dogen/stereotypes/io/pkg1/keyed_in_package_unversioned_key_io.hpp"
#include "dogen/stereotypes/io/refinement_concept_model_io.hpp"
#include "dogen/stereotypes/io/simple_concept_model_io.hpp"
#include "dogen/stereotypes/io/some_type_io.hpp"
#include "dogen/stereotypes/io/value_io.hpp"
#include "dogen/stereotypes/io/versioned_io.hpp"
