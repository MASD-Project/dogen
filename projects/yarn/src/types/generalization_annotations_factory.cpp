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
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/generalization_annotations_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.generalization_annotations_factory"));

}

namespace dogen {
namespace yarn {

generalization_annotations_factory::
generalization_annotations_factory(const dynamic::repository& rp)
    : field_definitions_(make_field_definitions(rp)) {}

generalization_annotations_factory::field_definitions
generalization_annotations_factory::make_field_definitions(
    const dynamic::repository& rp) const {

    field_definitions r;
    const dynamic::repository_selector rs(rp);
    r.is_final = rs.select_field_by_name(traits::generalization::is_final());
    r.parent = rs.select_field_by_name(traits::generalization::parent());
    return r;
}

generalization_annotations
generalization_annotations_factory::make(const dynamic::object& o) const {
    generalization_annotations r;

    const dynamic::field_selector fs(o);
    const auto& fd(field_definitions_);

    if (fs.has_field(fd.is_final))
        r.is_final(fs.get_boolean_content(fd.is_final));

    if (fs.has_field(fd.parent))
        r.parent(fs.get_text_content(fd.parent));

    return r;
}

} }
