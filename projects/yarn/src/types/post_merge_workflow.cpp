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
#include <boost/filesystem/path.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/indexer.hpp"
#include "dogen/yarn/types/injector.hpp"
#include "dogen/yarn/types/resolver.hpp"
#include "dogen/yarn/types/concept_expander.hpp"
#include "dogen/yarn/types/attributes_expander.hpp"
#include "dogen/yarn/types/association_expander.hpp"
#include "dogen/yarn/types/generalization_expander.hpp"
#include "dogen/yarn/types/post_merge_workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.post_merge_workflow"));

}

namespace dogen {
namespace yarn {

bool post_merge_workflow::is_generatable(const element& e) const {
    const auto gt(e.generation_type());
    return
        gt == generation_types::full_generation ||
        gt == generation_types::partial_generation;
}

bool post_merge_workflow::
has_generatable_types(const intermediate_model& im) const {
    for (const auto pair : im.objects()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : im.enumerations()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : im.enumerations()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : im.primitives()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : im.concepts()) {
        if (is_generatable(pair.second))
            return true;
    }

    return false;
}

void post_merge_workflow::create_indices(intermediate_model& im) const {
    indexer idx;
    idx.index(im);
}

void post_merge_workflow::inject_system_elements(intermediate_model& im) const {
    injector i;
    i.inject(im);
}

void post_merge_workflow::
resolve_element_references(intermediate_model& im) const {
    resolver rs;
    rs.resolve(im);
}

void post_merge_workflow::expand_generalizations(intermediate_model& im) const {
    generalization_expander ex;
    ex.expand(im);
}

void post_merge_workflow::expand_concepts(intermediate_model& im) const {
    concept_expander ex;
    ex.expand(im);
}

void post_merge_workflow::expand_attributes(intermediate_model& im) const {
    attributes_expander ex;
    ex.expand(im);
}

void post_merge_workflow::expand_associations(intermediate_model& im) const {
    association_expander ex;
    ex.expand(im);
}

void post_merge_workflow::
update_model_generability(intermediate_model& im) const {
    im.has_generatable_types(has_generatable_types(im));
}

void post_merge_workflow::execute(intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";

    /*
     * Create all indices first as its needed by generalisation. Note
     * that this means injected types are not part of indices, which
     * is not ideal - but for now, its not a major problem.
     */
    create_indices(im);

    /*
     * We must expand generalisation relationships before we inject
     * system elements because we need to know about leaves before we
     * can generate visitors.
     */
    expand_generalizations(im);
    inject_system_elements(im);

    /*
     * Resolution must be done after system elements have been
     * injected or else it will fail to find any references to those
     * elements.
     */
    resolve_element_references(im);
    expand_concepts(im);
    expand_attributes(im);

    /*
     * We must expand associations after attributes have been expanded
     * as it relies on the various attribute containers being
     * populated.
     */
    expand_associations(im);
    update_model_generability(im);

    BOOST_LOG_SEV(lg, debug) << "Finished workflow.";
}

} }
