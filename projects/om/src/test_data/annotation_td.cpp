/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/om/test_data/annotation_td.hpp"
#include "dogen/om/test_data/licence_td.hpp"
#include "dogen/om/test_data/modeline_td.hpp"

namespace {

dogen::om::modeline
create_dogen_om_modeline(const unsigned int position) {
    return dogen::om::modeline_generator::create(position);
}

dogen::om::licence
create_dogen_om_licence(const unsigned int position) {
    return dogen::om::licence_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace om {

annotation_generator::annotation_generator() : position_(0) { }

void annotation_generator::
populate(const unsigned int position, result_type& v) {
    v.modeline(create_dogen_om_modeline(position + 0));
    v.licence(create_dogen_om_licence(position + 1));
    v.code_generation_marker(create_std_string(position + 2));
}

annotation_generator::result_type
annotation_generator::create(const unsigned int position) {
    annotation r;
    annotation_generator::populate(position, r);
    return r;
}
annotation_generator::result_type*
annotation_generator::create_ptr(const unsigned int position) {
    annotation* p = new annotation();
    annotation_generator::populate(position, *p);
    return p;
}

annotation_generator::result_type
annotation_generator::operator()() {
    return create(position_++);
}

} }
