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
#include "dogen/om_formatters/test_data/formatted_file_td.hpp"
#include "dogen/om_formatters/test_data/result_td.hpp"

namespace {

dogen::om_formatters::formatted_file
create_dogen_om_formatters_formatted_file(const unsigned int position) {
    return dogen::om_formatters::formatted_file_generator::create(position);
}

std::list<dogen::om_formatters::formatted_file> create_std_list_dogen_om_formatters_formatted_file(unsigned int position) {
    std::list<dogen::om_formatters::formatted_file> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_om_formatters_formatted_file(position + i));
    }
    return r;
}

}

namespace dogen {
namespace om_formatters {

result_generator::result_generator() : position_(0) { }

void result_generator::
populate(const unsigned int position, result_type& v) {
    v.files(create_std_list_dogen_om_formatters_formatted_file(position + 0));
}

result_generator::result_type
result_generator::create(const unsigned int position) {
    result r;
    result_generator::populate(position, r);
    return r;
}
result_generator::result_type*
result_generator::create_ptr(const unsigned int position) {
    result* p = new result();
    result_generator::populate(position, *p);
    return p;
}

result_generator::result_type
result_generator::operator()() {
    return create(position_++);
}

} }
