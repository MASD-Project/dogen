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
#include "dogen/test_models/stereotypes/test_data/value_td.hpp"
#include "dogen/test_models/stereotypes/test_data/entity_td.hpp"
#include "dogen/test_models/stereotypes/test_data/fluent_td.hpp"
#include "dogen/test_models/stereotypes/test_data/some_type_td.hpp"
#include "dogen/test_models/stereotypes/test_data/versioned_td.hpp"
#include "dogen/test_models/stereotypes/test_data/identity_pod_td.hpp"
#include "dogen/test_models/stereotypes/test_data/just_identity_td.hpp"
#include "dogen/test_models/stereotypes/test_data/immutable_two_td.hpp"
#include "dogen/test_models/stereotypes/test_data/aggregate_root_td.hpp"
#include "dogen/test_models/stereotypes/test_data/immutable_zero_td.hpp"
#include "dogen/test_models/stereotypes/test_data/immutable_four_td.hpp"
#include "dogen/test_models/stereotypes/test_data/further_refined_td.hpp"
#include "dogen/test_models/stereotypes/test_data/just_identity_ver_td.hpp"
#include "dogen/test_models/stereotypes/test_data/base_with_concept_td.hpp"
#include "dogen/test_models/stereotypes/test_data/base_concept_model_td.hpp"
#include "dogen/test_models/stereotypes/test_data/composite_identity_td.hpp"
#include "dogen/test_models/stereotypes/test_data/identity_and_other_td.hpp"
#include "dogen/test_models/stereotypes/test_data/multi_concept_model_td.hpp"
#include "dogen/test_models/stereotypes/test_data/simple_concept_model_td.hpp"
#include "dogen/test_models/stereotypes/test_data/pkg1/keyed_in_package_td.hpp"
#include "dogen/test_models/stereotypes/test_data/identity_and_other_ver_td.hpp"
#include "dogen/test_models/stereotypes/test_data/composite_identity_ver_td.hpp"
#include "dogen/test_models/stereotypes/test_data/immutable_one_primitive_td.hpp"
#include "dogen/test_models/stereotypes/test_data/refinement_concept_model_td.hpp"
#include "dogen/test_models/stereotypes/test_data/identity_pod_versioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/immutable_one_non_primitive_td.hpp"
#include "dogen/test_models/stereotypes/test_data/identity_pod_unversioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/just_identity_unversioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/just_identity_ver_versioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/second_refinement_concept_model_td.hpp"
#include "dogen/test_models/stereotypes/test_data/just_identity_ver_unversioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/multiple_refinement_concept_model_td.hpp"
#include "dogen/test_models/stereotypes/test_data/composite_identity_unversioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/identity_and_other_unversioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/identity_and_other_ver_versioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/composite_identity_ver_versioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/pkg1/keyed_in_package_unversioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/identity_and_other_ver_unversioned_key_td.hpp"
#include "dogen/test_models/stereotypes/test_data/composite_identity_ver_unversioned_key_td.hpp"
