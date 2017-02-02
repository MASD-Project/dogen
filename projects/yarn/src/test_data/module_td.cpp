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
#include "dogen/yarn/test_data/name_td.hpp"
#include "dogen/yarn/test_data/module_td.hpp"
#include "dogen/yarn/test_data/element_td.hpp"

namespace {

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

std::list<dogen::yarn::name> create_std_list_dogen_yarn_name(unsigned int position) {
    std::list<dogen::yarn::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_name(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    if (position == 0)
        return true;
    else if (position == 1)
        return false;
    else
        return (position % 2) == 0;
}

}

namespace dogen {
namespace yarn {

module_generator::module_generator() : position_(0) { }

void module_generator::
populate(const unsigned int position, result_type& v) {
    dogen::yarn::element_generator::populate(position, v);
    v.members(create_std_list_dogen_yarn_name(position + 0));
    v.is_root(create_bool(position + 1));
    v.is_global_module(create_bool(position + 2));
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
