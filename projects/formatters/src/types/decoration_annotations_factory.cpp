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
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/formatters/types/traits.hpp"
#include "dogen/formatters/types/building_error.hpp"
#include "dogen/formatters/types/decoration_annotations_factory.hpp"

namespace dogen {
namespace formatters {

decoration_annotations_factory::
decoration_annotations_factory(const dynamic::repository& rp)
    : field_definitions_(make_field_definitions(rp)) { }

decoration_annotations_factory::field_definitions
decoration_annotations_factory::
make_field_definitions(const dynamic::repository& rp) const {
    const dynamic::repository_selector s(rp);

    field_definitions r;
    const auto gd(traits::decoration::generate_decoration());
    r.generate_decoration = s.select_field_by_name(gd);

    const auto cn(traits::decoration::copyright_notices());
    r.copyright_notice = s.select_field_by_name(cn);

    const auto ln(traits::decoration::licence_name());
    r.licence_name = s.select_field_by_name(ln);

    const auto& mlgn(traits::decoration::modeline_group_name());
    r. modeline_group_name = s.select_field_by_name(mlgn);

    using cgm = traits::decoration::code_generation_marker;
    r. marker_add_date_time = s.select_field_by_name(cgm::add_date_time());
    r. marker_add_warning = s.select_field_by_name(cgm::add_warning());
    r. marker_message = s.select_field_by_name(cgm::message());

    return r;
}

decoration_annotations
decoration_annotations_factory::make(const dynamic::object& o) const {
    const dynamic::field_selector fs(o);

    decoration_annotations r;
    const auto& gd(field_definitions_.generate_decoration);
    if (fs.has_field(gd))
        r.generate_decoration(fs.get_boolean_content(gd));

    const auto& cn(field_definitions_.copyright_notice);
    if (fs.has_field(cn))
        r.copyright_notices(fs.get_text_collection_content(cn));

    const auto& ln(field_definitions_.licence_name);
    if (fs.has_field(ln))
        r.licence_name(fs.get_text_content(ln));

    const auto& mlgn(field_definitions_.modeline_group_name);
    if (fs.has_field(mlgn))
        r.modeline_group_name(fs.get_text_content(mlgn));

    const auto madt(field_definitions_.marker_add_date_time);
    if (fs.has_field(madt))
        r.marker_add_date_time(fs.get_boolean_content(madt));

    const auto maw(field_definitions_.marker_add_warning);
    if (fs.has_field(maw))
        r.marker_add_date_time(fs.get_boolean_content(maw));

    const auto msg(field_definitions_.marker_message);
    if (fs.has_field(msg))
        r.marker_message(fs.get_text_content(msg));

    return r;
}

} }
