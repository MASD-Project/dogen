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
#include "dogen.variability/io/entities/profile_io.hpp"
#include "dogen.variability/io/entities/profile_template_io.hpp"
#include "dogen.variability/io/transforms/profile_repository_inputs_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::variability::entities::profile>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::variability::entities::profile_template>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::variability::transforms {

std::ostream& operator<<(std::ostream& s, const profile_repository_inputs& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::variability::transforms::profile_repository_inputs\"" << ", "
      << "\"profiles\": " << v.profiles() << ", "
      << "\"templates\": " << v.templates()
      << " }";
    return(s);
}

}
