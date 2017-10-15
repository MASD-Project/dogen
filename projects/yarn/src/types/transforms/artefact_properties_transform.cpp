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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/types/meta_model/artefact_properties.hpp"
#include "dogen/yarn/io/meta_model/model_io.hpp"
#include "dogen/yarn/types/helpers/scoped_transform_probing.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/artefact_properties_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.artefact_properties_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_archetype("Duplicate archetype: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

void artefact_properties_transform::
update_element(const context& ctx, meta_model::element& e) {
    /*
     * Check to see if the element has any archetypes. Some elements
     * such as object templates do not have any at present.
     */
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Updating element: " << id;

    const auto mn(e.meta_name().id());
    const auto& alrp(ctx.archetype_location_repository());
    const auto& c(alrp.archetype_locations_by_meta_name());
    const auto i(c.find(mn));
    if (i == c.end()) {
        BOOST_LOG_SEV(lg, debug) << "No archetypes for meta-name: " << mn;
        return;
    }
    BOOST_LOG_SEV(lg, debug) << "Element has archetypes.";

    /*
     * Perform the artefact expansion by looking at all the archetype
     * locations available in the context. These were originally
     * sourced from the formatters available in each backend.
     */
    auto& ap(e.artefact_properties());
    for (const auto& al : i->second.archetype_locations()) {
        const auto a(al.archetype());
        const auto pair(std::make_pair(a, meta_model::artefact_properties()));
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
transform(const context& ctx, meta_model::model& m) {
    helpers::scoped_transform_probing stp(lg, "artefact properties transform",
        transform_id, m.name().id(), ctx.prober(), m);

    for(auto& ptr : m.elements())
        update_element(ctx, *ptr);

    stp.end_transform(m);
}

} } }
