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
#include "dogen/config/test_data/cpp_facet_types_td.hpp"
#include "dogen/cpp/test_data/aspect_types_td.hpp"
#include "dogen/cpp/test_data/content_descriptor_td.hpp"
#include "dogen/cpp/test_data/content_types_td.hpp"
#include "dogen/cpp/test_data/file_types_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"

namespace {

dogen::cpp::file_types
create_dogen_cpp_file_types(const unsigned int position) {
    return dogen::cpp::file_types_generator::create(position);
}

dogen::config::cpp_facet_types
create_dogen_config_cpp_facet_types(const unsigned int position) {
    return dogen::config::cpp_facet_types_generator::create(position);
}

dogen::cpp::aspect_types
create_dogen_cpp_aspect_types(const unsigned int position) {
    return dogen::cpp::aspect_types_generator::create(position);
}

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

dogen::cpp::content_types
create_dogen_cpp_content_types(const unsigned int position) {
    return dogen::cpp::content_types_generator::create(position);
}

}

namespace dogen {
namespace cpp {

content_descriptor_generator::content_descriptor_generator() : position_(0) { }

void content_descriptor_generator::
populate(const unsigned int position, result_type& v) {
    v.file_type(create_dogen_cpp_file_types(position + 0));
    v.facet_type(create_dogen_config_cpp_facet_types(position + 1));
    v.aspect_type(create_dogen_cpp_aspect_types(position + 2));
    v.name(create_dogen_sml_qname(position + 3));
    v.content_type(create_dogen_cpp_content_types(position + 4));
}

content_descriptor_generator::result_type
content_descriptor_generator::create(const unsigned int position) {
    content_descriptor r;
    content_descriptor_generator::populate(position, r);
    return r;
}
content_descriptor_generator::result_type*
content_descriptor_generator::create_ptr(const unsigned int position) {
    content_descriptor* p = new content_descriptor();
    content_descriptor_generator::populate(position, *p);
    return p;
}

content_descriptor_generator::result_type
content_descriptor_generator::operator()() {
    return create(position_++);
}

} }
