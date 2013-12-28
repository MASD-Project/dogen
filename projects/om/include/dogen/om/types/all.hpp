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
#include "dogen/om/types/annotation.hpp"
#include "dogen/om/types/annotation_factory.hpp"
#include "dogen/om/types/building_error.hpp"
#include "dogen/om/types/code_generation_marker_factory.hpp"
#include "dogen/om/types/comment_formatter.hpp"
#include "dogen/om/types/comment_styles.hpp"
#include "dogen/om/types/concept_formatter_interface.hpp"
#include "dogen/om/types/cpp_file_boilerplate_formatter.hpp"
#include "dogen/om/types/cpp_header_guard_formatter.hpp"
#include "dogen/om/types/cpp_include_formatter.hpp"
#include "dogen/om/types/cpp_includer_formatter.hpp"
#include "dogen/om/types/cpp_includes.hpp"
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"
#include "dogen/om/types/editors.hpp"
#include "dogen/om/types/file.hpp"
#include "dogen/om/types/file_formatter_interface.hpp"
#include "dogen/om/types/formatter_factory.hpp"
#include "dogen/om/types/formatting_error.hpp"
#include "dogen/om/types/hydration_error.hpp"
#include "dogen/om/types/hydration_workflow.hpp"
#include "dogen/om/types/licence.hpp"
#include "dogen/om/types/licence_hydrator.hpp"
#include "dogen/om/types/model_formatter_interface.hpp"
#include "dogen/om/types/modeline.hpp"
#include "dogen/om/types/modeline_field.hpp"
#include "dogen/om/types/modeline_formatter.hpp"
#include "dogen/om/types/modeline_group.hpp"
#include "dogen/om/types/modeline_group_hydrator.hpp"
#include "dogen/om/types/modeline_locations.hpp"
#include "dogen/om/types/module_formatter_interface.hpp"
#include "dogen/om/types/type_formatter_interface.hpp"
#include "dogen/om/types/workflow.hpp"
#include "dogen/om/types/workflow_error.hpp"
