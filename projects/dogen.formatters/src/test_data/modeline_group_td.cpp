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
#include "dogen.formatters/test_data/modeline_td.hpp"
#include "dogen.formatters/test_data/modeline_group_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::formatters::modeline
create_dogen_formatters_modeline(const unsigned int position) {
    return dogen::formatters::modeline_generator::create(position);
}

std::unordered_map<std::string, dogen::formatters::modeline> create_std_unordered_map_std_string_dogen_formatters_modeline(unsigned int position) {
    std::unordered_map<std::string, dogen::formatters::modeline> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_formatters_modeline(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace formatters {

modeline_group_generator::modeline_group_generator() : position_(0) { }

void modeline_group_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.modelines(create_std_unordered_map_std_string_dogen_formatters_modeline(position + 1));
}

modeline_group_generator::result_type
modeline_group_generator::create(const unsigned int position) {
    modeline_group r;
    modeline_group_generator::populate(position, r);
    return r;
}

modeline_group_generator::result_type*
modeline_group_generator::create_ptr(const unsigned int position) {
    modeline_group* p = new modeline_group();
    modeline_group_generator::populate(position, *p);
    return p;
}

modeline_group_generator::result_type
modeline_group_generator::operator()() {
    return create(position_++);
}

} }
