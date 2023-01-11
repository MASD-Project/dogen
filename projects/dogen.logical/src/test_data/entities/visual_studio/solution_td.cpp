/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.logical/test_data/entities/element_td.hpp"
#include "dogen.logical/test_data/entities/visual_studio/solution_td.hpp"
#include "dogen.logical/test_data/entities/visual_studio/project_persistence_block_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::logical::entities::visual_studio::project_persistence_block
create_dogen_logical_entities_visual_studio_project_persistence_block(const unsigned int position) {
    return dogen::logical::entities::visual_studio::project_persistence_block_generator::create(position);
}

std::list<dogen::logical::entities::visual_studio::project_persistence_block> create_std_list_dogen_logical_entities_visual_studio_project_persistence_block(unsigned int position) {
    std::list<dogen::logical::entities::visual_studio::project_persistence_block> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_logical_entities_visual_studio_project_persistence_block(position + i));
    }
    return r;
}

}

namespace dogen::logical::entities::visual_studio {

solution_generator::solution_generator() : position_(0) { }

void solution_generator::
populate(const unsigned int position, result_type& v) {
    dogen::logical::entities::element_generator::populate(position, v);
    v.guid(create_std_string(position + 0));
    v.project_persistence_blocks(create_std_list_dogen_logical_entities_visual_studio_project_persistence_block(position + 1));
}

solution_generator::result_type
solution_generator::create(const unsigned int position) {
    solution r;
    solution_generator::populate(position, r);
    return r;
}

solution_generator::result_type*
solution_generator::create_ptr(const unsigned int position) {
    solution* p = new solution();
    solution_generator::populate(position, *p);
    return p;
}

solution_generator::result_type
solution_generator::operator()() {
    return create(position_++);
}

}