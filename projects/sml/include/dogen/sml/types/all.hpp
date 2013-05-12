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
#include "dogen/sml/types/boost_model_factory.hpp"
#include "dogen/sml/types/category_types.hpp"
#include "dogen/sml/types/entry.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/enumerator.hpp"
#include "dogen/sml/types/exception.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/injection_error.hpp"
#include "dogen/sml/types/injector.hpp"
#include "dogen/sml/types/merger.hpp"
#include "dogen/sml/types/merging_error.hpp"
#include "dogen/sml/types/meta_types.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/package.hpp"
#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/pod_types.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/primitive_model_factory.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/reference.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/service_types.hpp"
#include "dogen/sml/types/std_model_factory.hpp"
#include "dogen/sml/types/string_table.hpp"
#include "dogen/sml/types/workflow.hpp"
