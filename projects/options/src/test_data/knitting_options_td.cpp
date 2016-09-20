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
#include "dogen/options/test_data/cpp_options_td.hpp"
#include "dogen/options/test_data/input_options_td.hpp"
#include "dogen/options/test_data/output_options_td.hpp"
#include "dogen/options/test_data/knitting_options_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::options::input_options
create_dogen_options_input_options(const unsigned int position) {
    return dogen::options::input_options_generator::create(position);
}

dogen::options::output_options
create_dogen_options_output_options(const unsigned int position) {
    return dogen::options::output_options_generator::create(position);
}

dogen::options::cpp_options
create_dogen_options_cpp_options(const unsigned int position) {
    return dogen::options::cpp_options_generator::create(position);
}

}

namespace dogen {
namespace options {

knitting_options_generator::knitting_options_generator() : position_(0) { }

void knitting_options_generator::
populate(const unsigned int position, result_type& v) {
    v.verbose(create_bool(position + 0));
    v.input(create_dogen_options_input_options(position + 1));
    v.output(create_dogen_options_output_options(position + 2));
    v.cpp(create_dogen_options_cpp_options(position + 3));
}

knitting_options_generator::result_type
knitting_options_generator::create(const unsigned int position) {
    knitting_options r;
    knitting_options_generator::populate(position, r);
    return r;
}

knitting_options_generator::result_type*
knitting_options_generator::create_ptr(const unsigned int position) {
    knitting_options* p = new knitting_options();
    knitting_options_generator::populate(position, *p);
    return p;
}

knitting_options_generator::result_type
knitting_options_generator::operator()() {
    return create(position_++);
}

} }
