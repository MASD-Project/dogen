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
#include "dogen/dynamic/schema/types/aggregator.hpp"
#include "dogen/dynamic/schema/types/boolean.hpp"
#include "dogen/dynamic/schema/types/building_error.hpp"
#include "dogen/dynamic/schema/types/content_extensions.hpp"
#include "dogen/dynamic/schema/types/field_access_error.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/dynamic/schema/types/field_instance.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"
#include "dogen/dynamic/schema/types/hydration_error.hpp"
#include "dogen/dynamic/schema/types/indexer.hpp"
#include "dogen/dynamic/schema/types/indexing_error.hpp"
#include "dogen/dynamic/schema/types/json_hydrator.hpp"
#include "dogen/dynamic/schema/types/name.hpp"
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/ownership_hierarchy.hpp"
#include "dogen/dynamic/schema/types/registrar.hpp"
#include "dogen/dynamic/schema/types/registrar_error.hpp"
#include "dogen/dynamic/schema/types/schema.hpp"
#include "dogen/dynamic/schema/types/scope_types.hpp"
#include "dogen/dynamic/schema/types/text.hpp"
#include "dogen/dynamic/schema/types/text_collection.hpp"
#include "dogen/dynamic/schema/types/value.hpp"
#include "dogen/dynamic/schema/types/value_factory.hpp"
#include "dogen/dynamic/schema/types/value_types.hpp"
#include "dogen/dynamic/schema/types/value_visitor.hpp"
#include "dogen/dynamic/schema/types/workflow.hpp"
#include "dogen/dynamic/schema/types/workflow_error.hpp"
