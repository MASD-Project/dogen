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
#include "dogen/yarn/test_data/element_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/formattable_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/element_configuration_td.hpp"

namespace {

dogen::yarn::element*
create_dogen_yarn_element_ptr(const unsigned int position) {
    return dogen::yarn::element_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::element>
create_boost_shared_ptr_dogen_yarn_element(unsigned int position) {
    boost::shared_ptr<dogen::yarn::element> r(
        create_dogen_yarn_element_ptr(position));
    return r;
}

dogen::quilt::cpp::formattables::element_configuration
create_dogen_quilt_cpp_formattables_element_configuration(const unsigned int position) {
    return dogen::quilt::cpp::formattables::element_configuration_generator::create(position);
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

formattable_generator::formattable_generator() : position_(0) { }

void formattable_generator::
populate(const unsigned int position, result_type& v) {
    v.element(create_boost_shared_ptr_dogen_yarn_element(position + 0));
    v.configuration(create_dogen_quilt_cpp_formattables_element_configuration(position + 1));
}

formattable_generator::result_type
formattable_generator::create(const unsigned int position) {
    formattable r;
    formattable_generator::populate(position, r);
    return r;
}

formattable_generator::result_type*
formattable_generator::create_ptr(const unsigned int position) {
    formattable* p = new formattable();
    formattable_generator::populate(position, *p);
    return p;
}

formattable_generator::result_type
formattable_generator::operator()() {
    return create(position_++);
}

} } } }
