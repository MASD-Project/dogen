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
#include "masd.dogen/test_data/weaving_style_td.hpp"
#include "masd.dogen.cli/test_data/weaving_configuration_td.hpp"

namespace {

masd::dogen::weaving_style
create_masd_dogen_weaving_style(const unsigned int position) {
    return masd::dogen::weaving_style_generator::create(position);
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace masd::dogen::cli {

weaving_configuration_generator::weaving_configuration_generator() : position_(0) { }

void weaving_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.style(create_masd_dogen_weaving_style(position + 0));
    v.target(create_boost_filesystem_path(position + 1));
}

weaving_configuration_generator::result_type
weaving_configuration_generator::create(const unsigned int position) {
    weaving_configuration r;
    weaving_configuration_generator::populate(position, r);
    return r;
}

weaving_configuration_generator::result_type*
weaving_configuration_generator::create_ptr(const unsigned int position) {
    weaving_configuration* p = new weaving_configuration();
    weaving_configuration_generator::populate(position, *p);
    return p;
}

weaving_configuration_generator::result_type
weaving_configuration_generator::operator()() {
    return create(position_++);
}

}
