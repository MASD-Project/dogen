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
#include "dogen/cpp/test_data/formattables/class_info_td.hpp"
#include "dogen/cpp/test_data/formattables/cmakelists_info_td.hpp"
#include "dogen/cpp/test_data/formattables/concept_info_td.hpp"
#include "dogen/cpp/test_data/formattables/enum_info_td.hpp"
#include "dogen/cpp/test_data/formattables/exception_info_td.hpp"
#include "dogen/cpp/test_data/formattables/file_properties_td.hpp"
#include "dogen/cpp/test_data/formattables/formattable_td.hpp"
#include "dogen/cpp/test_data/formattables/namespace_info_td.hpp"
#include "dogen/cpp/test_data/formattables/new_class_info_td.hpp"
#include "dogen/cpp/test_data/formattables/odb_options_info_td.hpp"
#include "dogen/cpp/test_data/formattables/primitive_info_td.hpp"
#include "dogen/cpp/test_data/formattables/registrar_info_td.hpp"
#include "dogen/cpp/test_data/formattables/visitor_info_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::cpp::formattables::file_properties
create_dogen_cpp_formattables_file_properties(const unsigned int position) {
    return dogen::cpp::formattables::file_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::cpp::formattables::file_properties> create_std_unordered_map_std_string_dogen_cpp_formattables_file_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::cpp::formattables::file_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_cpp_formattables_file_properties(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formattables {


void formattable_generator::
populate(const unsigned int position, result_type& v) {
    v.identity(create_std_string(position + 0));
    v.file_properties_by_formatter_name(create_std_unordered_map_std_string_dogen_cpp_formattables_file_properties(position + 1));
}

formattable_generator::result_type*
formattable_generator::create_ptr(const unsigned int position) {
    if ((position % 10) == 0)
        return dogen::cpp::formattables::cmakelists_info_generator::create_ptr(position);
    if ((position % 10) == 1)
        return dogen::cpp::formattables::enum_info_generator::create_ptr(position);
    if ((position % 10) == 2)
        return dogen::cpp::formattables::exception_info_generator::create_ptr(position);
    if ((position % 10) == 3)
        return dogen::cpp::formattables::registrar_info_generator::create_ptr(position);
    if ((position % 10) == 4)
        return dogen::cpp::formattables::odb_options_info_generator::create_ptr(position);
    if ((position % 10) == 5)
        return dogen::cpp::formattables::namespace_info_generator::create_ptr(position);
    if ((position % 10) == 6)
        return dogen::cpp::formattables::visitor_info_generator::create_ptr(position);
    if ((position % 10) == 7)
        return dogen::cpp::formattables::new_class_info_generator::create_ptr(position);
    if ((position % 10) == 8)
        return dogen::cpp::formattables::concept_info_generator::create_ptr(position);
    if ((position % 10) == 9)
        return dogen::cpp::formattables::primitive_info_generator::create_ptr(position);
    return dogen::cpp::formattables::class_info_generator::create_ptr(position);
}


} } }
