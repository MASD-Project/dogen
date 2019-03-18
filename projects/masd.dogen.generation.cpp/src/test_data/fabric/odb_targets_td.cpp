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
#include "masd.dogen.generation.cpp/test_data/fabric/odb_target_td.hpp"
#include "masd.dogen.generation.cpp/test_data/fabric/odb_targets_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::generation::cpp::fabric::odb_target
create_masd_dogen_generation_cpp_fabric_odb_target(const unsigned int position) {
    return masd::dogen::generation::cpp::fabric::odb_target_generator::create(position);
}

std::list<masd::dogen::generation::cpp::fabric::odb_target> create_std_list_masd_dogen_generation_cpp_fabric_odb_target(unsigned int position) {
    std::list<masd::dogen::generation::cpp::fabric::odb_target> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_generation_cpp_fabric_odb_target(position + i));
    }
    return r;
}

}

namespace masd::dogen::generation::cpp::fabric {

odb_targets_generator::odb_targets_generator() : position_(0) { }

void odb_targets_generator::
populate(const unsigned int position, result_type& v) {
    v.main_target_name(create_std_string(position + 0));
    v.common_odb_options(create_std_string(position + 1));
    v.targets(create_std_list_masd_dogen_generation_cpp_fabric_odb_target(position + 2));
}

odb_targets_generator::result_type
odb_targets_generator::create(const unsigned int position) {
    odb_targets r;
    odb_targets_generator::populate(position, r);
    return r;
}

odb_targets_generator::result_type*
odb_targets_generator::create_ptr(const unsigned int position) {
    odb_targets* p = new odb_targets();
    odb_targets_generator::populate(position, *p);
    return p;
}

odb_targets_generator::result_type
odb_targets_generator::operator()() {
    return create(position_++);
}

}
