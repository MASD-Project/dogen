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
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/visitor_td.hpp"

namespace {

masd::dogen::coding::meta_model::name
create_masd_dogen_coding_meta_model_name(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::name> create_std_list_masd_dogen_coding_meta_model_name(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_name(position + i));
    }
    return r;
}

boost::optional<masd::dogen::coding::meta_model::name>
create_boost_optional_masd_dogen_coding_meta_model_name(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::name> r(
        create_masd_dogen_coding_meta_model_name(position));
    return r;
}

}

namespace masd::dogen::coding::meta_model {

visitor_generator::visitor_generator() : position_(0) { }

void visitor_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
    v.visits(create_std_list_masd_dogen_coding_meta_model_name(position + 0));
    v.parent(create_boost_optional_masd_dogen_coding_meta_model_name(position + 1));
}

visitor_generator::result_type
visitor_generator::create(const unsigned int position) {
    visitor r;
    visitor_generator::populate(position, r);
    return r;
}

visitor_generator::result_type*
visitor_generator::create_ptr(const unsigned int position) {
    visitor* p = new visitor();
    visitor_generator::populate(position, *p);
    return p;
}

visitor_generator::result_type
visitor_generator::operator()() {
    return create(position_++);
}

}
