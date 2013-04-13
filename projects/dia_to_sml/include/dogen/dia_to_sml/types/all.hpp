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
#include "dogen/dia_to_sml/types/building_error.hpp"
#include "dogen/dia_to_sml/types/comments_parser.hpp"
#include "dogen/dia_to_sml/types/context.hpp"
#include "dogen/dia_to_sml/types/enum_parser.hpp"
#include "dogen/dia_to_sml/types/graph_builder.hpp"
#include "dogen/dia_to_sml/types/identifier_parser.hpp"
#include "dogen/dia_to_sml/types/object_to_enumeration.hpp"
#include "dogen/dia_to_sml/types/object_to_exception.hpp"
#include "dogen/dia_to_sml/types/object_to_package.hpp"
#include "dogen/dia_to_sml/types/object_to_pod.hpp"
#include "dogen/dia_to_sml/types/object_transformer.hpp"
#include "dogen/dia_to_sml/types/object_transformer_interface.hpp"
#include "dogen/dia_to_sml/types/object_types.hpp"
#include "dogen/dia_to_sml/types/parsing_error.hpp"
#include "dogen/dia_to_sml/types/stereotypes.hpp"
#include "dogen/dia_to_sml/types/transformation_error.hpp"
#include "dogen/dia_to_sml/types/transformer.hpp"
#include "dogen/dia_to_sml/types/visitor.hpp"
#include "dogen/dia_to_sml/types/workflow.hpp"
#include "dogen/dia_to_sml/types/workflow_interface.hpp"
