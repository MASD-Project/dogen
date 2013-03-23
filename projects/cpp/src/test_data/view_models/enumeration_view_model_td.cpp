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
#include <sstream>
#include "dogen/cpp/test_data/view_models/enumeration_view_model_td.hpp"
#include "dogen/cpp/test_data/view_models/enumerator_view_model_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

dogen::cpp::view_models::enumerator_view_model
create_dogen_cpp_view_models_enumerator_view_model(const unsigned int position) {
    return dogen::cpp::view_models::enumerator_view_model_generator::create(position);
}

std::list<dogen::cpp::view_models::enumerator_view_model> create_std_list_dogen_cpp_view_models_enumerator_view_model(unsigned int position) {
    std::list<dogen::cpp::view_models::enumerator_view_model> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_view_models_enumerator_view_model(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace view_models {

enumeration_view_model_generator::enumeration_view_model_generator() : position_(0) { }

void enumeration_view_model_generator::
populate(const unsigned int position, result_type& v) {
    v.namespaces(create_std_list_std_string(position + 0));
    v.enumerators(create_std_list_dogen_cpp_view_models_enumerator_view_model(position + 1));
    v.name(create_std_string(position + 2));
    v.documentation(create_std_string(position + 3));
}

enumeration_view_model_generator::result_type
enumeration_view_model_generator::create(const unsigned int position) {
    enumeration_view_model r;
    enumeration_view_model_generator::populate(position, r);
    return r;
}
enumeration_view_model_generator::result_type*
enumeration_view_model_generator::create_ptr(const unsigned int position) {
    enumeration_view_model* p = new enumeration_view_model();
    enumeration_view_model_generator::populate(position, *p);
    return p;
}

enumeration_view_model_generator::result_type
enumeration_view_model_generator::operator()() {
    return create(position_++);
}

} } }
