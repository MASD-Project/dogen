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
#include "dogen.physical/types/entities/location_repository.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/artefact_properties.hpp"
#include "dogen.m2t/io/entities/model_io.hpp"
#include "dogen.m2t/types/transforms/transformation_error.hpp"
#include "dogen.m2t/types/transforms/artefact_properties_transform.hpp"

namespace {

const std::string transform_id(
    "generation.transforms.artefact_properties_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_archetype("Duplicate archetype: ");

}

namespace dogen::m2t::transforms {

void artefact_properties_transform::
update_element(const context& ctx, logical::entities::element& e) {
    /*
     * Check to see if the element has any archetypes. Some elements
     * such as object templates do not have any at present.
     */
    const auto id(e.name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Updating element: " << id;

    const auto mn(e.meta_name().qualified().dot());
    const auto& alrp(*ctx.archetype_location_repository());
    const auto& c(alrp.by_meta_name());
    const auto i(c.find(mn));
    if (i == c.end()) {
        BOOST_LOG_SEV(lg, debug) << "No archetypes for meta-name: " << mn;
        return;
    }
    BOOST_LOG_SEV(lg, debug) << "Element has archetypes.";

    /*
     * Perform the artefact expansion by looking at all the archetype
     * locations available in the context. These were originally
     * sourced from the formatting available in each backend.
     */
    auto& ap(e.artefact_properties());
    for (const auto& al : i->second.locations()) {
        const auto a(al.archetype());
        using logical::entities::artefact_properties;
        const auto pair(std::make_pair(a, artefact_properties()));
        const auto inserted(ap.insert(pair).second);
        if (inserted) {
            BOOST_LOG_SEV(lg, debug) << "Added archetype location: " << a;
            continue;
        }

        BOOST_LOG_SEV(lg, error) << duplicate_archetype << a;
        BOOST_THROW_EXCEPTION(transformation_error(duplicate_archetype + a));
    }
}

void artefact_properties_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "artefact properties transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    for(auto& ptr : m.elements())
        update_element(ctx, *ptr);

    stp.end_transform(m);
}

}
