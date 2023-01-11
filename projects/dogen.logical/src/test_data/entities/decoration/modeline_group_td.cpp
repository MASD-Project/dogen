/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.logical/test_data/entities/element_td.hpp"
#include "dogen.identification/test_data/entities/logical_id_td.hpp"
#include "dogen.logical/test_data/entities/decoration/modeline_td.hpp"
#include "dogen.logical/test_data/entities/decoration/modeline_group_td.hpp"

namespace {

dogen::identification::entities::logical_id
create_dogen_identification_entities_logical_id(const unsigned int position) {
    return dogen::identification::entities::logical_id_generator::create(position);
}

std::list<dogen::identification::entities::logical_id> create_std_list_dogen_identification_entities_logical_id(unsigned int position) {
    std::list<dogen::identification::entities::logical_id> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_identification_entities_logical_id(position + i));
    }
    return r;
}

dogen::logical::entities::decoration::modeline*
create_dogen_logical_entities_decoration_modeline_ptr(const unsigned int position) {
    return dogen::logical::entities::decoration::modeline_generator::create_ptr(position);
}

boost::shared_ptr<dogen::logical::entities::decoration::modeline>
create_boost_shared_ptr_dogen_logical_entities_decoration_modeline(unsigned int position) {
    boost::shared_ptr<dogen::logical::entities::decoration::modeline> r(
        create_dogen_logical_entities_decoration_modeline_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> > create_std_list_boost_shared_ptr_dogen_logical_entities_decoration_modeline(unsigned int position) {
    std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_logical_entities_decoration_modeline(position + i));
    }
    return r;
}

}

namespace dogen::logical::entities::decoration {

modeline_group_generator::modeline_group_generator() : position_(0) { }

void modeline_group_generator::
populate(const unsigned int position, result_type& v) {
    dogen::logical::entities::element_generator::populate(position, v);
    v.contains(create_std_list_dogen_identification_entities_logical_id(position + 0));
    v.modelines(create_std_list_boost_shared_ptr_dogen_logical_entities_decoration_modeline(position + 1));
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
