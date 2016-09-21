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
#include "dogen/quilt.cpp/types/annotations/directory_names_annotations_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

directory_names_annotations_factory::
directory_names_annotations_factory(const dynamic::repository& rp)
  : fields_(setup_fields(rp)) { }

directory_names_annotations_factory::fields directory_names_annotations_factory::
setup_fields(const dynamic::repository& rp) const {
    fields r;
    const dynamic::repository_selector s(rp);
    const auto& idn(traits::cpp::include_directory_name());
    r.include_directory_name = s.select_field_by_name(idn);

    const auto& sdn(traits::cpp::source_directory_name());
    r.source_directory_name = s.select_field_by_name(sdn);

    return r;
}

directory_names_annotations
directory_names_annotations_factory::make(const dynamic::object& o) const {
    directory_names_annotations r;
    const dynamic::field_selector fs(o);

    const auto& idn(fields_.include_directory_name);
    r.include_directory_name(fs.get_text_content_or_default(idn));

    const auto& sdn(fields_.source_directory_name);
    r.source_directory_name(fs.get_text_content_or_default(sdn));

    return r;
}

} } } }
