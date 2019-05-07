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
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/modeline_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/modeline_group_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_set<std::string> create_std_unordered_set_std_string(unsigned int position) {
    std::unordered_set<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

masd::dogen::coding::meta_model::decoration::modeline*
create_masd_dogen_coding_meta_model_decoration_modeline_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::decoration::modeline_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline>
create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> r(
        create_masd_dogen_coding_meta_model_decoration_modeline_ptr(position));
    return r;
}

std::list<boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> > create_std_list_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline(unsigned int position) {
    std::list<boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline(position + i));
    }
    return r;
}

}

namespace masd::dogen::coding::meta_model::decoration {

modeline_group_generator::modeline_group_generator() : position_(0) { }

void modeline_group_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
    v.contains(create_std_unordered_set_std_string(position + 0));
    v.modelines(create_std_list_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline(position + 1));
}

modeline_group_generator::result_type
modeline_group_generator::create(const unsigned int position) {
    modeline_group r;
    modeline_group_generator::populate(position, r);
    return r;
}

modeline_group_generator::result_type*
modeline_group_generator::create_ptr(const unsigned int position) {
    modeline_group* p = new modeline_group();
    modeline_group_generator::populate(position, *p);
    return p;
}

modeline_group_generator::result_type
modeline_group_generator::operator()() {
    return create(position_++);
}

}
