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
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml_to_cpp/test_data/relationships_td.hpp"

namespace {

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

std::unordered_set<dogen::sml::qname> create_std_unordered_set_dogen_sml_qname(unsigned int position) {
    std::unordered_set<dogen::sml::qname> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_sml_qname(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

boost::optional<dogen::sml::qname>
create_boost_optional_dogen_sml_qname(unsigned int position) {
    boost::optional<dogen::sml::qname> r(
        create_dogen_sml_qname(position));
    return r;
}

}

namespace dogen {
namespace sml_to_cpp {

relationships_generator::relationships_generator() : position_(0) { }

void relationships_generator::
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
    v.visitor(create_boost_optional_dogen_sml_qname(position + 10));
}

relationships_generator::result_type
relationships_generator::create(const unsigned int position) {
    relationships r;
    relationships_generator::populate(position, r);
    return r;
}

relationships_generator::result_type*
relationships_generator::create_ptr(const unsigned int position) {
    relationships* p = new relationships();
    relationships_generator::populate(position, *p);
    return p;
}

relationships_generator::result_type
relationships_generator::operator()() {
    return create(position_++);
}

} }
