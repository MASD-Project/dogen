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
#include "dogen/annotations/types/scribble_group.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/helpers/model_sorter.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

template<typename Element> bool
comparer(const std::pair<annotations::scribble_group,
    boost::shared_ptr<Element>>& lhs,
    const std::pair<annotations::scribble_group,
    boost::shared_ptr<Element>>& rhs) {
    return lhs.second->name().id() < rhs.second->name().id();
}

void model_sorter::sort(dogen::yarn::meta_model::exogenous_model& em) {
    em.modules().sort(comparer<dogen::yarn::meta_model::module>);
    em.concepts().sort(comparer<dogen::yarn::meta_model::concept>);
    em.builtins().sort(comparer<dogen::yarn::meta_model::builtin>);
    em.enumerations().sort(comparer<dogen::yarn::meta_model::enumeration>);
    em.primitives().sort(comparer<dogen::yarn::meta_model::primitive>);
    em.objects().sort(comparer<dogen::yarn::meta_model::object>);
    em.exceptions().sort(comparer<dogen::yarn::meta_model::exception>);
}

} } }
