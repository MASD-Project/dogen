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
#include "dogen/sml_to_cpp/types/locator.hpp"
#include "dogen/sml_to_cpp/types/context.hpp"
#include "dogen/sml_to_cpp/types/workflow.hpp"
#include "dogen/sml_to_cpp/types/includer.hpp"
#include "dogen/sml_to_cpp/types/std_types.hpp"
#include "dogen/sml_to_cpp/types/extractor.hpp"
#include "dogen/sml_to_cpp/types/sml_to_cpp.hpp"
#include "dogen/sml_to_cpp/types/boost_types.hpp"
#include "dogen/sml_to_cpp/types/transformer.hpp"
#include "dogen/sml_to_cpp/types/relationships.hpp"
#include "dogen/sml_to_cpp/types/inclusion_lists.hpp"
#include "dogen/sml_to_cpp/types/workflow_failure.hpp"
#include "dogen/sml_to_cpp/types/extraction_error.hpp"
#include "dogen/sml_to_cpp/types/std_model_helper.hpp"
#include "dogen/sml_to_cpp/types/file_info_factory.hpp"
#include "dogen/sml_to_cpp/types/boost_model_helper.hpp"
#include "dogen/sml_to_cpp/types/transformation_error.hpp"
