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
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

helper_settings_factory::helper_settings_factory(const dynamic::repository& rp)
    : field_definitions_(make_field_definitions(rp)) { }

helper_settings_factory::field_definitions
helper_settings_factory::make_field_definitions(const dynamic::repository& rp) {
    field_definitions r;

    const dynamic::repository_selector s(rp);
    const auto hf(traits::cpp::helper::family());
    r.family = s.select_field_by_name(hf);

    const auto rq(traits::cpp::helper::requires_quoting());
    r.requires_quoting = s.select_field_by_name(rq);

    const auto ruc(traits::cpp::helper::remove_unprintable_characters());
    r.remove_unprintable_characters = s.select_field_by_name(ruc);

    const auto rd(traits::cpp::helper::requires_dereferencing());
    r.requires_dereferencing = s.select_field_by_name(rd);

    return r;
}

void helper_settings_factory::
throw_if_dependent_fields_are_present(const dynamic::field_selector& fs) const {
    const auto& fd(field_definitions_);
    const bool dependent_fields_present(
        fs.has_field(fd.requires_quoting) ||
        fs.has_field(fd.remove_unprintable_characters) ||
        fs.has_field(fd.requires_dereferencing));

    if (dependent_fields_present) {
        // FIXME: throw
    }
}

boost::optional<helper_settings> helper_settings_factory::make(const dynamic::object& o) const {
    helper_settings r;
    const auto& fd(field_definitions_);
    const dynamic::field_selector fs(o);
    const bool has_family_field(fs.has_field(fd.family));

    if (!has_family_field) {
        throw_if_dependent_fields_are_present(fs);
        return boost::optional<helper_settings>();
    }

    r.family(fs.get_text_content(fd.family));
    r.requires_quoting(fs.get_boolean_content_or_default(fd.requires_quoting));

    const auto rup(fd.remove_unprintable_characters);
    r.remove_unprintable_characters(fs.get_boolean_content_or_default(rup));

    const auto rd(fs.get_boolean_content_or_default(fd.requires_dereferencing));
    r.requires_dereferencing(rd);

    return r;
}

} } } }
