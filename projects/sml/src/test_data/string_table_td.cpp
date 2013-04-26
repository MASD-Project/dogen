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
#include "dogen/sml/test_data/entry_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/string_table_td.hpp"

namespace {

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::sml::entry
create_dogen_sml_entry(const unsigned int position) {
    return dogen::sml::entry_generator::create(position);
}

std::list<dogen::sml::entry> create_std_list_dogen_sml_entry(unsigned int position) {
    std::list<dogen::sml::entry> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_sml_entry(position + i));
    }
    return r;
}

}

namespace dogen {
namespace sml {

string_table_generator::string_table_generator() : position_(0) { }

void string_table_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_sml_qname(position + 0));
    v.documentation(create_std_string(position + 1));
    v.entries(create_std_list_dogen_sml_entry(position + 2));
}

string_table_generator::result_type
string_table_generator::create(const unsigned int position) {
    string_table r;
    string_table_generator::populate(position, r);
    return r;
}
string_table_generator::result_type*
string_table_generator::create_ptr(const unsigned int position) {
    string_table* p = new string_table();
    string_table_generator::populate(position, *p);
    return p;
}

string_table_generator::result_type
string_table_generator::operator()() {
    return create(position_++);
}

} }
