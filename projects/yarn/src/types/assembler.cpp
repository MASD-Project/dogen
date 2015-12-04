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
#include "dogen/yarn/types/injector.hpp"
#include "dogen/yarn/types/resolver.hpp"
#include "dogen/yarn/types/concept_indexer.hpp"
#include "dogen/yarn/types/property_indexer.hpp"
#include "dogen/yarn/types/association_indexer.hpp"
#include "dogen/yarn/types/generalization_indexer.hpp"
#include "dogen/yarn/types/assembler.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.assembler"));

}

namespace dogen {
namespace yarn {

bool assembler::is_generatable(const element& e) const {
    const auto gt(e.generation_type());
    return
        gt == generation_types::full_generation ||
        gt == generation_types::partial_generation;
}

bool assembler::has_generatable_types(const intermediate_model& m) const {
    for (const auto pair : m.objects()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : m.enumerations()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : m.enumerations()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : m.primitives()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : m.concepts()) {
        if (is_generatable(pair.second))
            return true;
    }

    return false;
}

intermediate_model assembler::create_merged_model_activity(
    const std::list<intermediate_model>& models) const {
    merger mg;
    for (const auto& m : models)
        mg.add(m);

    return mg.merge();
}

void assembler::
inject_system_elements_activity(intermediate_model& merged_model) const {
    injector i;
    i.inject(merged_model);
}

void assembler::
resolve_element_references_activity(intermediate_model& merged_model) const {
    resolver res(merged_model);
    res.resolve();
}

void assembler::
index_generalizations_activity(intermediate_model& merged_model) const {
    generalization_indexer idx;
    idx.index(merged_model);
}

void assembler::
index_concepts_activity(intermediate_model& merged_model) const {
    concept_indexer idx;
    idx.index(merged_model);
}

void assembler::
index_properties_activity(intermediate_model& merged_model) const {
    property_indexer idx;
    idx.index(merged_model);
}

void assembler::
index_associations_activity(intermediate_model& merged_model) const {
    association_indexer idx;
    idx.index(merged_model);
}

void assembler::
update_model_generability_activity(intermediate_model& merged_model) const {
    merged_model.has_generatable_types(has_generatable_types(merged_model));
}

intermediate_model assembler::
assemble(const std::list<intermediate_model>& models) const {
    BOOST_LOG_SEV(lg, debug) << "Starting model assembly.";

    auto r(create_merged_model_activity(models));

    /* We must index generalisation relationships before we inject
     * system elements because we need to know about leaves before we
     * can generate visitors.
     */
    index_generalizations_activity(r);
    inject_system_elements_activity(r);

    /* Resolution must be done after system elements have been
     * injected or else it will fail to find any references to those
     * elements.
     */
    resolve_element_references_activity(r);
    index_concepts_activity(r);
    index_properties_activity(r);

    /* We must index associations after properties have been indexed
     * as it relies on the various property containers being populated.
     */
    index_associations_activity(r);
    update_model_generability_activity(r);

    BOOST_LOG_SEV(lg, debug) << "Finished assembling model.";
    BOOST_LOG_SEV(lg, debug) << "Totals: objects: " << r.objects().size()
                             << " modules: " << r.modules().size()
                             << " concepts: " << r.concepts().size()
                             << " enumerations: " << r.enumerations().size()
                             << " primitives: " << r.primitives().size();

    return r;
}

} }
