/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/config/io/cpp_facet_types_io.hpp"
#include "dogen/cpp/io/formattables/file_types_io.hpp"
#include "dogen/cpp/io/formattables/aspect_types_io.hpp"
#include "dogen/cpp/io/formattables/content_types_io.hpp"
#include "dogen/cpp/io/formattables/content_descriptor_io.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

std::ostream& operator<<(std::ostream& s, const content_descriptor& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::content_descriptor\"" << ", "
      << "\"file_type\": " << v.file_type() << ", "
      << "\"facet_type\": " << v.facet_type() << ", "
      << "\"aspect_type\": " << v.aspect_type() << ", "
      << "\"name\": " << v.name() << ", "
      << "\"content_type\": " << v.content_type()
      << " }";
    return(s);
}

} } }
