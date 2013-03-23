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
#include "dogen/cpp/test_data/dependency_details_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"

namespace {

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

std::unordered_set<dogen::sml::qname> create_std_unordered_set_dogen_sml_qname(unsigned int position) {
    std::unordered_set<dogen::sml::qname> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(create_dogen_sml_qname(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {

dependency_details_generator::dependency_details_generator() : position_(0) { }

void dependency_details_generator::
populate(const unsigned int position, result_type& v) {
    v.names(create_std_unordered_set_dogen_sml_qname(position + 0));
    v.forward_decls(create_std_unordered_set_dogen_sml_qname(position + 1));
    v.keys(create_std_unordered_set_dogen_sml_qname(position + 2));
    v.leaves(create_std_unordered_set_dogen_sml_qname(position + 3));
    v.has_std_string(create_bool(position + 4));
    v.has_variant(create_bool(position + 5));
    v.is_parent(create_bool(position + 6));
    v.is_child(create_bool(position + 7));
    v.requires_stream_manipulators(create_bool(position + 8));
    v.has_std_pair(create_bool(position + 9));
}

dependency_details_generator::result_type
dependency_details_generator::create(const unsigned int position) {
    dependency_details r;
    dependency_details_generator::populate(position, r);
    return r;
}
dependency_details_generator::result_type*
dependency_details_generator::create_ptr(const unsigned int position) {
    dependency_details* p = new dependency_details();
    dependency_details_generator::populate(position, *p);
    return p;
}

dependency_details_generator::result_type
dependency_details_generator::operator()() {
    return create(position_++);
}

} }
