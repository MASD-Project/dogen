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
#include "dogen/yarn/test_data/meta_model/module_td.hpp"
#include "dogen/yarn/test_data/meta_model/element_td.hpp"
#include "dogen/yarn/test_data/meta_model/orm_module_properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

dogen::yarn::meta_model::orm_module_properties
create_dogen_yarn_meta_model_orm_module_properties(const unsigned int position) {
    return dogen::yarn::meta_model::orm_module_properties_generator::create(position);
}

boost::optional<dogen::yarn::meta_model::orm_module_properties>
create_boost_optional_dogen_yarn_meta_model_orm_module_properties(unsigned int position) {
    boost::optional<dogen::yarn::meta_model::orm_module_properties> r(
        create_dogen_yarn_meta_model_orm_module_properties(position));
    return r;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

module_generator::module_generator() : position_(0) { }

void module_generator::
populate(const unsigned int position, result_type& v) {
    dogen::yarn::meta_model::element_generator::populate(position, v);
    v.members(create_std_list_std_string(position + 0));
    v.is_root(create_bool(position + 1));
    v.is_global_module(create_bool(position + 2));
    v.orm_properties(create_boost_optional_dogen_yarn_meta_model_orm_module_properties(position + 3));
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

} } }
