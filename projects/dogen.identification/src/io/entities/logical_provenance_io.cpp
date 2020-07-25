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
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.identification/io/entities/logical_meta_name_io.hpp"
#include "dogen.identification/io/entities/logical_provenance_io.hpp"
#include "dogen.identification/io/entities/injection_provenance_io.hpp"

namespace dogen::identification::entities {

std::ostream& operator<<(std::ostream& s, const logical_provenance& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::identification::entities::logical_provenance\"" << ", "
      << "\"injection\": " << v.injection() << ", "
      << "\"logical_name\": " << v.logical_name() << ", "
      << "\"logical_meta_name\": " << v.logical_meta_name()
      << " }";
    return(s);
}

}
