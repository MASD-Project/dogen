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
#include "dogen/yarn/types/merger.hpp"
#include "dogen/yarn/types/indexer.hpp"
#include "dogen/yarn/types/resolver.hpp"
#include "dogen/yarn/types/concept_expander.hpp"
#include "dogen/yarn/types/enumeration_expander.hpp"
#include "dogen/yarn/types/stereotypes_expander.hpp"
#include "dogen/yarn/types/containment_expander.hpp"
#include "dogen/yarn/types/attributes_expander.hpp"
#include "dogen/yarn/types/association_expander.hpp"
#include "dogen/yarn/types/generalization_expander.hpp"
#include "dogen/yarn/types/injection_expander.hpp"
#include "dogen/yarn/types/orm_properties_expander.hpp"
#include "dogen/yarn/types/second_stage_validator.hpp"
#include "dogen/yarn/types/second_stage_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.second_stage_expander"));

}

namespace dogen {
namespace yarn {

bool second_stage_expander::is_generatable(const element& e) const {
    const auto ot(e.origin_type());
    return ot == origin_types::target;
}

bool second_stage_expander::
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

    for (const auto pair : im.exceptions()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : im.builtins()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : im.concepts()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : im.primitives()) {
        if (is_generatable(pair.second))
            return true;
    }

    return false;
}

intermediate_model second_stage_expander::
merge_intermediate_models(const std::list<intermediate_model>& im) const {
    merger mg;
    for (const auto& m : im)
        mg.add(m);

    const auto r(mg.merge());

    BOOST_LOG_SEV(lg, debug) << "Totals: objects: " << r.objects().size()
                             << " modules: " << r.modules().size()
                             << " concepts: " << r.concepts().size()
                             << " enumerations: " << r.enumerations().size()
                             << " builtins: " << r.builtins().size();
    return r;
}

void second_stage_expander::
expand_enumerations(const annotations::type_repository& atrp,
    intermediate_model& im) const {
    enumeration_expander ex;
    ex.expand(atrp, im);
}

indices second_stage_expander::create_indices(intermediate_model& im) const {
    indexer idx;
    return idx.index(im);
}

void second_stage_expander::expand_stereotypes(intermediate_model& im) const {
    stereotypes_expander ex;
    ex.expand(im);
}

void second_stage_expander::expand_containment(intermediate_model& im) const {
    containment_expander ex;
    ex.expand(im);
}

void second_stage_expander::
expand_orm_properties(const annotations::type_repository& atrp,
    intermediate_model& im) const {
    orm_properties_expander ex;
    ex.expand(atrp, im);
}

void second_stage_expander::
resolve_element_references(const indices& idx, intermediate_model& im) const {
    resolver rs;
    rs.resolve(idx, im);
}

void second_stage_expander::
expand_generalizations(const annotations::type_repository& atrp,
    const indices& idx, intermediate_model& im) const {
    generalization_expander ex;
    ex.expand(atrp, idx, im);
}

void second_stage_expander::expand_concepts(intermediate_model& im) const {
    concept_expander ex;
    ex.expand(im);
}

void second_stage_expander::expand_attributes(intermediate_model& im) const {
    attributes_expander ex;
    ex.expand(im);
}

void second_stage_expander::expand_associations(intermediate_model& im) const {
    association_expander ex;
    ex.expand(im);
}

void second_stage_expander::
update_model_generability(intermediate_model& im) const {
    im.has_generatable_types(has_generatable_types(im));
}

void second_stage_expander::
inject_model(const annotations::type_repository& atrp,
    const injector_registrar& rg, intermediate_model& im) const {
    injection_expander ex;
    ex.expand(atrp, rg, im);
}

void second_stage_expander::
validate(const indices& idx, const intermediate_model& im) const {
    second_stage_validator v;
    v.validate(idx, im);
}

intermediate_model second_stage_expander::
make(const annotations::type_repository& atrp, const injector_registrar& rg,
    const std::list<intermediate_model>& ims) const {
    BOOST_LOG_SEV(lg, debug) << "Starting second stage expansion.";

    /*
     * First we must merge all of the intermediate models into the
     * merged model.
     */
    auto r(merge_intermediate_models(ims));

    /*
     * Enumeration expansion must be done after merging as we need the
     * built-in types; these are required in order to find the default
     * enumeration underlying element.
     */
    expand_enumerations(atrp, r);

    /*
     * Create all indices first as its needed by generalisation. Note
     * that this means injected types are not part of indices, which
     * is not ideal - but for now, its not a major problem.
     */
    const auto idx(create_indices(r));

    /*
     * We must expand generalisation relationships before we expand
     * stereotypes because we need to know about leaves before we can
     * generate visitors. Note also that generalisations must be
     * expanded after merging models because we may inherit across
     * models.
     */
    expand_generalizations(atrp, idx, r);

    /*
     * Stereotypes expansion must be done before concepts because we
     * obtain concept information from the stereotypes.
     */
    expand_stereotypes(r);
    expand_concepts(r);
    expand_containment(r);

    /*
     * ORM properties must be expanded after stereotypes and
     * containment.
     */
    expand_orm_properties(atrp, r);

    /*
     * Resolution must be done after system elements have been
     * injected or else it will fail to find any references to those
     * elements.
     */
    resolve_element_references(idx, r);

    /*
     * We can only expand attributes after we've expanded:
     *
     * - concepts, as we rely on all attributes obtained from modeling
     *   a concept already being present.
     * - stereotypes, as we need settings such as immutability and
     *   fluency to be populated.
     *  - resolution, else we will copy unresolved attributes.
     */
    expand_attributes(r);

    /*
     * We must expand associations after attributes have been expanded
     * as it relies on the various attribute containers being
     * populated.
     */
    expand_associations(r);
    update_model_generability(r);

    /*
     * We can inject types into the model last as no one should be
     * relying on them.
     */
    inject_model(atrp, rg, r);

    /*
     * Ensure the model is valid.
     */
    validate(idx, r);

    BOOST_LOG_SEV(lg, debug) << "Finished second stage expansion.";
    return r;
}

} }
