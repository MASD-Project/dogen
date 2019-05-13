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
#ifndef DOGEN_TEMPLATING_TYPES_ALL_HPP
#define DOGEN_TEMPLATING_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.templating/types/stitch/line.hpp"
#include "dogen.templating/types/stitch/block.hpp"
#include "dogen.templating/types/stitch/parser.hpp"
#include "dogen.templating/types/stitch/traits.hpp"
#include "dogen.templating/types/wale/workflow.hpp"
#include "dogen.templating/types/wale/formatter.hpp"
#include "dogen.templating/types/wale/properties.hpp"
#include "dogen.templating/types/stitch/formatter.hpp"
#include "dogen.templating/types/stitch/properties.hpp"
#include "dogen.templating/types/stitch/block_types.hpp"
#include "dogen.templating/types/wale/key_extractor.hpp"
#include "dogen.templating/types/wale/text_template.hpp"
#include "dogen.templating/types/stitch/instantiator.hpp"
#include "dogen.templating/types/helpers/kvp_resolver.hpp"
#include "dogen.templating/types/stitch/parsing_error.hpp"
#include "dogen.templating/types/stitch/text_template.hpp"
#include "dogen.templating/types/helpers/kvp_validator.hpp"
#include "dogen.templating/types/stitch/building_error.hpp"
#include "dogen.templating/types/wale/extraction_error.hpp"
#include "dogen.templating/types/wale/formatting_error.hpp"
#include "dogen.templating/types/stitch/formatting_error.hpp"
#include "dogen.templating/types/helpers/resolution_error.hpp"
#include "dogen.templating/types/helpers/validation_error.hpp"
#include "dogen.templating/types/stitch/properties_factory.hpp"
#include "dogen.templating/types/stitch/text_template_body.hpp"
#include "dogen.templating/types/stitch/instantiation_error.hpp"

#endif
