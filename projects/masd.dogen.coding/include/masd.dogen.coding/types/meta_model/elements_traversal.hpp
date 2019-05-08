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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_ELEMENTS_TRAVERSAL_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_ELEMENTS_TRAVERSAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/structural/object.hpp"
#include "masd.dogen.coding/types/meta_model/structural/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/structural/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/structural/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/structural/exception.hpp"
#include "masd.dogen.coding/types/meta_model/structural/visitor.hpp"
#include "masd.dogen.coding/types/meta_model/structural/module.hpp"
#include "masd.dogen.coding/types/meta_model/structural/object_template.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/licence.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/modeline.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/modeline_group.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/generation_marker.hpp"
#include "masd.dogen.coding/types/meta_model/variability/profile_template.hpp"

namespace masd::dogen::coding::meta_model {

/**
 * @brief Performs a traversal across all elements in an intermediate
 * model.
 */
/**@{*/
template<typename TraversalVisitor>
inline void elements_traversal(const meta_model::model& m,
    const TraversalVisitor& v) {
    for (const auto& pair : m.modules())
        v(*pair.second);

    for (const auto& pair : m.object_templates())
        v(*pair.second);

    for (const auto& pair : m.builtins())
        v(*pair.second);

    for (const auto& pair : m.enumerations())
        v(*pair.second);

    for (const auto& pair : m.primitives())
        v(*pair.second);

    for (const auto& pair : m.objects())
        v(*pair.second);

    for (const auto& pair : m.exceptions())
        v(*pair.second);

    for (const auto& pair : m.visitors())
        v(*pair.second);

    for (const auto& pair : m.licences())
        v(*pair.second);

    for (const auto& pair : m.modelines())
        v(*pair.second);

    for (const auto& pair : m.modeline_groups())
        v(*pair.second);

    for (const auto& pair : m.generation_markers())
        v(*pair.second);

    for (const auto& pair : m.variability_profile_templates())
        v(*pair.second);
}

template<typename TraversalVisitor>
inline void elements_traversal(const meta_model::model& m,
    TraversalVisitor& v) {
    for (auto& pair : m.modules())
        v(*pair.second);

    for (auto& pair : m.object_templates())
        v(*pair.second);

    for (auto& pair : m.builtins())
        v(*pair.second);

    for (auto& pair : m.enumerations())
        v(*pair.second);

    for (auto& pair : m.primitives())
        v(*pair.second);

    for (auto& pair : m.objects())
        v(*pair.second);

    for (auto& pair : m.exceptions())
        v(*pair.second);

    for (auto& pair : m.visitors())
        v(*pair.second);

    for (const auto& pair : m.licences())
        v(*pair.second);

    for (const auto& pair : m.modelines())
        v(*pair.second);

    for (const auto& pair : m.modeline_groups())
        v(*pair.second);

    for (const auto& pair : m.generation_markers())
        v(*pair.second);

    for (const auto& pair : m.variability_profile_templates())
        v(*pair.second);
}

template<typename TraversalVisitor>
inline void elements_traversal(meta_model::model& m,
    TraversalVisitor& v) {
    for (auto& pair : m.modules())
        v(*pair.second);

    for (auto& pair : m.object_templates())
        v(*pair.second);

    for (auto& pair : m.builtins())
        v(*pair.second);

    for (auto& pair : m.enumerations())
        v(*pair.second);

    for (auto& pair : m.primitives())
        v(*pair.second);

    for (auto& pair : m.objects())
        v(*pair.second);

    for (auto& pair : m.exceptions())
        v(*pair.second);

    for (auto& pair : m.visitors())
        v(*pair.second);

    for (const auto& pair : m.licences())
        v(*pair.second);

    for (const auto& pair : m.modelines())
        v(*pair.second);

    for (const auto& pair : m.modeline_groups())
        v(*pair.second);

    for (const auto& pair : m.generation_markers())
        v(*pair.second);

    for (const auto& pair : m.variability_profile_templates())
        v(*pair.second);
}
/**@}*/

/**
 * @brief Performs a traversal across all element pointers in an
 * intermediate model.
 */
/**@{*/
template<typename TraversalVisitor>
inline void shared_elements_traversal(const meta_model::model& m,
    const TraversalVisitor& v) {
    for (const auto& pair : m.modules())
        v(pair.second);

    for (const auto& pair : m.object_templates())
        v(pair.second);

    for (const auto& pair : m.builtins())
        v(pair.second);

    for (const auto& pair : m.enumerations())
        v(pair.second);

    for (const auto& pair : m.primitives())
        v(pair.second);

    for (const auto& pair : m.objects())
        v(pair.second);

    for (const auto& pair : m.exceptions())
        v(pair.second);

    for (const auto& pair : m.visitors())
        v(pair.second);

    for (const auto& pair : m.licences())
        v(pair.second);

    for (const auto& pair : m.modelines())
        v(pair.second);

    for (const auto& pair : m.modeline_groups())
        v(pair.second);

    for (const auto& pair : m.generation_markers())
        v(pair.second);

    for (const auto& pair : m.variability_profile_templates())
        v(pair.second);
}

template<typename TraversalVisitor>
inline void shared_elements_traversal(const meta_model::model& m,
    TraversalVisitor& v) {
    for (auto& pair : m.modules())
        v(pair.second);

    for (auto& pair : m.object_templates())
        v(pair.second);

    for (auto& pair : m.builtins())
        v(pair.second);

    for (auto& pair : m.enumerations())
        v(pair.second);

    for (auto& pair : m.primitives())
        v(pair.second);

    for (auto& pair : m.objects())
        v(pair.second);

    for (auto& pair : m.exceptions())
        v(pair.second);

    for (auto& pair : m.visitors())
        v(pair.second);

    for (const auto& pair : m.licences())
        v(pair.second);

    for (const auto& pair : m.modelines())
        v(pair.second);

    for (const auto& pair : m.modeline_groups())
        v(pair.second);

    for (const auto& pair : m.generation_markers())
        v(pair.second);

    for (const auto& pair : m.variability_profile_templates())
        v(pair.second);
}

template<typename TraversalVisitor>
inline void shared_elements_traversal(meta_model::model& m,
    TraversalVisitor& v) {
    for (auto& pair : m.modules())
        v(pair.second);

    for (auto& pair : m.object_templates())
        v(pair.second);

    for (auto& pair : m.builtins())
        v(pair.second);

    for (auto& pair : m.enumerations())
        v(pair.second);

    for (auto& pair : m.primitives())
        v(pair.second);

    for (auto& pair : m.objects())
        v(pair.second);

    for (auto& pair : m.exceptions())
        v(pair.second);

    for (auto& pair : m.visitors())
        v(pair.second);

    for (const auto& pair : m.licences())
        v(pair.second);

    for (const auto& pair : m.modelines())
        v(pair.second);

    for (const auto& pair : m.modeline_groups())
        v(pair.second);

    for (const auto& pair : m.generation_markers())
        v(pair.second);

    for (const auto& pair : m.variability_profile_templates())
        v(pair.second);
}
/**@}*/

}

#endif
