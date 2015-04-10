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
#include "dogen/test_models/stereotypes/hash/value_hash.hpp"
#include "dogen/test_models/stereotypes/hash/entity_hash.hpp"
#include "dogen/test_models/stereotypes/hash/fluent_hash.hpp"
#include "dogen/test_models/stereotypes/hash/some_type_hash.hpp"
#include "dogen/test_models/stereotypes/hash/versioned_hash.hpp"
#include "dogen/test_models/stereotypes/hash/identity_pod_hash.hpp"
#include "dogen/test_models/stereotypes/hash/just_identity_hash.hpp"
#include "dogen/test_models/stereotypes/hash/immutable_two_hash.hpp"
#include "dogen/test_models/stereotypes/hash/aggregate_root_hash.hpp"
#include "dogen/test_models/stereotypes/hash/immutable_zero_hash.hpp"
#include "dogen/test_models/stereotypes/hash/immutable_four_hash.hpp"
#include "dogen/test_models/stereotypes/hash/further_refined_hash.hpp"
#include "dogen/test_models/stereotypes/hash/just_identity_ver_hash.hpp"
#include "dogen/test_models/stereotypes/hash/base_with_concept_hash.hpp"
#include "dogen/test_models/stereotypes/hash/base_concept_model_hash.hpp"
#include "dogen/test_models/stereotypes/hash/composite_identity_hash.hpp"
#include "dogen/test_models/stereotypes/hash/identity_and_other_hash.hpp"
#include "dogen/test_models/stereotypes/hash/multi_concept_model_hash.hpp"
#include "dogen/test_models/stereotypes/hash/simple_concept_model_hash.hpp"
#include "dogen/test_models/stereotypes/hash/pkg1/keyed_in_package_hash.hpp"
#include "dogen/test_models/stereotypes/hash/identity_and_other_ver_hash.hpp"
#include "dogen/test_models/stereotypes/hash/composite_identity_ver_hash.hpp"
#include "dogen/test_models/stereotypes/hash/immutable_one_primitive_hash.hpp"
#include "dogen/test_models/stereotypes/hash/refinement_concept_model_hash.hpp"
#include "dogen/test_models/stereotypes/hash/identity_pod_versioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/immutable_one_non_primitive_hash.hpp"
#include "dogen/test_models/stereotypes/hash/identity_pod_unversioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/just_identity_unversioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/just_identity_ver_versioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/second_refinement_concept_model_hash.hpp"
#include "dogen/test_models/stereotypes/hash/just_identity_ver_unversioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/multiple_refinement_concept_model_hash.hpp"
#include "dogen/test_models/stereotypes/hash/composite_identity_unversioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/identity_and_other_unversioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/identity_and_other_ver_versioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/composite_identity_ver_versioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/pkg1/keyed_in_package_unversioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/identity_and_other_ver_unversioned_key_hash.hpp"
#include "dogen/test_models/stereotypes/hash/composite_identity_ver_unversioned_key_hash.hpp"
