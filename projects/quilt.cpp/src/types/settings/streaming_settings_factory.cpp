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
#include "dogen/quilt.cpp/types/settings/streaming_settings_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

streaming_settings_factory::
streaming_settings_factory(const dynamic::repository& rp)
    : field_definitions_(make_field_definitions(rp)) { }

streaming_settings_factory::field_definitions
streaming_settings_factory::
make_field_definitions(const dynamic::repository& rp) {
    field_definitions r;

    const dynamic::repository_selector s(rp);
    const auto scm(traits::cpp::streaming::string_conversion_method());
    r.string_conversion_method = s.select_field_by_name(scm);

    const auto rq(traits::cpp::streaming::requires_quoting());
    r.requires_quoting = s.select_field_by_name(rq);

    const auto ruc(traits::cpp::streaming::remove_unprintable_characters());
    r.remove_unprintable_characters = s.select_field_by_name(ruc);

    const auto rd(traits::cpp::streaming::requires_dereferencing());
    r.requires_dereferencing = s.select_field_by_name(rd);

    return r;
}

boost::optional<streaming_settings>
streaming_settings_factory::make(const dynamic::object& o) const {
    streaming_settings r;
    const auto& fd(field_definitions_);
    const dynamic::field_selector fs(o);
    bool has_settings(false);

    const auto& rq(fd.requires_quoting);
    if (fs.has_field(rq)) {
        has_settings = true;
        r.requires_quoting(fs.get_boolean_content_or_default(rq));
    }

    const auto& rd(fd.requires_dereferencing);
    if (fs.has_field(rd)) {
        has_settings = true;
        r.requires_dereferencing(fs.get_boolean_content_or_default(rd));
    }

    const auto& scm(fd.string_conversion_method);
    if (fs.has_field(scm)) {
        has_settings = true;
        r.string_conversion_method(fs.get_text_content_or_default(scm));
    }

    const auto& ruc(fd.remove_unprintable_characters);
    if (fs.has_field(ruc)) {
        has_settings = true;
        r.remove_unprintable_characters(fs.get_boolean_content_or_default(ruc));
    }

    if (!has_settings)
        return boost::optional<streaming_settings>();

    return r;
}

} } } }
