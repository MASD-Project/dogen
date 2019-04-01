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
#include "masd.dogen.coding/test_data/meta_model/modeline_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/technical_space_td.hpp"
#include "masd.dogen.generation/test_data/helpers/modeline_repository_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::coding::meta_model::technical_space
create_masd_dogen_coding_meta_model_technical_space(const unsigned int position) {
    return masd::dogen::coding::meta_model::technical_space_generator::create(position);
}

masd::dogen::coding::meta_model::modeline
create_masd_dogen_coding_meta_model_modeline(const unsigned int position) {
    return masd::dogen::coding::meta_model::modeline_generator::create(position);
}

std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> create_std_unordered_map_masd_dogen_coding_meta_model_technical_space_masd_dogen_coding_meta_model_modeline(unsigned int position) {
    std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_masd_dogen_coding_meta_model_technical_space(position + i), create_masd_dogen_coding_meta_model_modeline(position + i)));
    }
    return r;
}

std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> > create_std_unordered_map_std_string_std_unordered_map_masd_dogen_coding_meta_model_technical_space_masd_dogen_coding_meta_model_modeline(unsigned int position) {
    std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_unordered_map_masd_dogen_coding_meta_model_technical_space_masd_dogen_coding_meta_model_modeline(position + i)));
    }
    return r;
}

}

namespace masd::dogen::generation::helpers {

modeline_repository_generator::modeline_repository_generator() : position_(0) { }

void modeline_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.modelines_by_group_by_technical_space(create_std_unordered_map_std_string_std_unordered_map_masd_dogen_coding_meta_model_technical_space_masd_dogen_coding_meta_model_modeline(position + 0));
}

modeline_repository_generator::result_type
modeline_repository_generator::create(const unsigned int position) {
    modeline_repository r;
    modeline_repository_generator::populate(position, r);
    return r;
}

modeline_repository_generator::result_type*
modeline_repository_generator::create_ptr(const unsigned int position) {
    modeline_repository* p = new modeline_repository();
    modeline_repository_generator::populate(position, *p);
    return p;
}

modeline_repository_generator::result_type
modeline_repository_generator::operator()() {
    return create(position_++);
}

}
