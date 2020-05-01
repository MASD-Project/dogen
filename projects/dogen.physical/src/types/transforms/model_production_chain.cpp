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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/io/entities/model_set_io.hpp"
#include "dogen.physical/types/transforms/merge_transform.hpp"
#include "dogen.physical/types/transforms/update_outputting_properties_transform.hpp"
#include "dogen.physical/types/transforms/operation_transform.hpp"
#include "dogen.physical/types/transforms/gather_external_artefacts_transform.hpp"
#include "dogen.physical/types/transforms/generate_diffs_transform.hpp"
#include "dogen.physical/types/transforms/generate_patch_transform.hpp"
#include "dogen.physical/types/transforms/generate_report_transform.hpp"
#include "dogen.physical/types/transforms/mock_content_filler_transform.hpp"
#include "dogen.physical/types/transforms/model_production_chain.hpp"

namespace {

const std::string transform_id("physical.transforms.model_production_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

entities::model model_production_chain::
apply(const context& ctx, const entities::model_set& ms) {
    tracing::scoped_chain_tracer stp(lg, "model production chain",
        transform_id, ms.name().simple(), *ctx.tracer(), ms);

    /*
     * Before we do anything, we might as well merge all models into
     * one.
     */
    auto r(physical::transforms::merge_transform::apply(ctx, ms));

    /*
     * Now we start the processing proper. We start by reading the
     * outputting properties. We don't need this until later on but
     * its probably wise to get the meta-data out of the way first.
     */
    update_outputting_properties_transform::apply(ctx, r);

    /*
     * Fill in any empty files with mock content. Must be done before
     * the operation transform.
     */
    mock_content_filler_transform::apply(ctx, r);

    /*
     * Update the operations on all artefacts so that subsequent
     * transforms know what to do with them.
     */
    operation_transform::apply(ctx, r);

    /*
     * Now find all the external artefacts in the filesystem and
     * figure out which ones are not expected. This must be done
     * before we generate diffs.
     */
    gather_external_artefacts_transform::apply(ctx, r);

    /*
     * If diffing is enabled and the user requested unified diffs, we
     * will now compute unified diffs between the files in the
     * filesystem and the generated artefacts. This must be done
     * before writing and generating a patch.
     */
    generate_diffs_transform::apply(ctx, r);

    /*
     * If unified diffs were generated, we can now create a patch
     * file.
     */
    generate_patch_transform::apply(ctx, r);

    /*
     * If brief diffs were requested, we will generate a report of all
     * the operations for this set of artefacts.
     */
    generate_report_transform::apply(ctx, r);

    stp.end_chain(r);
    return r;
}

}
