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
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/structural/visitor.hpp"
#include "dogen.assets/types/meta_model/structural/builtin.hpp"
#include "dogen.assets/types/meta_model/structural/exception.hpp"
#include "dogen.assets/types/meta_model/structural/enumeration.hpp"
#include "dogen.assets/types/meta_model/structural/primitive.hpp"
#include "dogen.assets/types/meta_model/visual_studio/project_persistence_block.hpp"
#include "dogen.assets/types/meta_model/visual_studio/project.hpp"
#include "dogen.assets/types/meta_model/structural/assistant.hpp"
#include "dogen.generation.csharp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.csharp/types/formattables/project_items_expander.hpp"

namespace {

const std::string msbuild_target("Compile");

}

namespace dogen::generation::csharp::formattables {

std::unordered_set<std::string>
project_items_expander::meta_names_for_project_items() {
    std::unordered_set<std::string> r;

    using ymnf = assets::helpers::meta_name_factory;
    r.insert(ymnf::make_enumeration_name().qualified().dot());
    r.insert(ymnf::make_primitive_name().qualified().dot());
    r.insert(ymnf::make_exception_name().qualified().dot());
    r.insert(ymnf::make_object_name().qualified().dot());
    r.insert(ymnf::make_builtin_name().qualified().dot());
    r.insert(ymnf::make_visitor_name().qualified().dot());
    r.insert(ymnf::make_assistant_name().qualified().dot());

    return r;
}


bool project_items_expander::is_project_item(const std::string& mn) const {
    static const auto mnfpi(meta_names_for_project_items());
    const auto i(mnfpi.find(mn));
    return i != mnfpi.end();
}

void project_items_expander::expand(model& fm) const {
    using assets::meta_model::visual_studio::project;
    boost::shared_ptr<project> proj;
    using ymnf = assets::helpers::meta_name_factory;
    const auto proj_name(ymnf::make_visual_studio_project_name());
    const auto proj_qn(proj_name.qualified().dot());

    std::set<std::string> set;
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& e(*formattable.element());

        const auto mt(e.meta_name().qualified().dot());
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
        assets::meta_model::visual_studio::item_group ig;
        for (const auto& pi : set) {
            assets::meta_model::visual_studio::item item;
            item.include(pi);
            item.name(msbuild_target);
            ig.items().push_back(item);
        }
        proj->item_groups().push_back(ig);
    }
}

}
