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
#include "dogen/formatters/types/file.hpp"
#include "dogen/formatters/types/traits.hpp"
#include "dogen/formatters/types/editors.hpp"
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/types/utility.hpp"
#include "dogen/formatters/types/modeline.hpp"
#include "dogen/formatters/types/annotation.hpp"
#include "dogen/formatters/types/formatters.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/quote_types.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/formatters/types/padding_types.hpp"
#include "dogen/formatters/types/spacing_types.hpp"
#include "dogen/formatters/types/building_error.hpp"
#include "dogen/formatters/types/comment_styles.hpp"
#include "dogen/formatters/types/modeline_field.hpp"
#include "dogen/formatters/types/modeline_group.hpp"
#include "dogen/formatters/types/hydration_error.hpp"
#include "dogen/formatters/types/formatting_error.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/formatters/types/comment_formatter.hpp"
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/formatters/types/modeline_formatter.hpp"
#include "dogen/formatters/types/modeline_locations.hpp"
#include "dogen/formatters/types/licence_text_hydrator.hpp"
#include "dogen/formatters/types/modeline_group_hydrator.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"
#include "dogen/formatters/types/code_generation_marker_factory.hpp"
