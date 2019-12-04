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
#include "dogen.tracing/io/backend_io.hpp"
#include "dogen.tracing/types/null_tracer.hpp"

namespace dogen::tracing {

// void null_tracer::to_stream(std::ostream& s) const {
//     s << " { "
//       << "\"__type__\": " << "\"dogen::tracing::null_tracer\"" << ", "
//       << "\"__parent_0__\": ";
//     dogen::tracing::backend::to_stream(s);
//     s << " }";
// }

// bool null_tracer::equals(const dogen::tracing::backend& other) const {
//     const null_tracer* const p(dynamic_cast<const null_tracer* const>(&other));
//     if (!p) return false;
//     return *this == *p;
// }

bool null_tracer::operator==(const null_tracer& /*rhs*/) const {
    return true;
}

}
