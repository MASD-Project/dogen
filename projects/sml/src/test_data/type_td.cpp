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
#include "dogen/sml/test_data/enumeration_td.hpp"
#include "dogen/sml/test_data/generation_types_td.hpp"
#include "dogen/sml/test_data/object_td.hpp"
#include "dogen/sml/test_data/origin_types_td.hpp"
#include "dogen/sml/test_data/primitive_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/type_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::property_tree::ptree
create_boost_property_tree_ptree(const unsigned int position) {
    using boost::property_tree::ptree;
    ptree c;
    c.put("key_2", position);
    ptree r;
    r.push_back(ptree::value_type("key_1", c));
    return r;
}

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

dogen::sml::generation_types
create_dogen_sml_generation_types(const unsigned int position) {
    return dogen::sml::generation_types_generator::create(position);
}

dogen::sml::origin_types
create_dogen_sml_origin_types(const unsigned int position) {
    return dogen::sml::origin_types_generator::create(position);
}

}

namespace dogen {
namespace sml {


void type_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.meta_data(create_boost_property_tree_ptree(position + 1));
    v.name(create_dogen_sml_qname(position + 2));
    v.generation_type(create_dogen_sml_generation_types(position + 3));
    v.origin_type(create_dogen_sml_origin_types(position + 4));
}

type_generator::result_type*
type_generator::create_ptr(const unsigned int position) {
    if ((position % 2) == 0)
        return dogen::sml::enumeration_generator::create_ptr(position);
    if ((position % 2) == 1)
        return dogen::sml::object_generator::create_ptr(position);
    return dogen::sml::primitive_generator::create_ptr(position);
}


} }
