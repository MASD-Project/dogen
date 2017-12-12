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
#include "dogen.yarn/test_data/meta_model/denormalised_archetype_properties_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::optional<bool>
create_boost_optional_bool(unsigned int position) {
    boost::optional<bool> r(
        create_bool(position));
    return r;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

denormalised_archetype_properties_generator::denormalised_archetype_properties_generator() : position_(0) { }

void denormalised_archetype_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.backend_enabled(create_bool(position + 0));
    v.backend_directory(create_std_string(position + 1));
    v.facet_enabled(create_bool(position + 2));
    v.facet_overwrite(create_bool(position + 3));
    v.facet_directory(create_std_string(position + 4));
    v.facet_postfix(create_std_string(position + 5));
    v.archetype_enabled(create_bool(position + 6));
    v.archetype_overwrite(create_boost_optional_bool(position + 7));
    v.archetype_postfix(create_std_string(position + 8));
}

denormalised_archetype_properties_generator::result_type
denormalised_archetype_properties_generator::create(const unsigned int position) {
    denormalised_archetype_properties r;
    denormalised_archetype_properties_generator::populate(position, r);
    return r;
}

denormalised_archetype_properties_generator::result_type*
denormalised_archetype_properties_generator::create_ptr(const unsigned int position) {
    denormalised_archetype_properties* p = new denormalised_archetype_properties();
    denormalised_archetype_properties_generator::populate(position, *p);
    return p;
}

denormalised_archetype_properties_generator::result_type
denormalised_archetype_properties_generator::operator()() {
    return create(position_++);
}

} } }
