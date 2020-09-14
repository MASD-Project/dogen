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
#include <boost/make_shared.hpp>
#include "dogen.identification/types/entities/physical_id.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/operation_reason.hpp"
#include "dogen.physical/types/entities/operation_type.hpp"
#include "dogen.physical/io/helpers/files_by_status_io.hpp"
#include "dogen.physical/types/helpers/file_status_collector.hpp"
#include "dogen.physical/types/transforms/gather_external_artefacts_transform.hpp"

namespace {

const std::string transform_id(
    "physical.transforms.gather_external_artefacts_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

boost::shared_ptr<entities::artefact>
gather_external_artefacts_transform::make_artefact(
    const boost::filesystem::path& p,
    const entities::operation_type ot,
    const entities::operation_reason rsn) {

    auto r(boost::make_shared<entities::artefact>());
    r->name().simple(p.filename().generic_string());
    r->name().id(identification::entities::physical_id(p.generic_string()));
    r->file_path(p);
    r->operation().type(ot);
    r->operation().reason(rsn);

    return r;
}

void gather_external_artefacts_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "gather external artefacts transform", transform_id, m.name().simple(),
        *ctx.tracer(), m);

    /*
     * Collect all files with a status worth looking at. If nothing
     * turns up, we're done.
     */
    const auto fbs(helpers::file_status_collector::collect(m));
    if (fbs.unexpected().empty() && fbs.ignored().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No files found.";
        return;
    }

    using entities::operation_type;
    using entities::operation_reason;
    using entities::artefact;

    /*
     * Now, for each file, generate artefacts with the appropriate
     * operations and add them to the model. First, we mark files that
     * are ignored because the suer supplied regexes for them.
     */
    for (const auto& f : fbs.ignored()) {
        const auto ot(operation_type::ignore);
        const auto rsn(operation_reason::ignore_regex);
        m.orphan_artefacts().push_back(make_artefact(f, ot, rsn));
    }

    /*
     * Finally, we handle unexpected files. If the user asked us to
     * delete extra files, we need to mark them for removal;
     * otherwise, they should be ignored (for the right reasons).
     */
    const auto def(m.outputting_properties().delete_extra_files());
    for (const auto& f : fbs.unexpected()) {
        const auto ot(def ? operation_type::remove : operation_type::ignore);
        const auto rsn(def ? operation_reason::unexpected :
            operation_reason::ignore_unexpected);
        m.orphan_artefacts().push_back(make_artefact(f, ot, rsn));
    }

    stp.end_transform(fbs);
}

}
