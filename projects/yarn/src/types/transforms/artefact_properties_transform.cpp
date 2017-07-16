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
#include <functional>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/meta_model/artefact_properties.hpp"
#include "dogen/yarn/types/meta_model/elements_traversal.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/artefact_properties_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("yarn.transforms.artefact_properties_transform"));

const std::string duplicate_archetype("Duplicate archetype: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

void artefact_properties_transform::
update_element(const context& ctx, meta_model::element& e) {
    /*
     * Check to see if the element has any archetypes. Some elements
     * such as concepts do not have any at present.
     */
    const auto id(e.name().id());
    const auto ti(std::type_index(typeid(e)));
    const auto& c(ctx.archetype_locations_by_element_type_index());
    const auto i(c.find(ti));
    if (i == c.end()) {
        BOOST_LOG_SEV(lg, debug) << "Element has no archetypes: " << id;
        return;
    }
    BOOST_LOG_SEV(lg, debug) << "Element has archetypes " << id;

    /*
     * Perform the artefact expansion by looking at all the archetype
     * locations available in the context. These were originally
     * sourced from the formatters available in each kernel.
     */
    auto& ap(e.element_properties().artefact_properties());
    for (const auto& al : i->second) {
        const auto a(al.archetype());
        const auto pair(std::make_pair(a, meta_model::artefact_properties()));
        const auto inserted(ap.insert(pair).second);
        if (inserted)
            continue;

        BOOST_LOG_SEV(lg, error) << duplicate_archetype << a;
        BOOST_THROW_EXCEPTION(transformation_error(duplicate_archetype + a));

        BOOST_LOG_SEV(lg, debug) << "Added archetype location: " << a
                                 << " to element: " << id;
    }
}

void artefact_properties_transform::
transform(const context& ctx, meta_model::intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Started artefact properties transform.";

    using namespace std::placeholders;
    const auto f(artefact_properties_transform::update_element);
    const auto v(std::bind(f, ctx, _1));
    const bool include_injected_elements(true);
    meta_model::elements_traversal(im, v, include_injected_elements);

    BOOST_LOG_SEV(lg, debug) << "Finished artefact properties transform.";
}

} } }
