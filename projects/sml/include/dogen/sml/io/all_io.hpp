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
#include "dogen/sml/io/abstract_entity_io.hpp"
#include "dogen/sml/io/abstract_object_io.hpp"
#include "dogen/sml/io/category_types_io.hpp"
#include "dogen/sml/io/concept_io.hpp"
#include "dogen/sml/io/entity_io.hpp"
#include "dogen/sml/io/enumeration_io.hpp"
#include "dogen/sml/io/enumerator_io.hpp"
#include "dogen/sml/io/factory_io.hpp"
#include "dogen/sml/io/generation_types_io.hpp"
#include "dogen/sml/io/keyed_entity_io.hpp"
#include "dogen/sml/io/meta_types_io.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/module_io.hpp"
#include "dogen/sml/io/nested_qname_io.hpp"
#include "dogen/sml/io/pod_io.hpp"
#include "dogen/sml/io/pod_types_io.hpp"
#include "dogen/sml/io/primitive_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/reference_io.hpp"
#include "dogen/sml/io/repository_io.hpp"
#include "dogen/sml/io/service_io.hpp"
#include "dogen/sml/io/service_types_io.hpp"
#include "dogen/sml/io/type_io.hpp"
#include "dogen/sml/io/value_object_io.hpp"
#include "dogen/sml/io/value_types_io.hpp"
