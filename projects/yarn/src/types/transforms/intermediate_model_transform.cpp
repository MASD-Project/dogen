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
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/intermediate_model_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.builder"));

const std::string duplicate_element_id("Element id already exists: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

template<typename Element>
inline std::unordered_map<std::string, boost::shared_ptr<Element>>
to_element_map(const std::list<std::pair<annotations::scribble_group,
    boost::shared_ptr<Element>>>& elements) {

    std::unordered_map<std::string, boost::shared_ptr<Element>> r;
    for (const auto pair : elements) {
        const auto e(pair.second);
        const auto id(e->name().id());

        bool inserted(r.insert(std::make_pair(id, e)).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element_id << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_element_id + id));
        }
    }
    return r;
}

meta_model::intermediate_model intermediate_model_transform::
transform(const meta_model::exogenous_model& em) {
    BOOST_LOG_SEV(lg, debug) << "Transforming exogenous model "
                             << "intermediate model.";

    meta_model::intermediate_model r;
    r.modules(to_element_map(em.modules()));
    r.concepts(to_element_map(em.concepts()));
    r.builtins(to_element_map(em.builtins()));
    r.enumerations(to_element_map(em.enumerations()));
    r.primitives(to_element_map(em.primitives()));
    r.objects(to_element_map(em.objects()));
    r.exceptions(to_element_map(em.exceptions()));

    BOOST_LOG_SEV(lg, debug) << "Transformed exogenous model "
                             << "intermediate model.";
    return r;
}

} } }
