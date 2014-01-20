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
#include "dogen/cpp/test_data/content_descriptor_td.hpp"
#include "dogen/cpp/test_data/entity_td.hpp"
#include "dogen/cpp/test_data/includes_td.hpp"
#include "dogen/cpp/test_data/source_file_td.hpp"
#include "dogen/formatters/test_data/annotation_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::cpp::includes
create_dogen_cpp_includes(const unsigned int position) {
    return dogen::cpp::includes_generator::create(position);
}

dogen::cpp::content_descriptor
create_dogen_cpp_content_descriptor(const unsigned int position) {
    return dogen::cpp::content_descriptor_generator::create(position);
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::cpp::entity*
create_dogen_cpp_entity_ptr(const unsigned int position) {
    return dogen::cpp::entity_generator::create_ptr(position);
}

boost::shared_ptr<dogen::cpp::entity>
create_boost_shared_ptr_dogen_cpp_entity(unsigned int position) {
    boost::shared_ptr<dogen::cpp::entity> r(
        create_dogen_cpp_entity_ptr(position));
    return r;
}

dogen::formatters::annotation
create_dogen_formatters_annotation(const unsigned int position) {
    return dogen::formatters::annotation_generator::create(position);
}

}

namespace dogen {
namespace cpp {

source_file_generator::source_file_generator() : position_(0) { }

void source_file_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.includes(create_dogen_cpp_includes(position + 1));
    v.descriptor(create_dogen_cpp_content_descriptor(position + 2));
    v.header_guard(create_std_string(position + 3));
    v.file_path(create_boost_filesystem_path(position + 4));
    v.relative_path(create_boost_filesystem_path(position + 5));
    v.entity(create_boost_shared_ptr_dogen_cpp_entity(position + 6));
    v.annotation(create_dogen_formatters_annotation(position + 7));
}

source_file_generator::result_type
source_file_generator::create(const unsigned int position) {
    source_file r;
    source_file_generator::populate(position, r);
    return r;
}
source_file_generator::result_type*
source_file_generator::create_ptr(const unsigned int position) {
    source_file* p = new source_file();
    source_file_generator::populate(position, *p);
    return p;
}

source_file_generator::result_type
source_file_generator::operator()() {
    return create(position_++);
}

} }
