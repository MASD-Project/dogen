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
#include "dogen/std_model/test_data/class_a_td.hpp"
#include "dogen/std_model/test_data/class_a_unversioned_key_td.hpp"
#include "dogen/std_model/test_data/class_a_versioned_key_td.hpp"
#include "dogen/std_model/test_data/class_g_td.hpp"
#include "dogen/std_model/test_data/pkg1/class_c_td.hpp"

namespace {

dogen::std_model::class_a
create_dogen_std_model_class_a(const unsigned int position) {
    return dogen::std_model::class_a_generator::create(position);
}

dogen::std_model::pkg1::class_c
create_dogen_std_model_pkg1_class_c(const unsigned int position) {
    return dogen::std_model::pkg1::class_c_generator::create(position);
}

std::vector<dogen::std_model::pkg1::class_c> create_std_vector_dogen_std_model_pkg1_class_c(unsigned int position) {
    std::vector<dogen::std_model::pkg1::class_c> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_std_model_pkg1_class_c(position + i));
    }
    return r;
}

std::unordered_map<dogen::std_model::class_a, std::vector<dogen::std_model::pkg1::class_c> > create_std_unordered_map_dogen_std_model_class_a_std_vector_dogen_std_model_pkg1_class_c_(unsigned int position) {
    std::unordered_map<dogen::std_model::class_a, std::vector<dogen::std_model::pkg1::class_c> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_std_model_class_a(position + i), create_std_vector_dogen_std_model_pkg1_class_c(position + i)));
    }
    return r;
}

std::list<dogen::std_model::class_a> create_std_list_dogen_std_model_class_a(unsigned int position) {
    std::list<dogen::std_model::class_a> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_std_model_class_a(position + i));
    }
    return r;
}

std::unordered_map<dogen::std_model::pkg1::class_c, std::list<dogen::std_model::class_a> > create_std_unordered_map_dogen_std_model_pkg1_class_c_std_list_dogen_std_model_class_a_(unsigned int position) {
    std::unordered_map<dogen::std_model::pkg1::class_c, std::list<dogen::std_model::class_a> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_std_model_pkg1_class_c(position + i), create_std_list_dogen_std_model_class_a(position + i)));
    }
    return r;
}

dogen::std_model::class_a_unversioned_key
create_dogen_std_model_class_a_unversioned_key(const unsigned int position) {
    return dogen::std_model::class_a_unversioned_key_generator::create(position);
}

std::unordered_map<dogen::std_model::class_a_unversioned_key, dogen::std_model::class_a> create_std_unordered_map_dogen_std_model_class_a_unversioned_key_dogen_std_model_class_a(unsigned int position) {
    std::unordered_map<dogen::std_model::class_a_unversioned_key, dogen::std_model::class_a> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_std_model_class_a_unversioned_key(position + i), create_dogen_std_model_class_a(position + i)));
    }
    return r;
}

dogen::std_model::class_a_versioned_key
create_dogen_std_model_class_a_versioned_key(const unsigned int position) {
    return dogen::std_model::class_a_versioned_key_generator::create(position);
}

std::unordered_map<dogen::std_model::class_a_versioned_key, dogen::std_model::class_a> create_std_unordered_map_dogen_std_model_class_a_versioned_key_dogen_std_model_class_a(unsigned int position) {
    std::unordered_map<dogen::std_model::class_a_versioned_key, dogen::std_model::class_a> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_std_model_class_a_versioned_key(position + i), create_dogen_std_model_class_a(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace std_model {

class_g_generator::class_g_generator() : position_(0) { }

void class_g_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_std_unordered_map_dogen_std_model_class_a_std_vector_dogen_std_model_pkg1_class_c_(position + 0));
    v.prop_1(create_std_unordered_map_dogen_std_model_pkg1_class_c_std_list_dogen_std_model_class_a_(position + 1));
    v.prop_2(create_std_unordered_map_dogen_std_model_class_a_unversioned_key_dogen_std_model_class_a(position + 2));
    v.prop_3(create_std_unordered_map_dogen_std_model_class_a_versioned_key_dogen_std_model_class_a(position + 3));
}

class_g_generator::result_type
class_g_generator::create(const unsigned int position) {
    class_g r;
    class_g_generator::populate(position, r);
    return r;
}
class_g_generator::result_type*
class_g_generator::create_ptr(const unsigned int position) {
    class_g* p = new class_g();
    class_g_generator::populate(position, *p);
    return p;
}

class_g_generator::result_type
class_g_generator::operator()() {
    return create(position_++);
}

} }
