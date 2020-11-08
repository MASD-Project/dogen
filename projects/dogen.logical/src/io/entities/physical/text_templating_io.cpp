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
#include <boost/algorithm/string.hpp>
#include "dogen.variability/io/entities/configuration_io.hpp"
#include "dogen.logical/io/entities/physical/relations_io.hpp"
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.logical/io/entities/physical/text_templating_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::identification::entities::logical_name>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::logical::entities::physical {

std::ostream& operator<<(std::ostream& s, const text_templating& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::physical::text_templating\"" << ", "
      << "\"configuration\": " << v.configuration() << ", "
      << "\"stitch_template_content\": " << "\"" << tidy_up_string(v.stitch_template_content()) << "\"" << ", "
      << "\"wale_template\": " << v.wale_template() << ", "
      << "\"wale_template_content\": " << "\"" << tidy_up_string(v.wale_template_content()) << "\"" << ", "
      << "\"rendered_stitch_template\": " << "\"" << tidy_up_string(v.rendered_stitch_template()) << "\"" << ", "
      << "\"relations\": " << v.relations()
      << " }";
    return(s);
}

}
