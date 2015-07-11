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
#ifndef DOGEN_SML_TYPES_ALL_HPP
#define DOGEN_SML_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/sml.hpp"
#include "dogen/sml/types/node.hpp"
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/merger.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/concept.hpp"
#include "dogen/sml/types/injector.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/resolver.hpp"
#include "dogen/sml/types/workflow.hpp"
#include "dogen/sml/types/persister.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/enumerator.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/object_types.hpp"
#include "dogen/sml/types/origin_types.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/sml/types/json_hydrator.hpp"
#include "dogen/sml/types/merging_error.hpp"
#include "dogen/sml/types/parsing_error.hpp"
#include "dogen/sml/types/indexing_error.hpp"
#include "dogen/sml/types/concept_indexer.hpp"
#include "dogen/sml/types/hydration_error.hpp"
#include "dogen/sml/types/injection_error.hpp"
#include "dogen/sml/types/persister_error.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/property_indexer.hpp"
#include "dogen/sml/types/resolution_error.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/identifier_parser.hpp"
#include "dogen/sml/types/relationship_types.hpp"
#include "dogen/sml/types/association_indexer.hpp"
#include "dogen/sml/types/nested_qname_builder.hpp"
#include "dogen/sml/types/generalization_indexer.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"

#endif
