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
#include "dogen/sml/types/system_types_injector.hpp"
#include "dogen/sml/types/primitive_model_factory.hpp"
#include "dogen/sml/types/std_model_factory.hpp"
#include "dogen/sml/types/boost_model_factory.hpp"
#include "dogen/sml/types/workflow.hpp"

namespace dogen {
namespace sml {

workflow::workflow() : add_system_models_(true), add_versioning_types_(true) {}

workflow::
workflow(const bool add_system_models, const bool add_versioning_types)
    : add_system_models_(add_system_models),
      add_versioning_types_(add_versioning_types) {}

bool workflow::has_generatable_types(const sml::model& m) const {
    auto lambda([](sml::generation_types gt) {
            return
                gt == sml::generation_types::full_generation ||
                gt == sml::generation_types::partial_generation;
        });

    for (const auto pair : m.pods()) {
        if (lambda(pair.second.generation_type()))
            return true;
    }

    for (const auto pair : m.enumerations()) {
        if (lambda(pair.second.generation_type()))
            return true;
    }

    for (const auto pair : m.exceptions()) {
        if (lambda(pair.second.generation_type()))
            return true;
    }

    return false;
}

void workflow::add_system_models() {
    if (!add_system_models_)
        return;

    merger_.add(sml::primitive_model_factory::create());
    merger_.add(sml::std_model_factory::create());
    merger_.add(sml::boost_model_factory::create());
}

void workflow::add_references(const model_source_interface& source) {
    system_types_injector sti(add_versioning_types_);
    for (auto& r : source.references()) {
        sti.inject(r);
        merger_.add(r);
    }
}

void workflow::add_target(const model_source_interface& source) {
    system_types_injector sti(add_versioning_types_);
    auto t(source.target());
    sti.inject(t);
    merger_.add_target(t);
}

std::pair<bool, model> workflow::
execute(const model_source_interface& source) {
    add_system_models();
    add_references(source);
    add_target(source);

    const auto r(merger_.merge());
    return std::pair<bool, model> { has_generatable_types(r), r };
}

} }
