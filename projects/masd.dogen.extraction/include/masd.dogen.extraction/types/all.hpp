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
#ifndef MASD_DOGEN_EXTRACTION_TYPES_ALL_HPP
#define MASD_DOGEN_EXTRACTION_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.extraction/types/traits.hpp"
#include "masd.dogen.extraction/types/extraction.hpp"
#include "masd.dogen.extraction/types/quote_types.hpp"
#include "masd.dogen.extraction/types/indent_filter.hpp"
#include "masd.dogen.extraction/types/spacing_types.hpp"
#include "masd.dogen.extraction/types/comment_styles.hpp"
#include "masd.dogen.extraction/types/formatting_error.hpp"
#include "masd.dogen.extraction/types/meta_model/model.hpp"
#include "masd.dogen.extraction/types/comment_formatter.hpp"
#include "masd.dogen.extraction/types/utility_formatter.hpp"
#include "masd.dogen.extraction/types/sequence_formatter.hpp"
#include "masd.dogen.extraction/types/transforms/context.hpp"
#include "masd.dogen.extraction/types/infix_configuration.hpp"
#include "masd.dogen.extraction/types/meta_model/artefact.hpp"
#include "masd.dogen.extraction/types/meta_model/operation.hpp"
#include "masd.dogen.extraction/types/cpp/include_formatter.hpp"
#include "masd.dogen.extraction/types/helpers/stream_writer.hpp"
#include "masd.dogen.extraction/types/helpers/writing_error.hpp"
#include "masd.dogen.extraction/types/meta_model/meta_model.hpp"
#include "masd.dogen.extraction/types/csharp/using_formatter.hpp"
#include "masd.dogen.extraction/types/helpers/unified_differ.hpp"
#include "masd.dogen.extraction/types/cpp/namespace_formatter.hpp"
#include "masd.dogen.extraction/types/helpers/files_by_status.hpp"
#include "masd.dogen.extraction/types/cpp/boilerplate_formatter.hpp"
#include "masd.dogen.extraction/types/helpers/filesystem_writer.hpp"
#include "masd.dogen.extraction/types/meta_model/operation_type.hpp"
#include "masd.dogen.extraction/types/cpp/header_guard_formatter.hpp"
#include "masd.dogen.extraction/types/csharp/namespace_formatter.hpp"
#include "masd.dogen.extraction/types/meta_model/operation_reason.hpp"
#include "masd.dogen.extraction/types/csharp/boilerplate_formatter.hpp"
#include "masd.dogen.extraction/types/helpers/file_status_collector.hpp"
#include "masd.dogen.extraction/types/cpp/scoped_namespace_formatter.hpp"
#include "masd.dogen.extraction/types/transforms/operation_transform.hpp"
#include "masd.dogen.extraction/types/transforms/transform_exception.hpp"
#include "masd.dogen.extraction/types/cpp/scoped_boilerplate_formatter.hpp"
#include "masd.dogen.extraction/types/meta_model/outputting_properties.hpp"
#include "masd.dogen.extraction/types/transforms/code_generation_chain.hpp"
#include "masd.dogen.extraction/types/csharp/scoped_namespace_formatter.hpp"
#include "masd.dogen.extraction/types/helpers/artefact_writer_interface.hpp"
#include "masd.dogen.extraction/types/transforms/model_production_chain.hpp"
#include "masd.dogen.extraction/types/transforms/remove_files_transform.hpp"
#include "masd.dogen.extraction/types/csharp/scoped_boilerplate_formatter.hpp"
#include "masd.dogen.extraction/types/transforms/generate_diffs_transform.hpp"
#include "masd.dogen.extraction/types/transforms/generate_patch_transform.hpp"
#include "masd.dogen.extraction/types/transforms/generate_report_transform.hpp"
#include "masd.dogen.extraction/types/transforms/write_artefacts_transform.hpp"
#include "masd.dogen.extraction/types/transforms/mock_content_filler_transform.hpp"
#include "masd.dogen.extraction/types/transforms/gather_external_artefacts_transform.hpp"
#include "masd.dogen.extraction/types/transforms/update_outputting_properties_transform.hpp"

#endif
