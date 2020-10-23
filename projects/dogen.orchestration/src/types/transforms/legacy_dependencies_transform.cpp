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
#include <sstream>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/legacy_dependencies_transform.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.legacy_dependencies_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_id("Duplicate logical-physical ID: ");

}

namespace dogen::orchestration::transforms {

using physical::entities::inclusion_directives;
using identification::entities::logical_meta_physical_id;

std::unordered_map<logical_meta_physical_id, inclusion_directives>
legacy_dependencies_transform::
get_inclusion_directives(const physical::entities::model& m) {
    std::unordered_map<logical_meta_physical_id, inclusion_directives> r;

    for (const auto& region_pair : m.regions_by_logical_id()) {
        const auto& region(region_pair.second);
        for (const auto& artefact_pair  : region.artefacts_by_archetype()) {
            const auto& a(*artefact_pair.second);

            const auto& directives(a.path_properties().inclusion_directives());
            const auto pair(std::make_pair(a.id(), directives));
            const bool inserted(r.insert(pair).second);
            if (!inserted) {
                std::ostringstream os;
                os << duplicate_id
                   << a.id().logical_id().value() << "-"
                   << a.id().physical_meta_id().value();
                const auto msg(os.str());
                BOOST_LOG_SEV(lg, error) << msg;
                BOOST_THROW_EXCEPTION(transform_exception(msg));
            }
        }
    }
    return r;
}

void legacy_dependencies_transform::apply(const text::transforms::context& ctx,
    text::entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "legacy dependencies",
        transform_id, m.logical().name().id().value(), *ctx.tracer(), m);

    const auto ids(get_inclusion_directives(m.physical()));

    stp.end_transform(m);
}

}
