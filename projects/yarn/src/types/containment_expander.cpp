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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/injection_error.hpp"
#include "dogen/yarn/types/containment_expander.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.containment_expander"));

const std::string global_module_doc("Module that represents the global scope.");
const std::string model_already_has_global_module(
    "Found a global module in model: ");

}

namespace dogen {
namespace yarn {

template<typename AssociativeContainerOfContainable>
inline void add_containing_module_to_non_contained_entities(
    const name& container_name, AssociativeContainerOfContainable& c) {
    for (auto& pair : c) {
        auto& s(pair.second);
        if (!s.contained_by())
            s.contained_by(container_name);
    }
}

module containment_expander::create_global_module(const origin_types ot) const {
    module r;
    r.origin_type(ot);
    r.documentation(global_module_doc);
    r.is_global_module(true);
    return r;
}

void containment_expander::inject_global_module(intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Injecting global module for: "
                             << im.name().id();

    const auto gm(create_global_module(im.origin_type()));
    const auto gmn(gm.name());
    const auto i(im.modules().find(gmn.id()));
    if (i != im.modules().end()) {
        const auto id(im.name().id());
        BOOST_LOG_SEV(lg, error) << model_already_has_global_module << id;
        BOOST_THROW_EXCEPTION(
            injection_error(model_already_has_global_module + id));
    }
    im.modules().insert(std::make_pair(gmn.id(), gm));

    add_containing_module_to_non_contained_entities(gmn, im.modules());
    add_containing_module_to_non_contained_entities(gmn, im.concepts());
    add_containing_module_to_non_contained_entities(gmn, im.primitives());
    add_containing_module_to_non_contained_entities(gmn, im.enumerations());
    add_containing_module_to_non_contained_entities(gmn, im.objects());
    add_containing_module_to_non_contained_entities(gmn, im.exceptions());
    add_containing_module_to_non_contained_entities(gmn, im.visitors());

    BOOST_LOG_SEV(lg, debug) << "Done injecting global module";
}

void containment_expander::expand(intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding containment for: " << im.name().id();
    inject_global_module(im);
    BOOST_LOG_SEV(lg, debug) << "Finished expanding containment.";
}

} }
