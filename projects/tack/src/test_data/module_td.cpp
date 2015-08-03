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
#include "dogen/tack/test_data/qname_td.hpp"
#include "dogen/tack/test_data/module_td.hpp"
#include "dogen/dynamic/test_data/object_td.hpp"
#include "dogen/tack/test_data/origin_types_td.hpp"
#include "dogen/tack/test_data/generation_types_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::dynamic::object
create_dogen_dynamic_object(const unsigned int position) {
    return dogen::dynamic::object_generator::create(position);
}

dogen::tack::qname
create_dogen_tack_qname(const unsigned int position) {
    return dogen::tack::qname_generator::create(position);
}

dogen::tack::generation_types
create_dogen_tack_generation_types(const unsigned int position) {
    return dogen::tack::generation_types_generator::create(position);
}

dogen::tack::origin_types
create_dogen_tack_origin_types(const unsigned int position) {
    return dogen::tack::origin_types_generator::create(position);
}

boost::optional<dogen::tack::qname>
create_boost_optional_dogen_tack_qname(unsigned int position) {
    boost::optional<dogen::tack::qname> r(
        create_dogen_tack_qname(position));
    return r;
}

std::list<dogen::tack::qname> create_std_list_dogen_tack_qname(unsigned int position) {
    std::list<dogen::tack::qname> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_tack_qname(position + i));
    }
    return r;
}

}

namespace dogen {
namespace tack {

module_generator::module_generator() : position_(0) { }

void module_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.extensions(create_dogen_dynamic_object(position + 1));
    v.name(create_dogen_tack_qname(position + 2));
    v.generation_type(create_dogen_tack_generation_types(position + 3));
    v.origin_type(create_dogen_tack_origin_types(position + 4));
    v.containing_module(create_boost_optional_dogen_tack_qname(position + 5));
    v.members(create_std_list_dogen_tack_qname(position + 6));
}

module_generator::result_type
module_generator::create(const unsigned int position) {
    module r;
    module_generator::populate(position, r);
    return r;
}

module_generator::result_type*
module_generator::create_ptr(const unsigned int position) {
    module* p = new module();
    module_generator::populate(position, *p);
    return p;
}

module_generator::result_type
module_generator::operator()() {
    return create(position_++);
}

} }
