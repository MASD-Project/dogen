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
#include "dogen/test_models/stereotypes/types/value.hpp"
#include "dogen/test_models/stereotypes/types/entity.hpp"
#include "dogen/test_models/stereotypes/types/fluent.hpp"
#include "dogen/test_models/stereotypes/types/service.hpp"
#include "dogen/test_models/stereotypes/types/some_type.hpp"
#include "dogen/test_models/stereotypes/types/versioned.hpp"
#include "dogen/test_models/stereotypes/types/stereotypes.hpp"
#include "dogen/test_models/stereotypes/types/identity_pod.hpp"
#include "dogen/test_models/stereotypes/types/immutable_two.hpp"
#include "dogen/test_models/stereotypes/types/just_identity.hpp"
#include "dogen/test_models/stereotypes/types/aggregate_root.hpp"
#include "dogen/test_models/stereotypes/types/immutable_four.hpp"
#include "dogen/test_models/stereotypes/types/immutable_zero.hpp"
#include "dogen/test_models/stereotypes/types/further_refined.hpp"
#include "dogen/test_models/stereotypes/types/base_with_concept.hpp"
#include "dogen/test_models/stereotypes/types/just_identity_ver.hpp"
#include "dogen/test_models/stereotypes/types/base_concept_model.hpp"
#include "dogen/test_models/stereotypes/types/composite_identity.hpp"
#include "dogen/test_models/stereotypes/types/identity_and_other.hpp"
#include "dogen/test_models/stereotypes/types/multi_concept_model.hpp"
#include "dogen/test_models/stereotypes/types/simple_concept_model.hpp"
#include "dogen/test_models/stereotypes/types/pkg1/keyed_in_package.hpp"
#include "dogen/test_models/stereotypes/types/composite_identity_ver.hpp"
#include "dogen/test_models/stereotypes/types/identity_and_other_ver.hpp"
#include "dogen/test_models/stereotypes/types/immutable_one_primitive.hpp"
#include "dogen/test_models/stereotypes/types/refinement_concept_model.hpp"
#include "dogen/test_models/stereotypes/types/identity_pod_versioned_key.hpp"
#include "dogen/test_models/stereotypes/types/immutable_one_non_primitive.hpp"
#include "dogen/test_models/stereotypes/types/identity_pod_unversioned_key.hpp"
#include "dogen/test_models/stereotypes/types/just_identity_unversioned_key.hpp"
#include "dogen/test_models/stereotypes/types/just_identity_ver_versioned_key.hpp"
#include "dogen/test_models/stereotypes/types/second_refinement_concept_model.hpp"
#include "dogen/test_models/stereotypes/types/just_identity_ver_unversioned_key.hpp"
#include "dogen/test_models/stereotypes/types/multiple_refinement_concept_model.hpp"
#include "dogen/test_models/stereotypes/types/composite_identity_unversioned_key.hpp"
#include "dogen/test_models/stereotypes/types/identity_and_other_unversioned_key.hpp"
#include "dogen/test_models/stereotypes/types/composite_identity_ver_versioned_key.hpp"
#include "dogen/test_models/stereotypes/types/identity_and_other_ver_versioned_key.hpp"
#include "dogen/test_models/stereotypes/types/pkg1/keyed_in_package_unversioned_key.hpp"
#include "dogen/test_models/stereotypes/types/composite_identity_ver_unversioned_key.hpp"
#include "dogen/test_models/stereotypes/types/identity_and_other_ver_unversioned_key.hpp"
