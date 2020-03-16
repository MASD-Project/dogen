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
#include <ostream>
#include "dogen.generation/io/entities/path_contribution_types_io.hpp"
#include "dogen.generation/io/entities/intra_backend_segment_properties_io.hpp"

namespace dogen::generation::entities {

std::ostream& operator<<(std::ostream& s, const intra_backend_segment_properties& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::generation::entities::intra_backend_segment_properties\"" << ", "
      << "\"override_parent_path\": " << "\"" << v.override_parent_path().generic_string() << "\"" << ", "
      << "\"path_segment\": " << "\"" << v.path_segment().generic_string() << "\"" << ", "
      << "\"external_modules\": " << v.external_modules() << ", "
      << "\"model_modules\": " << v.model_modules() << ", "
      << "\"internal_modules\": " << v.internal_modules() << ", "
      << "\"facet\": " << v.facet()
      << " }";
    return(s);
}

}
