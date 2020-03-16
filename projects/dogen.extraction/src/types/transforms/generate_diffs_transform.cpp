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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.extraction/io/entities/model_io.hpp"
#include "dogen.extraction/io/entities/operation_io.hpp"
#include "dogen.extraction/io/helpers/files_by_status_io.hpp"
#include "dogen.extraction/types/helpers/file_status_collector.hpp"
#include "dogen.extraction/types/helpers/unified_differ.hpp"
#include "dogen.extraction/types/transforms/generate_diffs_transform.hpp"

namespace {

const std::string transform_id(
    "extraction.transforms.generate_diffs_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string reason_new("Reason: New generated file.");
const std::string reason_changed("Reason: Changed generated file.");
const std::string reason_unexpected("Reason: unexpected file.");
const std::string reason_force_write("Reason: Force write requested.");
const std::string reason_other("Reason: Other.");

}

namespace dogen::extraction::transforms {

void generate_diffs_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "generate diffs transform", transform_id, m.name(),
        *ctx.tracer(), m);

    BOOST_LOG_SEV(lg, debug) << "Finding diffs for model: " << m.name();

    /*
     * If the user did not request diffing, there is nothing to do.
     */
    if (!ctx.diffing_configuration()) {
        BOOST_LOG_SEV(lg, debug) << "Diffing not enabled.";
        return;
    }

    bool found_diffs(false);
    const auto md(m.managed_directories().front());
    for (auto& a : m.artefacts()) {
        const auto& p(a.path());
        if (p.empty()) {
            // FIXME: throw
            BOOST_LOG_SEV(lg, error) << "Empty file name supplied.";
            continue;
        }

        BOOST_LOG_SEV(lg, trace) << "Processing arefact: "
                                 << p.filename();
        BOOST_LOG_SEV(lg, trace) << "Arefact operation: " << a.operation();

        /*
         * Ensure the artefact can contribute to the diff.
         */
        const auto ot(a.operation().type());
        using extraction::entities::operation_type;
        if (ot != operation_type::write && ot != operation_type::remove) {
            BOOST_LOG_SEV(lg, trace) << "Operation will not produce diffs.";
            continue;
        }

        found_diffs = true;
        BOOST_LOG_SEV(lg, debug) << "Arefact has diffs.";

        /*
         * If the file already exists, obtain its current content.
         */
        using extraction::entities::operation_reason;
        const auto reason(a.operation().reason());
        using dogen::utility::filesystem::read_file_content;
        const std::string c(reason == operation_reason::newly_generated ?
            empty : read_file_content(p));

        /*
         * Diff the content of the file against the artefact,
         * producing a unified diff.
         */
        const std::string info(
            [&]() {
                switch(reason) {
                case operation_reason::newly_generated:
                    return reason_new;
                case operation_reason::changed_generated:
                    return reason_changed;
                case operation_reason::unexpected:
                    return reason_unexpected;
                case operation_reason::force_write:
                    return reason_force_write;
                default:
                    return reason_other;
                }
            }());

        using helpers::unified_differ;
        const auto ud(unified_differ::diff(c, a.content(), md, p, info));
        a.unified_diff(ud);
    }

    if (!found_diffs)
        BOOST_LOG_SEV(lg, debug) << "No diffs found in model.";

    stp.end_transform(m);

}

}
