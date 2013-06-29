/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/types/injector.hpp"
#include "dogen/sml/types/primitive_model_factory.hpp"
#include "dogen/sml/types/std_model_factory.hpp"
#include "dogen/sml/types/boost_model_factory.hpp"
#include "dogen/sml/types/merger.hpp"
#include "dogen/sml/types/resolver.hpp"
#include "dogen/sml/types/workflow.hpp"

namespace dogen {
namespace sml {

workflow::workflow() : add_system_models_(true) {}

workflow::
workflow(const bool add_system_models)
    : add_system_models_(add_system_models) {}

bool workflow::is_generatable(const type& t) const {
    const auto gt(t.generation_type());
    return
        gt == sml::generation_types::full_generation ||
        gt == sml::generation_types::partial_generation;
}

bool workflow::has_generatable_types(const sml::model& m) const {
    for (const auto pair : m.objects()) {
        if (is_generatable(*pair.second))
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

    return false;
}

std::list<model>
workflow::augment_references_activity(const std::list<model>& references) {
    std::list<model> r(references);
    if (add_system_models_) {
        r.push_back(sml::primitive_model_factory::create());
        r.push_back(sml::std_model_factory::create());
        r.push_back(sml::boost_model_factory::create());
    }
    return r;
}

model workflow::create_merged_model_activity(const model& target,
    const std::list<model>& references) {

    injector i;
    auto t(target);
    i.inject(t);

    merger mg;
    mg.add_target(t);

    for (auto r : references) {
        i.inject(r);
        mg.add(r);
    }
    return mg.merge();
}

void workflow::resolve_types_activity(model& merged_model) {
    resolver res(merged_model);
    res.resolve();
}

std::pair<bool, model> workflow::
execute(const model& target, const std::list<model>& references) {
    const auto augment_references(augment_references_activity(references));
    auto r(create_merged_model_activity(target, augment_references));
    resolve_types_activity(r);
    return std::pair<bool, model> { has_generatable_types(r), r };
}

} }
