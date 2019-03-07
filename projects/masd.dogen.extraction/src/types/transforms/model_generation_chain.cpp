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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/types/transforms/operation_transform.hpp"
#include "masd.dogen.extraction/types/transforms/gather_external_artefacts_transform.hpp"
#include "masd.dogen.extraction/types/transforms/generate_diffs_transform.hpp"
#include "masd.dogen.extraction/types/transforms/generate_patch_transform.hpp"
#include "masd.dogen.extraction/types/transforms/generate_report_transform.hpp"
#include "masd.dogen.extraction/types/transforms/write_artefacts_transform.hpp"
#include "masd.dogen.extraction/types/transforms/remove_files_transform.hpp"
#include "masd.dogen.extraction/types/transforms/model_generation_chain.hpp"

namespace {

const std::string transform_id("extraction.transforms.model_generation_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::extraction::transforms {

void model_generation_chain::
transform(const context& ctx, meta_model::model& m) {
    tracing::scoped_chain_tracer stp(lg, "model generation chain",
        transform_id, m.name(), *ctx.tracer(), m);

    /*
     * First we need to update the operations on all artefacts so that
     * subsequent transforms know what to do with them.
     */
    operation_transform::transform(ctx, m);

    /*
     * Now find all the external artefacts in the filesystem and
     * figure out which ones are not expected. This must be done
     * before we generate diffs.
     */
    gather_external_artefacts_transform::transform(ctx, m);

    /*
     * If diffing is enabled and the user requested unified diffs, we
     * will now compute unified diffs between the files in the
     * filesystem and the generated artefacts. This must be done
     * before writing and generating a patch.
     */
    generate_diffs_transform::transform(ctx, m);

    /*
     * If unified diffs were generated, we can now create a patch
     * file.
     */
    generate_patch_transform::transform(ctx, m);

    /*
     * If brief diffs were requested, we will generate a report of all
     * the operations for this set of artefacts.
     */
    generate_report_transform::transform(ctx, m);

    /*
     * Write all of the artefacts that require writing.
     */
    write_artefacts_transform::transform(ctx, m);

    /*
     * Finally, remove all of the unexpected files.
     */
    remove_files_transform::transform(ctx, m);
}

}
