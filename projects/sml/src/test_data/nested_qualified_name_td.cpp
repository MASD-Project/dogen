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
#include "dogen/sml/test_data/nested_qualified_name_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"

namespace {

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

dogen::sml::nested_qualified_name
create_dogen_sml_nested_qualified_name(const unsigned int) {
    return dogen::sml::nested_qualified_name();
}

std::list<dogen::sml::nested_qualified_name> create_std_list_dogen_sml_nested_qualified_name(unsigned int position) {
    std::list<dogen::sml::nested_qualified_name> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_sml_nested_qualified_name(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace sml {

nested_qualified_name_generator::nested_qualified_name_generator() : position_(0) { }

void nested_qualified_name_generator::
populate(const unsigned int position, result_type& v) {
    v.type(create_dogen_sml_qname(position + 0));
    v.children(create_std_list_dogen_sml_nested_qualified_name(position + 1));
    v.is_pointer(create_bool(position + 2));
}

nested_qualified_name_generator::result_type
nested_qualified_name_generator::create(const unsigned int position) {
    nested_qualified_name r;
    nested_qualified_name_generator::populate(position, r);
    return r;
}
nested_qualified_name_generator::result_type*
nested_qualified_name_generator::create_ptr(const unsigned int position) {
    nested_qualified_name* p = new nested_qualified_name();
    nested_qualified_name_generator::populate(position, *p);
    return p;
}

nested_qualified_name_generator::result_type
nested_qualified_name_generator::operator()() {
    return create(position_++);
}

} }
