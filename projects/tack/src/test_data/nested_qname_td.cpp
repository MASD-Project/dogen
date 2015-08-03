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
#include "dogen/tack/test_data/qname_td.hpp"
#include "dogen/tack/test_data/nested_qname_td.hpp"

namespace {

dogen::tack::qname
create_dogen_tack_qname(const unsigned int position) {
    return dogen::tack::qname_generator::create(position);
}

dogen::tack::nested_qname
create_dogen_tack_nested_qname(const unsigned int) {
    return dogen::tack::nested_qname();
}

std::list<dogen::tack::nested_qname> create_std_list_dogen_tack_nested_qname(unsigned int position) {
    std::list<dogen::tack::nested_qname> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_tack_nested_qname(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace tack {

nested_qname_generator::nested_qname_generator() : position_(0) { }

void nested_qname_generator::
populate(const unsigned int position, result_type& v) {
    v.type(create_dogen_tack_qname(position + 0));
    v.children(create_std_list_dogen_tack_nested_qname(position + 1));
    v.is_pointer(create_bool(position + 2));
}

nested_qname_generator::result_type
nested_qname_generator::create(const unsigned int position) {
    nested_qname r;
    nested_qname_generator::populate(position, r);
    return r;
}

nested_qname_generator::result_type*
nested_qname_generator::create_ptr(const unsigned int position) {
    nested_qname* p = new nested_qname();
    nested_qname_generator::populate(position, *p);
    return p;
}

nested_qname_generator::result_type
nested_qname_generator::operator()() {
    return create(position_++);
}

} }
