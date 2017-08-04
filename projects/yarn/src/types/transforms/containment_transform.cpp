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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/containment_transform.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.containment_transform"));

const std::string global_module_doc("Module that represents the global scope.");
const std::string model_already_has_global_module(
    "Found a global module in model: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

template<typename AssociativeContainerOfContainable>
inline void add_containing_module_to_non_contained_entities(
    const meta_model::name& container_name,
    AssociativeContainerOfContainable& c) {
    for (auto& pair : c) {
        auto& s(*pair.second);
        if (!s.contained_by())
            s.contained_by(container_name);
    }
}

boost::shared_ptr<meta_model::module>
containment_transform::create_global_module(const meta_model::origin_types ot) {
    auto r(boost::make_shared<meta_model::module>());
    r->name().id("<global module>");
    r->origin_type(ot);
    r->documentation(global_module_doc);
    r->is_global_module(true);
    return r;
}

void containment_transform::
inject_global_module(meta_model::intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Injecting global module for: "
                             << im.name().id();

    const auto gm(create_global_module(im.origin_type()));
    const auto gmn(gm->name());
    const auto i(im.modules().find(gmn.id()));
    if (i != im.modules().end()) {
        const auto id(im.name().id());
        BOOST_LOG_SEV(lg, error) << model_already_has_global_module << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(model_already_has_global_module + id));
    }
    im.modules().insert(std::make_pair(gmn.id(), gm));

    add_containing_module_to_non_contained_entities(gmn, im.modules());
    add_containing_module_to_non_contained_entities(gmn, im.concepts());
    add_containing_module_to_non_contained_entities(gmn, im.builtins());
    add_containing_module_to_non_contained_entities(gmn, im.enumerations());
    add_containing_module_to_non_contained_entities(gmn, im.objects());
    add_containing_module_to_non_contained_entities(gmn, im.exceptions());
    add_containing_module_to_non_contained_entities(gmn, im.visitors());
    add_containing_module_to_non_contained_entities(gmn, im.primitives());

    BOOST_LOG_SEV(lg, debug) << "Done injecting global module";
}

void containment_transform::transform(meta_model::intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding containment for: " << im.name().id();
    inject_global_module(im);
    BOOST_LOG_SEV(lg, debug) << "Finished expanding containment.";
}

} } }
