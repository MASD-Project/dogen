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

bool assembler::has_generatable_types(const model& m) const {
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

    // FIXME: add concepts, etc.

    return false;
}

model assembler::
create_merged_model_activity(const std::list<model>& models) const {
    merger mg;
    for (const auto& m : models)
        mg.add(m);

    return mg.merge();
}

void assembler::index_generalizations_activity(model& merged_model) const {
    generalization_indexer idx;
    idx.index(merged_model);
}

void assembler::inject_system_types_activity(model& m) const {
    injector i;
    i.inject(m);
}

void assembler::resolve_types_activity(model& merged_model) const {
    resolver res(merged_model);
    res.resolve();
}

void assembler::index_concepts_activity(model& merged_model) const {
    concept_indexer idx;
    idx.index(merged_model);
}

void assembler::index_properties_activity(model& merged_model) const {
    property_indexer idx;
    idx.index(merged_model);
}

void assembler::index_associations_activity(model& merged_model) const {
    association_indexer idx;
    idx.index(merged_model);
}

void assembler::update_model_generability_activity(model& merged_model) const {
    merged_model.has_generatable_types(has_generatable_types(merged_model));
}

model assembler::assemble(const std::list<model>& models) const {
    BOOST_LOG_SEV(lg, debug) << "Starting model assembly.";

    auto r(create_merged_model_activity(models));
    index_generalizations_activity(r);
    inject_system_types_activity(r);
    resolve_types_activity(r);
    index_concepts_activity(r);
    index_properties_activity(r);
    index_associations_activity(r);
    update_model_generability_activity(r);

    BOOST_LOG_SEV(lg, debug) << "Finished assembling models.";

    return r;
}

} }
