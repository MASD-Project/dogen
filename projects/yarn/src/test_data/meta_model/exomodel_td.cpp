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
#include "dogen/yarn/test_data/meta_model/exomodel_td.hpp"
#include "dogen/yarn/test_data/meta_model/exoelement_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
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

dogen::yarn::meta_model::exoelement
create_dogen_yarn_meta_model_exoelement(const unsigned int position) {
    return dogen::yarn::meta_model::exoelement_generator::create(position);
}

std::list<dogen::yarn::meta_model::exoelement> create_std_list_dogen_yarn_meta_model_exoelement(unsigned int position) {
    std::list<dogen::yarn::meta_model::exoelement> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_meta_model_exoelement(position + i));
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

}

namespace dogen {
namespace yarn {
namespace meta_model {

exomodel_generator::exomodel_generator() : position_(0) { }

void exomodel_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.tagged_values(create_std_list_std_pair_std_string_std_string(position + 1));
    v.id(create_std_string(position + 2));
    v.elements(create_std_list_dogen_yarn_meta_model_exoelement(position + 3));
    v.stereotypes(create_std_list_std_string(position + 4));
}

exomodel_generator::result_type
exomodel_generator::create(const unsigned int position) {
    exomodel r;
    exomodel_generator::populate(position, r);
    return r;
}

exomodel_generator::result_type*
exomodel_generator::create_ptr(const unsigned int position) {
    exomodel* p = new exomodel();
    exomodel_generator::populate(position, *p);
    return p;
}

exomodel_generator::result_type
exomodel_generator::operator()() {
    return create(position_++);
}

} } }
