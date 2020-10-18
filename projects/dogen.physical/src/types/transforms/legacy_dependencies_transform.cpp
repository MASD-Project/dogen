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
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/legacy_dependencies_transform.hpp"

namespace {

const std::string
transform_id("physical.transforms.legacy_dependencies_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_id("Duplicate logical-physical ID: ");

}

namespace dogen::physical::transforms {

using entities::inclusion_directives;
using identification::entities::logical_meta_physical_id;

std::unordered_map<logical_meta_physical_id, inclusion_directives>
legacy_dependencies_transform::
get_inclusion_directives(const entities::model& m) {
    std::unordered_map<logical_meta_physical_id, inclusion_directives> r;
    for (const auto& region_pair : m.regions_by_logical_id()) {
        const auto& region(region_pair.second);
        for (const auto& arch_pair : region.artefacts_by_archetype()) {
            const auto& a(*arch_pair.second);

            logical_meta_physical_id id;
            id.logical_id(a.provenance().logical_name().id());
            id.physical_meta_id(a.meta_name().id());

            const auto& dir(a.path_properties().inclusion_directives());
            const auto inserted(r.insert(std::make_pair(id, dir)).second);
            if (!inserted) {
                std::ostringstream os;
                os << duplicate_id << id.logical_id().value() << "-"
                   << id.physical_meta_id().value();
                const auto s(os.str());
                BOOST_LOG_SEV(lg, error) << s;
                BOOST_THROW_EXCEPTION(transform_exception(s));
            }
        }
    }
    return r;
}

void
legacy_dependencies_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "legacy dependencies",
        transform_id, m.name().id().value(), *ctx.tracer(), m);

    const auto ids(get_inclusion_directives(m));

    stp.end_transform(m);
}

}
