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
#include <sstream>
#include "dogen/yarn/test_data/meta_model/exoelement_td.hpp"
#include "dogen/yarn/test_data/meta_model/exoattribute_td.hpp"
#include "dogen/yarn/test_data/meta_model/static_stereotypes_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::meta_model::static_stereotypes
create_dogen_yarn_meta_model_static_stereotypes(const unsigned int position) {
    return dogen::yarn::meta_model::static_stereotypes_generator::create(position);
}

std::list<dogen::yarn::meta_model::static_stereotypes> create_std_list_dogen_yarn_meta_model_static_stereotypes(unsigned int position) {
    std::list<dogen::yarn::meta_model::static_stereotypes> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_meta_model_static_stereotypes(position + i));
    }
    return r;
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::list<std::pair<std::string, std::string> > create_std_list_std_pair_std_string_std_string(unsigned int position) {
    std::list<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
    }
    return r;
}

dogen::yarn::meta_model::exoattribute
create_dogen_yarn_meta_model_exoattribute(const unsigned int position) {
    return dogen::yarn::meta_model::exoattribute_generator::create(position);
}

std::list<dogen::yarn::meta_model::exoattribute> create_std_list_dogen_yarn_meta_model_exoattribute(unsigned int position) {
    std::list<dogen::yarn::meta_model::exoattribute> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_meta_model_exoattribute(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

exoelement_generator::exoelement_generator() : position_(0) { }

void exoelement_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.static_stereotypes(create_std_list_dogen_yarn_meta_model_static_stereotypes(position + 1));
    v.dynamic_stereotypes(create_std_list_std_string(position + 2));
    v.tagged_values(create_std_list_std_pair_std_string_std_string(position + 3));
    v.name(create_std_string(position + 4));
    v.parents(create_std_list_std_string(position + 5));
    v.attributes(create_std_list_dogen_yarn_meta_model_exoattribute(position + 6));
    v.can_be_primitive_underlier(create_bool(position + 7));
    v.in_global_module(create_bool(position + 8));
    v.can_be_enumeration_underlier(create_bool(position + 9));
    v.is_default_enumeration_type(create_bool(position + 10));
    v.is_associative_container(create_bool(position + 11));
    v.is_floating_point(create_bool(position + 12));
}

exoelement_generator::result_type
exoelement_generator::create(const unsigned int position) {
    exoelement r;
    exoelement_generator::populate(position, r);
    return r;
}

exoelement_generator::result_type*
exoelement_generator::create_ptr(const unsigned int position) {
    exoelement* p = new exoelement();
    exoelement_generator::populate(position, *p);
    return p;
}

exoelement_generator::result_type
exoelement_generator::operator()() {
    return create(position_++);
}

} } }
