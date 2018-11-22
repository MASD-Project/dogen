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
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.generation.csharp/types/fabric/assistant.hpp"
#include "masd.dogen.generation.csharp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.csharp/types/formattables/project_items_expander.hpp"

namespace masd::dogen::generation::csharp::formattables {

std::unordered_set<std::string>
project_items_expander::meta_names_for_project_items() {
    std::unordered_set<std::string> r;

    using ymnf = coding::helpers::meta_name_factory;
    r.insert(ymnf::make_enumeration_name().id());
    r.insert(ymnf::make_primitive_name().id());
    r.insert(ymnf::make_exception_name().id());
    r.insert(ymnf::make_object_name().id());
    r.insert(ymnf::make_builtin_name().id());
    r.insert(ymnf::make_visitor_name().id());
    r.insert(fabric::meta_name_factory::make_assistant_name().id());

    return r;
}


bool project_items_expander::is_project_item(const std::string& mn) const {
    static const auto mnfpi(meta_names_for_project_items());
    const auto i(mnfpi.find(mn));
    return i != mnfpi.end();
}

void project_items_expander::expand(model& fm) const {
    std::set<std::string> set;
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& e(*formattable.element());

        const auto mt(e.meta_name().id());
        if (!is_project_item(mt))
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

}
