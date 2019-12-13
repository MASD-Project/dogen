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
#include <boost/date_time/posix_time/posix_time.hpp>
#include "dogen.relational/io/tracing/json_io.hpp"
#include "dogen.relational/io/tracing/run_id_io.hpp"
#include "dogen.relational/io/tracing/event_type_io.hpp"
#include "dogen.relational/io/tracing/transform_id_io.hpp"
#include "dogen.relational/io/tracing/transform_type_io.hpp"
#include "dogen.relational/io/tracing/transform_event_io.hpp"
#include "dogen.relational/io/tracing/transform_instance_id_io.hpp"

namespace dogen::relational::tracing {

std::ostream& operator<<(std::ostream& s, const transform_event& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::relational::tracing::transform_event\"" << ", "
      << "\"timestamp\": " << "\"" << v.timestamp() << "\"" << ", "
      << "\"id\": " << v.id() << ", "
      << "\"instance_id\": " << v.instance_id() << ", "
      << "\"run_id\": " << v.run_id() << ", "
      << "\"transform_type\": " << v.transform_type() << ", "
      << "\"event_type\": " << v.event_type() << ", "
      << "\"payload\": " << v.payload()
      << " }";
    return(s);
}

}
