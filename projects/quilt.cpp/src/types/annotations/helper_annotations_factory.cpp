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
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/quilt.cpp/types/annotations/helper_annotations_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

helper_annotations_factory::
helper_annotations_factory(const dynamic::repository& drp)
    : field_definitions_(make_field_definitions(drp)) { }

helper_annotations_factory::field_definitions helper_annotations_factory::
make_field_definitions(const dynamic::repository& drp) {
    field_definitions r;
    const dynamic::repository_selector s(drp);

    const auto hf(traits::cpp::helper::family());
    r.family = s.select_field_by_name(hf);
    return r;
}

helper_annotations
helper_annotations_factory::make(const dynamic::object& o) const {
    helper_annotations r;
    const dynamic::field_selector fs(o);
    r.family(fs.get_text_content_or_default(field_definitions_.family));
    return r;
}

} } } }
