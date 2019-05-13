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
#include "dogen.coding/test_data/meta_model/decoration/licence_td.hpp"
#include "dogen.coding/test_data/meta_model/decoration/modeline_td.hpp"
#include "dogen.coding/test_data/meta_model/decoration/modeline_group_td.hpp"
#include "dogen.coding/test_data/meta_model/decoration/generation_marker_td.hpp"
#include "dogen.coding/test_data/meta_model/decoration/element_repository_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::coding::meta_model::decoration::modeline_group*
create_dogen_coding_meta_model_decoration_modeline_group_ptr(const unsigned int position) {
    return dogen::coding::meta_model::decoration::modeline_group_generator::create_ptr(position);
}

boost::shared_ptr<dogen::coding::meta_model::decoration::modeline_group>
create_boost_shared_ptr_dogen_coding_meta_model_decoration_modeline_group(unsigned int position) {
    boost::shared_ptr<dogen::coding::meta_model::decoration::modeline_group> r(
        create_dogen_coding_meta_model_decoration_modeline_group_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::coding::meta_model::decoration::modeline_group> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_coding_meta_model_decoration_modeline_group(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::coding::meta_model::decoration::modeline_group> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_coding_meta_model_decoration_modeline_group(position + i)));
    }
    return r;
}

dogen::coding::meta_model::decoration::modeline*
create_dogen_coding_meta_model_decoration_modeline_ptr(const unsigned int position) {
    return dogen::coding::meta_model::decoration::modeline_generator::create_ptr(position);
}

boost::shared_ptr<dogen::coding::meta_model::decoration::modeline>
create_boost_shared_ptr_dogen_coding_meta_model_decoration_modeline(unsigned int position) {
    boost::shared_ptr<dogen::coding::meta_model::decoration::modeline> r(
        create_dogen_coding_meta_model_decoration_modeline_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::coding::meta_model::decoration::modeline> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_coding_meta_model_decoration_modeline(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::coding::meta_model::decoration::modeline> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_coding_meta_model_decoration_modeline(position + i)));
    }
    return r;
}

dogen::coding::meta_model::decoration::licence*
create_dogen_coding_meta_model_decoration_licence_ptr(const unsigned int position) {
    return dogen::coding::meta_model::decoration::licence_generator::create_ptr(position);
}

boost::shared_ptr<dogen::coding::meta_model::decoration::licence>
create_boost_shared_ptr_dogen_coding_meta_model_decoration_licence(unsigned int position) {
    boost::shared_ptr<dogen::coding::meta_model::decoration::licence> r(
        create_dogen_coding_meta_model_decoration_licence_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::coding::meta_model::decoration::licence> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_coding_meta_model_decoration_licence(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::coding::meta_model::decoration::licence> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_coding_meta_model_decoration_licence(position + i)));
    }
    return r;
}

dogen::coding::meta_model::decoration::generation_marker*
create_dogen_coding_meta_model_decoration_generation_marker_ptr(const unsigned int position) {
    return dogen::coding::meta_model::decoration::generation_marker_generator::create_ptr(position);
}

boost::shared_ptr<dogen::coding::meta_model::decoration::generation_marker>
create_boost_shared_ptr_dogen_coding_meta_model_decoration_generation_marker(unsigned int position) {
    boost::shared_ptr<dogen::coding::meta_model::decoration::generation_marker> r(
        create_dogen_coding_meta_model_decoration_generation_marker_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::coding::meta_model::decoration::generation_marker> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_coding_meta_model_decoration_generation_marker(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::coding::meta_model::decoration::generation_marker> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_coding_meta_model_decoration_generation_marker(position + i)));
    }
    return r;
}

}

namespace dogen::coding::meta_model::decoration {

element_repository_generator::element_repository_generator() : position_(0) { }

void element_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.modeline_groups(create_std_unordered_map_std_string_boost_shared_ptr_dogen_coding_meta_model_decoration_modeline_group(position + 0));
    v.modelines(create_std_unordered_map_std_string_boost_shared_ptr_dogen_coding_meta_model_decoration_modeline(position + 1));
    v.licences(create_std_unordered_map_std_string_boost_shared_ptr_dogen_coding_meta_model_decoration_licence(position + 2));
    v.generation_markers(create_std_unordered_map_std_string_boost_shared_ptr_dogen_coding_meta_model_decoration_generation_marker(position + 3));
}

element_repository_generator::result_type
element_repository_generator::create(const unsigned int position) {
    element_repository r;
    element_repository_generator::populate(position, r);
    return r;
}

element_repository_generator::result_type*
element_repository_generator::create_ptr(const unsigned int position) {
    element_repository* p = new element_repository();
    element_repository_generator::populate(position, *p);
    return p;
}

element_repository_generator::result_type
element_repository_generator::operator()() {
    return create(position_++);
}

}
