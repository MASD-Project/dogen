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
#include "masd.dogen.variability/io/meta_model/profile_template_io.hpp"
#include "masd.dogen.variability/io/meta_model/profile_template_repository_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<masd::dogen::variability::meta_model::profile_template>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace masd::dogen::variability::meta_model {

std::ostream& operator<<(std::ostream& s, const profile_template_repository& v) {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::variability::meta_model::profile_template_repository\"" << ", "
      << "\"templates\": " << v.templates()
      << " }";
    return(s);
}

}
