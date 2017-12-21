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
#include "dogen.modeling/test_data/helpers/mapping_td.hpp"
#include "dogen.modeling/test_data/meta_model/languages_td.hpp"
#include "dogen.modeling/test_data/helpers/mapping_value_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::modeling::meta_model::languages
create_dogen_modeling_meta_model_languages(const unsigned int position) {
    return dogen::modeling::meta_model::languages_generator::create(position);
}

dogen::modeling::helpers::mapping_value
create_dogen_modeling_helpers_mapping_value(const unsigned int position) {
    return dogen::modeling::helpers::mapping_value_generator::create(position);
}

std::unordered_map<dogen::modeling::meta_model::languages, dogen::modeling::helpers::mapping_value> create_std_unordered_map_dogen_modeling_meta_model_languages_dogen_modeling_helpers_mapping_value(unsigned int position) {
    std::unordered_map<dogen::modeling::meta_model::languages, dogen::modeling::helpers::mapping_value> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_modeling_meta_model_languages(position + i), create_dogen_modeling_helpers_mapping_value(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace modeling {
namespace helpers {

mapping_generator::mapping_generator() : position_(0) { }

void mapping_generator::
populate(const unsigned int position, result_type& v) {
    v.lam_id(create_std_string(position + 0));
    v.by_language(create_std_unordered_map_dogen_modeling_meta_model_languages_dogen_modeling_helpers_mapping_value(position + 1));
}

mapping_generator::result_type
mapping_generator::create(const unsigned int position) {
    mapping r;
    mapping_generator::populate(position, r);
    return r;
}

mapping_generator::result_type*
mapping_generator::create_ptr(const unsigned int position) {
    mapping* p = new mapping();
    mapping_generator::populate(position, *p);
    return p;
}

mapping_generator::result_type
mapping_generator::operator()() {
    return create(position_++);
}

} } }
