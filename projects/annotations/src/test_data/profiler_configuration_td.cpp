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
#include "dogen/annotations/test_data/profile_td.hpp"
#include "dogen/annotations/test_data/annotation_td.hpp"
#include "dogen/annotations/test_data/profiler_configuration_td.hpp"

namespace {

dogen::annotations::profile
create_dogen_annotations_profile(const unsigned int position) {
    return dogen::annotations::profile_generator::create(position);
}

dogen::annotations::annotation
create_dogen_annotations_annotation(const unsigned int position) {
    return dogen::annotations::annotation_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace annotations {

profiler_configuration_generator::profiler_configuration_generator() : position_(0) { }

void profiler_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.profile(create_dogen_annotations_profile(position + 0));
    v.annotation(create_dogen_annotations_annotation(position + 1));
    v.merged(create_bool(position + 2));
}

profiler_configuration_generator::result_type
profiler_configuration_generator::create(const unsigned int position) {
    profiler_configuration r;
    profiler_configuration_generator::populate(position, r);
    return r;
}

profiler_configuration_generator::result_type*
profiler_configuration_generator::create_ptr(const unsigned int position) {
    profiler_configuration* p = new profiler_configuration();
    profiler_configuration_generator::populate(position, *p);
    return p;
}

profiler_configuration_generator::result_type
profiler_configuration_generator::operator()() {
    return create(position_++);
}

} }
