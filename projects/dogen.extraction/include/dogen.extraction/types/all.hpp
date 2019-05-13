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
#ifndef DOGEN_EXTRACTION_TYPES_ALL_HPP
#define DOGEN_EXTRACTION_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.extraction/types/traits.hpp"
#include "dogen.extraction/types/extraction.hpp"
#include "dogen.extraction/types/meta_model/model.hpp"
#include "dogen.extraction/types/features/features.hpp"
#include "dogen.extraction/types/transforms/context.hpp"
#include "dogen.extraction/types/meta_model/artefact.hpp"
#include "dogen.extraction/types/meta_model/operation.hpp"
#include "dogen.extraction/types/meta_model/meta_model.hpp"
#include "dogen.extraction/types/helpers/unified_differ.hpp"
#include "dogen.extraction/types/helpers/files_by_status.hpp"
#include "dogen.extraction/types/meta_model/operation_type.hpp"
#include "dogen.extraction/types/meta_model/operation_reason.hpp"
#include "dogen.extraction/types/helpers/file_status_collector.hpp"
#include "dogen.extraction/types/transforms/operation_transform.hpp"
#include "dogen.extraction/types/transforms/transform_exception.hpp"
#include "dogen.extraction/types/meta_model/outputting_properties.hpp"
#include "dogen.extraction/types/transforms/code_generation_chain.hpp"
#include "dogen.extraction/types/transforms/model_production_chain.hpp"
#include "dogen.extraction/types/transforms/remove_files_transform.hpp"
#include "dogen.extraction/types/transforms/generate_diffs_transform.hpp"
#include "dogen.extraction/types/transforms/generate_patch_transform.hpp"
#include "dogen.extraction/types/transforms/generate_report_transform.hpp"
#include "dogen.extraction/types/transforms/write_artefacts_transform.hpp"
#include "dogen.extraction/types/transforms/mock_content_filler_transform.hpp"
#include "dogen.extraction/types/transforms/gather_external_artefacts_transform.hpp"
#include "dogen.extraction/types/transforms/update_outputting_properties_transform.hpp"

#endif
