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
#include "dogen/dynamic/types/aggregator.hpp"
#include "dogen/dynamic/types/boolean.hpp"
#include "dogen/dynamic/types/boolean_collection.hpp"
#include "dogen/dynamic/types/building_error.hpp"
#include "dogen/dynamic/types/dynamic.hpp"
#include "dogen/dynamic/types/field.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/dynamic/types/field_factory.hpp"
#include "dogen/dynamic/types/merger.hpp"
#include "dogen/dynamic/types/name.hpp"
#include "dogen/dynamic/types/number.hpp"
#include "dogen/dynamic/types/number_collection.hpp"
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/object_extensions.hpp"
#include "dogen/dynamic/types/registrar.hpp"
#include "dogen/dynamic/types/registrar_error.hpp"
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/dynamic/types/text.hpp"
#include "dogen/dynamic/types/text_collection.hpp"
#include "dogen/dynamic/types/value.hpp"
#include "dogen/dynamic/types/value_types.hpp"
#include "dogen/dynamic/types/value_visitor.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/dynamic/types/workflow_error.hpp"
