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
#include "dogen/cpp/test_data/path_spec_key_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

}

namespace dogen {
namespace cpp {

path_spec_key_generator::path_spec_key_generator() : position_(0) { }

void path_spec_key_generator::
populate(const unsigned int position, result_type& v) {
    v.formatter_id(create_std_string(position + 0));
    v.qname(create_dogen_sml_qname(position + 1));
}

path_spec_key_generator::result_type
path_spec_key_generator::create(const unsigned int position) {
    path_spec_key r;
    path_spec_key_generator::populate(position, r);
    return r;
}
path_spec_key_generator::result_type*
path_spec_key_generator::create_ptr(const unsigned int position) {
    path_spec_key* p = new path_spec_key();
    path_spec_key_generator::populate(position, *p);
    return p;
}

path_spec_key_generator::result_type
path_spec_key_generator::operator()() {
    return create(position_++);
}

} }
