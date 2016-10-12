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
#include "dogen/annotations/io/name_io.hpp"
#include "dogen/annotations/io/value_io.hpp"
#include "dogen/annotations/io/scope_types_io.hpp"
#include "dogen/annotations/io/value_types_io.hpp"
#include "dogen/annotations/io/type_template_io.hpp"
#include "dogen/annotations/io/template_kinds_io.hpp"
#include "dogen/annotations/io/ownership_hierarchy_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::annotations::value>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s << " }";
    return s;
}

}

namespace dogen {
namespace annotations {

std::ostream& operator<<(std::ostream& s, const type_template& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::annotations::type_template\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"value_type\": " << v.value_type() << ", "
      << "\"scope\": " << v.scope() << ", "
      << "\"ownership_hierarchy\": " << v.ownership_hierarchy() << ", "
      << "\"default_value\": " << v.default_value() << ", "
      << "\"kind\": " << v.kind()
      << " }";
    return(s);
}

} }
