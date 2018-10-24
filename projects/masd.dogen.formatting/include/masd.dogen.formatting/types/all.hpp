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
#ifndef DOGEN_FORMATTING_TYPES_ALL_HPP
#define DOGEN_FORMATTING_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.formatting/types/traits.hpp"
#include "dogen.formatting/types/editors.hpp"
#include "dogen.formatting/types/licence.hpp"
#include "dogen.formatting/types/modeline.hpp"
#include "dogen.formatting/types/formatting.hpp"
#include "dogen.formatting/types/repository.hpp"
#include "dogen.formatting/types/quote_types.hpp"
#include "dogen.formatting/types/indent_filter.hpp"
#include "dogen.formatting/types/spacing_types.hpp"
#include "dogen.formatting/types/building_error.hpp"
#include "dogen.formatting/types/comment_styles.hpp"
#include "dogen.formatting/types/modeline_field.hpp"
#include "dogen.formatting/types/modeline_group.hpp"
#include "dogen.formatting/types/hydration_error.hpp"
#include "dogen.formatting/types/formatting_error.hpp"
#include "dogen.formatting/types/comment_formatter.hpp"
#include "dogen.formatting/types/utility_formatter.hpp"
#include "dogen.formatting/types/modeline_formatter.hpp"
#include "dogen.formatting/types/modeline_locations.hpp"
#include "dogen.formatting/types/repository_factory.hpp"
#include "dogen.formatting/types/sequence_formatter.hpp"
#include "dogen.formatting/types/infix_configuration.hpp"
#include "dogen.formatting/types/decoration_formatter.hpp"
#include "dogen.formatting/types/cpp/include_formatter.hpp"
#include "dogen.formatting/types/decoration_properties.hpp"
#include "dogen.formatting/types/licence_text_hydrator.hpp"
#include "dogen.formatting/types/csharp/using_formatter.hpp"
#include "dogen.formatting/types/cpp/namespace_formatter.hpp"
#include "dogen.formatting/types/modeline_group_hydrator.hpp"
#include "dogen.formatting/types/decoration_configuration.hpp"
#include "dogen.formatting/types/cpp/boilerplate_formatter.hpp"
#include "dogen.formatting/types/cpp/header_guard_formatter.hpp"
#include "dogen.formatting/types/csharp/namespace_formatter.hpp"
#include "dogen.formatting/types/csharp/boilerplate_formatter.hpp"
#include "dogen.formatting/types/decoration_properties_factory.hpp"
#include "dogen.formatting/types/code_generation_marker_factory.hpp"
#include "dogen.formatting/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen.formatting/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen.formatting/types/csharp/scoped_namespace_formatter.hpp"
#include "dogen.formatting/types/csharp/scoped_boilerplate_formatter.hpp"

#endif
