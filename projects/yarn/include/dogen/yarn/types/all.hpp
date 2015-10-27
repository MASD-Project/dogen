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
#ifndef DOGEN_YARN_TYPES_ALL_HPP
#define DOGEN_YARN_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/node.hpp"
#include "dogen/yarn/types/yarn.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/merger.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/expander.hpp"
#include "dogen/yarn/types/importer.hpp"
#include "dogen/yarn/types/injector.hpp"
#include "dogen/yarn/types/location.hpp"
#include "dogen/yarn/types/property.hpp"
#include "dogen/yarn/types/resolver.hpp"
#include "dogen/yarn/types/assembler.hpp"
#include "dogen/yarn/types/persister.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumerator.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/nested_name.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/object_types.hpp"
#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/yarn/types/merging_error.hpp"
#include "dogen/yarn/types/parsing_error.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/indexing_error.hpp"
#include "dogen/yarn/types/concept_indexer.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/injection_error.hpp"
#include "dogen/yarn/types/persister_error.hpp"
#include "dogen/yarn/types/registrar_error.hpp"
#include "dogen/yarn/types/generation_types.hpp"
#include "dogen/yarn/types/input_descriptor.hpp"
#include "dogen/yarn/types/modules_expander.hpp"
#include "dogen/yarn/types/property_indexer.hpp"
#include "dogen/yarn/types/resolution_error.hpp"
#include "dogen/yarn/types/identifier_parser.hpp"
#include "dogen/yarn/types/relationship_types.hpp"
#include "dogen/yarn/types/association_indexer.hpp"
#include "dogen/yarn/types/nested_name_builder.hpp"
#include "dogen/yarn/types/properties_expander.hpp"
#include "dogen/yarn/types/references_expander.hpp"
#include "dogen/yarn/types/generalization_indexer.hpp"
#include "dogen/yarn/types/file_importer_interface.hpp"
#include "dogen/yarn/types/file_importer_registrar.hpp"
#include "dogen/yarn/types/all_model_items_traversal.hpp"

#endif
