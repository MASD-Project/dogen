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
#include "dogen.assets/test_data/meta_model/element_td.hpp"
#include "dogen.generation.csharp/test_data/fabric/visual_studio_project_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen::generation::csharp::fabric {

visual_studio_project_generator::visual_studio_project_generator() : position_(0) { }

void visual_studio_project_generator::
populate(const unsigned int position, result_type& v) {
    dogen::assets::meta_model::element_generator::populate(position, v);
    v.project_guid(create_std_string(position + 0));
    v.project_name(create_std_string(position + 1));
    v.tools_version(create_std_string(position + 2));
}

visual_studio_project_generator::result_type
visual_studio_project_generator::create(const unsigned int position) {
    visual_studio_project r;
    visual_studio_project_generator::populate(position, r);
    return r;
}

visual_studio_project_generator::result_type*
visual_studio_project_generator::create_ptr(const unsigned int position) {
    visual_studio_project* p = new visual_studio_project();
    visual_studio_project_generator::populate(position, *p);
    return p;
}

visual_studio_project_generator::result_type
visual_studio_project_generator::operator()() {
    return create(position_++);
}

}
