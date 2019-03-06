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
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/io/helpers/files_by_status_io.hpp"
#include "masd.dogen.extraction/types/helpers/file_status_collector.hpp"
#include "masd.dogen.extraction/types/transforms/gather_external_artefacts_transform.hpp"

namespace {

const std::string transform_id(
    "extraction.transforms.gather_external_artefacts_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::extraction::transforms {

void gather_external_artefacts_transform::
transform(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "gather external artefacts transform", transform_id, m.name(),
        *ctx.tracer(), m);

    /*
     * First, collect all files with a status worth looking at. If
     * nothing turns up, we're done.
     */
    const auto fbs(helpers::file_status_collector::collect(m));
    if (fbs.unexpected().empty() && fbs.ignored().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No files found.";
        return;
    }

    /*
     * Now, for each file, generate artefacts with the appropriate
     * operations and add them to the model.
     */
    for (const auto& f : fbs.ignored()) {
        meta_model::artefact a;
        a.path(f);

        using meta_model::operation_type;
        a.operation().type(operation_type::ignore);

        using meta_model::operation_reason;
        a.operation().reason(operation_reason::ignore_unexpected);

        m.artefacts().push_back(a);
    }

    for (const auto& f : fbs.unexpected()) {
        meta_model::artefact a;
        a.path(f);

        using meta_model::operation_type;
        a.operation().type(operation_type::remove);

        using meta_model::operation_reason;
        a.operation().reason(operation_reason::unexpected);

        m.artefacts().push_back(a);
    }

    stp.end_transform(fbs);
}

}
