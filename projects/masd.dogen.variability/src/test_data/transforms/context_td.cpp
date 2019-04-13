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
#include <sstream>
#include "masd.dogen.archetypes/test_data/location_repository_td.hpp"
#include "masd.dogen.variability/test_data/transforms/context_td.hpp"

namespace {

masd::dogen::archetypes::location_repository
create_masd_dogen_archetypes_location_repository(const unsigned int position) {
    return masd::dogen::archetypes::location_repository_generator::create(position);
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

std::vector<boost::filesystem::path> create_std_vector_boost_filesystem_path(unsigned int position) {
    std::vector<boost::filesystem::path> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_filesystem_path(position + i));
    }
    return r;
}

}

namespace masd::dogen::variability::transforms {

context_generator::context_generator() : position_(0) { }

void context_generator::
populate(const unsigned int position, result_type& v) {
    v.archetype_location_repository(create_masd_dogen_archetypes_location_repository(position + 0));
    v.data_directories(create_std_vector_boost_filesystem_path(position + 1));
}

context_generator::result_type
context_generator::create(const unsigned int position) {
    context r;
    context_generator::populate(position, r);
    return r;
}

context_generator::result_type*
context_generator::create_ptr(const unsigned int position) {
    context* p = new context();
    context_generator::populate(position, *p);
    return p;
}

context_generator::result_type
context_generator::operator()() {
    return create(position_++);
}

}
