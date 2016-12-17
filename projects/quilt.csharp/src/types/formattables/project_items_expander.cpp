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
#include <set>
#include <algorithm>
#include"dogen/yarn/types/object.hpp"
#include"dogen/yarn/types/visitor.hpp"
#include"dogen/yarn/types/primitive.hpp"
#include"dogen/yarn/types/exception.hpp"
#include"dogen/yarn/types/enumeration.hpp"
#include "dogen/quilt.csharp/types/fabric/assistant.hpp"
#include "dogen/quilt.csharp/types/formattables/project_items_expander.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

bool project_items_expander::is_project_item(const std::type_index& ti) const {
    return
        ti == std::type_index(typeid(fabric::assistant)) ||
        ti == std::type_index(typeid(yarn::enumeration)) ||
        ti == std::type_index(typeid(yarn::exception)) ||
        ti == std::type_index(typeid(yarn::object)) ||
        ti == std::type_index(typeid(yarn::primitive)) ||
        ti == std::type_index(typeid(yarn::visitor));
}

void project_items_expander::expand(model& fm) const {
    std::set<std::string> set;
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& e(*formattable.element());

        const auto ti(std::type_index(typeid(e)));
        if (!is_project_item(ti))
            continue;

        const auto& eprops(formattable.element_properties());
        for (const auto& art_pair : eprops.artefact_properties()) {
            const auto art_props(art_pair.second);

            /*
             * Ensure the item path uses backslashes for compatibility
             * with Visual Studio and MonoDevelop.
             */
            auto rp(art_props.relative_path().generic_string());
            std::replace(rp.begin(), rp.end(), '/', '\\');
            set.insert(rp);
        }
    }

    for (const auto& p : set)
        fm.project_items().push_back(p);
}

} } } }
