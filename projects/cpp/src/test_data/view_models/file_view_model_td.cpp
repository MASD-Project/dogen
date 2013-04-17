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
#include "dogen/config/test_data/cpp_facet_types_td.hpp"
#include "dogen/cpp/test_data/aspect_types_td.hpp"
#include "dogen/cpp/test_data/file_types_td.hpp"
#include "dogen/cpp/test_data/view_models/class_view_model_td.hpp"
#include "dogen/cpp/test_data/view_models/enumeration_view_model_td.hpp"
#include "dogen/cpp/test_data/view_models/exception_view_model_td.hpp"
#include "dogen/cpp/test_data/view_models/file_view_model_td.hpp"
#include "dogen/cpp/test_data/view_models/namespace_view_model_td.hpp"
#include "dogen/cpp/test_data/view_models/registrar_view_model_td.hpp"
#include "dogen/sml/test_data/category_types_td.hpp"
#include "dogen/sml/test_data/meta_types_td.hpp"

namespace {

dogen::config::cpp_facet_types
create_dogen_config_cpp_facet_types(const unsigned int position) {
    return dogen::config::cpp_facet_types_generator::create(position);
}

dogen::cpp::file_types
create_dogen_cpp_file_types(const unsigned int position) {
    return dogen::cpp::file_types_generator::create(position);
}

dogen::cpp::aspect_types
create_dogen_cpp_aspect_types(const unsigned int position) {
    return dogen::cpp::aspect_types_generator::create(position);
}

dogen::sml::category_types
create_dogen_sml_category_types(const unsigned int position) {
    return dogen::sml::category_types_generator::create(position);
}

dogen::sml::meta_types
create_dogen_sml_meta_types(const unsigned int position) {
    return dogen::sml::meta_types_generator::create(position);
}

dogen::cpp::view_models::class_view_model
create_dogen_cpp_view_models_class_view_model(const unsigned int position) {
    return dogen::cpp::view_models::class_view_model_generator::create(position);
}

boost::optional<dogen::cpp::view_models::class_view_model>
create_boost_optional_dogen_cpp_view_models_class_view_model(unsigned int position) {
    boost::optional<dogen::cpp::view_models::class_view_model> r(        create_dogen_cpp_view_models_class_view_model(position));
    return r;
}

dogen::cpp::view_models::enumeration_view_model
create_dogen_cpp_view_models_enumeration_view_model(const unsigned int position) {
    return dogen::cpp::view_models::enumeration_view_model_generator::create(position);
}

boost::optional<dogen::cpp::view_models::enumeration_view_model>
create_boost_optional_dogen_cpp_view_models_enumeration_view_model(unsigned int position) {
    boost::optional<dogen::cpp::view_models::enumeration_view_model> r(        create_dogen_cpp_view_models_enumeration_view_model(position));
    return r;
}

dogen::cpp::view_models::exception_view_model
create_dogen_cpp_view_models_exception_view_model(const unsigned int position) {
    return dogen::cpp::view_models::exception_view_model_generator::create(position);
}

boost::optional<dogen::cpp::view_models::exception_view_model>
create_boost_optional_dogen_cpp_view_models_exception_view_model(unsigned int position) {
    boost::optional<dogen::cpp::view_models::exception_view_model> r(        create_dogen_cpp_view_models_exception_view_model(position));
    return r;
}

dogen::cpp::view_models::registrar_view_model
create_dogen_cpp_view_models_registrar_view_model(const unsigned int position) {
    return dogen::cpp::view_models::registrar_view_model_generator::create(position);
}

boost::optional<dogen::cpp::view_models::registrar_view_model>
create_boost_optional_dogen_cpp_view_models_registrar_view_model(unsigned int position) {
    boost::optional<dogen::cpp::view_models::registrar_view_model> r(        create_dogen_cpp_view_models_registrar_view_model(position));
    return r;
}

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

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::cpp::view_models::namespace_view_model
create_dogen_cpp_view_models_namespace_view_model(const unsigned int position) {
    return dogen::cpp::view_models::namespace_view_model_generator::create(position);
}

boost::optional<dogen::cpp::view_models::namespace_view_model>
create_boost_optional_dogen_cpp_view_models_namespace_view_model(unsigned int position) {
    boost::optional<dogen::cpp::view_models::namespace_view_model> r(        create_dogen_cpp_view_models_namespace_view_model(position));
    return r;
}

}

namespace dogen {
namespace cpp {
namespace view_models {

file_view_model_generator::file_view_model_generator() : position_(0) { }

void file_view_model_generator::
populate(const unsigned int position, result_type& v) {
    v.facet_type(create_dogen_config_cpp_facet_types(position + 0));
    v.file_type(create_dogen_cpp_file_types(position + 1));
    v.aspect_type(create_dogen_cpp_aspect_types(position + 2));
    v.category_type(create_dogen_sml_category_types(position + 3));
    v.meta_type(create_dogen_sml_meta_types(position + 4));
    v.class_vm(create_boost_optional_dogen_cpp_view_models_class_view_model(position + 5));
    v.enumeration_vm(create_boost_optional_dogen_cpp_view_models_enumeration_view_model(position + 6));
    v.exception_vm(create_boost_optional_dogen_cpp_view_models_exception_view_model(position + 7));
    v.registrar_vm(create_boost_optional_dogen_cpp_view_models_registrar_view_model(position + 8));
    v.header_guard(create_std_string(position + 9));
    v.system_includes(create_std_list_std_string(position + 10));
    v.user_includes(create_std_list_std_string(position + 11));
    v.file_path(create_boost_filesystem_path(position + 12));
    v.namespace_vm(create_boost_optional_dogen_cpp_view_models_namespace_view_model(position + 13));
}

file_view_model_generator::result_type
file_view_model_generator::create(const unsigned int position) {
    file_view_model r;
    file_view_model_generator::populate(position, r);
    return r;
}
file_view_model_generator::result_type*
file_view_model_generator::create_ptr(const unsigned int position) {
    file_view_model* p = new file_view_model();
    file_view_model_generator::populate(position, *p);
    return p;
}

file_view_model_generator::result_type
file_view_model_generator::operator()() {
    return create(position_++);
}

} } }
