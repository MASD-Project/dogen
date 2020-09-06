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
#include <boost/pointer_cast.hpp>
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/visual_studio/project_persistence_block.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.logical/types/entities/structural/assistant.hpp"
#include "dogen.text.csharp/types/formattables/project_items_expander.hpp"

namespace {

const std::string msbuild_target("Compile");

}

namespace dogen::text::csharp::formattables {

std::unordered_set<identification::entities::logical_meta_id>
project_items_expander::meta_names_for_project_items() {
    std::unordered_set<identification::entities::logical_meta_id> r;

    using ymnf = identification::helpers::logical_meta_name_factory;
    r.insert(ymnf::make_enumeration_name().id());
    r.insert(ymnf::make_primitive_name().id());
    r.insert(ymnf::make_exception_name().id());
    r.insert(ymnf::make_object_name().id());
    r.insert(ymnf::make_builtin_name().id());
    r.insert(ymnf::make_visitor_name().id());
    r.insert(ymnf::make_assistant_name().id());

    return r;
}


bool project_items_expander::
is_project_item(const identification::entities::logical_meta_id& mn) const {
    static const auto mnfpi(meta_names_for_project_items());
    const auto i(mnfpi.find(mn));
    return i != mnfpi.end();
}

void project_items_expander::expand(model& fm) const {
    using logical::entities::visual_studio::project;
    boost::shared_ptr<project> proj;
    using ymnf = identification::helpers::logical_meta_name_factory;
    const auto proj_name(ymnf::make_visual_studio_project_name());
    const auto proj_qn(proj_name.id());

    std::set<std::string> set;
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& e(*formattable.element());

        const auto mt(e.meta_name().id());
        if (mt == proj_qn) {
            proj = boost::dynamic_pointer_cast<project>(formattable.element());
            continue;
        } else if (!is_project_item(mt))
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

    for (const auto& pi : set)
        fm.project_items().push_back(pi);

    if (proj) {
        logical::entities::visual_studio::item_group ig;
        for (const auto& pi : set) {
            logical::entities::visual_studio::item item;
            item.include(pi);
            item.name(msbuild_target);
            ig.items().push_back(item);
        }
        proj->item_groups().push_back(ig);
    }
}

}
