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
#include "dogen/quilt.cpp/test_data/formattables/formatting_styles_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/formatting_configuration_td.hpp"

namespace {

dogen::quilt::cpp::formattables::formatting_styles
create_dogen_quilt_cpp_formattables_formatting_styles(const unsigned int position) {
    return dogen::quilt::cpp::formattables::formatting_styles_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

formatting_configuration_generator::formatting_configuration_generator() : position_(0) { }

void formatting_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.style(create_dogen_quilt_cpp_formattables_formatting_styles(position + 0));
    v.input(create_std_string(position + 1));
}

formatting_configuration_generator::result_type
formatting_configuration_generator::create(const unsigned int position) {
    formatting_configuration r;
    formatting_configuration_generator::populate(position, r);
    return r;
}

formatting_configuration_generator::result_type*
formatting_configuration_generator::create_ptr(const unsigned int position) {
    formatting_configuration* p = new formatting_configuration();
    formatting_configuration_generator::populate(position, *p);
    return p;
}

formatting_configuration_generator::result_type
formatting_configuration_generator::operator()() {
    return create(position_++);
}

} } } }
