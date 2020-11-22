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
#include "dogen.text/types/transforms/helper_transform.hpp"

namespace dogen::text::transforms {

using identification::entities::physical_meta_id;
using identification::entities::logical_meta_physical_id;

bool helper_transform::is_streaming_enabled(const physical::entities::model& m,
    const logical::entities::element& e,
    const physical::entities::artefact& a,
    const logical::entities::helper_properties& hp) const {

    /*
     * If the IO facet is globally disabled, we don't need streaming.
     */
    const auto& mmp(m.meta_model_properties());
    const auto& eafe(mmp.enabled_archetype_for_element());
    const physical_meta_id pmid("masd.cpp.io.canonical_archetype");
    const logical_meta_physical_id ea(e.name().id(), pmid);
    const auto i(eafe.find(ea));
    bool is_io_enabled(i != eafe.end());
    if (!is_io_enabled)
        return false;

    /*
     * If we are in the IO facet, and we are not in an inheritance
     * relationship we need streaming.
     */
    const auto is_io(a.meta_name().location().facet() == "io");
    if (is_io && !hp.in_inheritance_relationship())
        return true;

    /*
     * If we are in the types class implementation and we are in an
     * inheritance relationship, we'll need streaming.
     */
    bool in_types_class_implementation(a.meta_name().id() ==
        physical_meta_id("masd.cpp.types.class_implementation"));
    return in_types_class_implementation && hp.in_inheritance_relationship();
}

bool helper_transform::operator==(const helper_transform& /*rhs*/) const {
    return true;
}

}
