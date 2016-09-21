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
#include "dogen/formatters/test_data/decoration_td.hpp"
#include "dogen/formatters/test_data/file_configuration_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::formatters::decoration
create_dogen_formatters_decoration(const unsigned int position) {
    return dogen::formatters::decoration_generator::create(position);
}

}

namespace dogen {
namespace formatters {

file_configuration_generator::file_configuration_generator() : position_(0) { }

void file_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.generate_preamble(create_bool(position + 0));
    v.decoration(create_dogen_formatters_decoration(position + 1));
}

file_configuration_generator::result_type
file_configuration_generator::create(const unsigned int position) {
    file_configuration r;
    file_configuration_generator::populate(position, r);
    return r;
}

file_configuration_generator::result_type*
file_configuration_generator::create_ptr(const unsigned int position) {
    file_configuration* p = new file_configuration();
    file_configuration_generator::populate(position, *p);
    return p;
}

file_configuration_generator::result_type
file_configuration_generator::operator()() {
    return create(position_++);
}

} }
