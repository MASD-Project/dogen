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
#include <dtl/dtl.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/io/meta_model/operation_io.hpp"
#include "masd.dogen.extraction/io/helpers/files_by_status_io.hpp"
#include "masd.dogen.extraction/types/helpers/file_status_collector.hpp"
#include "masd.dogen.extraction/types/helpers/unified_differ.hpp"
#include "masd.dogen.extraction/types/transforms/generate_diffs_transform.hpp"

namespace {

const std::string transform_id(
    "extraction.transforms.generate_diffs_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;

}

namespace masd::dogen::extraction::transforms {

void generate_diffs_transform::
transform(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "gather external artefacts transform", transform_id, m.name(),
        *ctx.tracer(), m);

    BOOST_LOG_SEV(lg, debug) << "Finding diffs for model: " << m.name();

    /*
     * If the user did not request diffing, there is nothing to do.
     */
    if (!ctx.diffing_configuration())
        return;

    /*
     * If the user requested brief diffs, there is nothing to do as
     * the transform only cares about unified diffs.
     */
    const auto style(ctx.diffing_configuration()->style());
    if (style == diffing_style::brief)
        return;

    bool found_diffs(false);
    for (auto& a : m.artefacts()) {
        BOOST_LOG_SEV(lg, debug) << "Processing arefact: "
                                 << a.path().filename();
        BOOST_LOG_SEV(lg, debug) << "Arefact operation: " << a.operation();

        /*
         * Ensure the artefact can contribute to the diff.
         */
        const auto reason(a.operation().reason());
        using extraction::meta_model::operation_reason;
        if (reason != operation_reason::newly_generated &&
            reason != operation_reason::changed_generated)
            continue;

        found_diffs = true;

        /*
         * If the file already exists, obtain its current content.
         */
        using masd::dogen::utility::filesystem::read_file_content;
        const std::string c(reason == operation_reason::newly_generated ?
            empty : read_file_content(a.path()));

        /*
         * Diff the content of the file against the artefact,
         * producing a unified diff.
         */
        const auto ud(helpers::unified_differ::diff(c, a.content(),
                m.managed_directories().front(), a.path(),
                "Changed generated file"));
        a.unified_diff(ud);
    }

    if (!found_diffs)
        BOOST_LOG_SEV(lg, debug) << "No diffs found in model.";

    stp.end_transform(m);

}

}
