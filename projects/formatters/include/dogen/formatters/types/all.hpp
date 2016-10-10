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
#ifndef DOGEN_FORMATTERS_TYPES_ALL_HPP
#define DOGEN_FORMATTERS_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/formatters/types/file.hpp"
#include "dogen/formatters/types/traits.hpp"
#include "dogen/formatters/types/editors.hpp"
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/types/modeline.hpp"
#include "dogen/formatters/types/formatters.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/quote_types.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/formatters/types/spacing_types.hpp"
#include "dogen/formatters/types/stream_writer.hpp"
#include "dogen/formatters/types/writing_error.hpp"
#include "dogen/formatters/types/building_error.hpp"
#include "dogen/formatters/types/comment_styles.hpp"
#include "dogen/formatters/types/modeline_field.hpp"
#include "dogen/formatters/types/modeline_group.hpp"
#include "dogen/formatters/types/hydration_error.hpp"
#include "dogen/formatters/types/formatting_error.hpp"
#include "dogen/formatters/types/comment_formatter.hpp"
#include "dogen/formatters/types/filesystem_writer.hpp"
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/formatters/types/modeline_formatter.hpp"
#include "dogen/formatters/types/modeline_locations.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/formatters/types/infix_configuration.hpp"
#include "dogen/formatters/types/decoration_formatter.hpp"
#include "dogen/formatters/types/cpp/include_formatter.hpp"
#include "dogen/formatters/types/decoration_properties.hpp"
#include "dogen/formatters/types/file_writer_interface.hpp"
#include "dogen/formatters/types/licence_text_hydrator.hpp"
#include "dogen/formatters/types/cpp/namespace_formatter.hpp"
#include "dogen/formatters/types/modeline_group_hydrator.hpp"
#include "dogen/formatters/types/decoration_configuration.hpp"
#include "dogen/formatters/types/cpp/boilerplate_formatter.hpp"
#include "dogen/formatters/types/cpp/header_guard_formatter.hpp"
#include "dogen/formatters/types/decoration_properties_factory.hpp"
#include "dogen/formatters/types/code_generation_marker_factory.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"

#endif
