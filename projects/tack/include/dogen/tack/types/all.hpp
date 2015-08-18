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
#ifndef DOGEN_TACK_TYPES_ALL_HPP
#define DOGEN_TACK_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/tack/types/name.hpp"
#include "dogen/tack/types/node.hpp"
#include "dogen/tack/types/tack.hpp"
#include "dogen/tack/types/type.hpp"
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/types/merger.hpp"
#include "dogen/tack/types/module.hpp"
#include "dogen/tack/types/object.hpp"
#include "dogen/tack/types/concept.hpp"
#include "dogen/tack/types/expander.hpp"
#include "dogen/tack/types/importer.hpp"
#include "dogen/tack/types/injector.hpp"
#include "dogen/tack/types/location.hpp"
#include "dogen/tack/types/property.hpp"
#include "dogen/tack/types/resolver.hpp"
#include "dogen/tack/types/assembler.hpp"
#include "dogen/tack/types/persister.hpp"
#include "dogen/tack/types/primitive.hpp"
#include "dogen/tack/types/enumerator.hpp"
#include "dogen/tack/types/enumeration.hpp"
#include "dogen/tack/types/nested_name.hpp"
#include "dogen/tack/types/name_builder.hpp"
#include "dogen/tack/types/object_types.hpp"
#include "dogen/tack/types/origin_types.hpp"
#include "dogen/tack/types/type_visitor.hpp"
#include "dogen/tack/types/merging_error.hpp"
#include "dogen/tack/types/parsing_error.hpp"
#include "dogen/tack/types/building_error.hpp"
#include "dogen/tack/types/indexing_error.hpp"
#include "dogen/tack/types/concept_indexer.hpp"
#include "dogen/tack/types/injection_error.hpp"
#include "dogen/tack/types/module_expander.hpp"
#include "dogen/tack/types/persister_error.hpp"
#include "dogen/tack/types/registrar_error.hpp"
#include "dogen/tack/types/generation_types.hpp"
#include "dogen/tack/types/input_descriptor.hpp"
#include "dogen/tack/types/property_indexer.hpp"
#include "dogen/tack/types/resolution_error.hpp"
#include "dogen/tack/types/identifier_parser.hpp"
#include "dogen/tack/types/referenes_expander.hpp"
#include "dogen/tack/types/relationship_types.hpp"
#include "dogen/tack/types/association_indexer.hpp"
#include "dogen/tack/types/nested_name_builder.hpp"
#include "dogen/tack/types/properties_expander.hpp"
#include "dogen/tack/types/generalization_indexer.hpp"
#include "dogen/tack/types/file_importer_interface.hpp"
#include "dogen/tack/types/file_importer_registrar.hpp"
#include "dogen/tack/types/all_model_items_traversal.hpp"

#endif
