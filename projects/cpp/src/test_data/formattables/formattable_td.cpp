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
#include "dogen/cpp/test_data/formattables/enum_info_td.hpp"
#include "dogen/cpp/test_data/formattables/class_info_td.hpp"
#include "dogen/cpp/test_data/formattables/formattable_td.hpp"
#include "dogen/cpp/test_data/formattables/concept_info_td.hpp"
#include "dogen/cpp/test_data/formattables/visitor_info_td.hpp"
#include "dogen/cpp/test_data/formattables/exception_info_td.hpp"
#include "dogen/cpp/test_data/formattables/includers_info_td.hpp"
#include "dogen/cpp/test_data/formattables/namespace_info_td.hpp"
#include "dogen/cpp/test_data/formattables/primitive_info_td.hpp"
#include "dogen/cpp/test_data/formattables/registrar_info_td.hpp"
#include "dogen/cpp/test_data/formattables/cmakelists_info_td.hpp"
#include "dogen/cpp/test_data/formattables/odb_options_info_td.hpp"
#include "dogen/cpp/test_data/formattables/forward_declarations_info_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace cpp {
namespace formattables {


void formattable_generator::
populate(const unsigned int position, result_type& v) {
    v.identity(create_std_string(position + 0));
}

formattable_generator::result_type*
formattable_generator::create_ptr(const unsigned int position) {
    if ((position % 11) == 0)
        return dogen::cpp::formattables::cmakelists_info_generator::create_ptr(position);
    if ((position % 11) == 1)
        return dogen::cpp::formattables::concept_info_generator::create_ptr(position);
    if ((position % 11) == 2)
        return dogen::cpp::formattables::enum_info_generator::create_ptr(position);
    if ((position % 11) == 3)
        return dogen::cpp::formattables::exception_info_generator::create_ptr(position);
    if ((position % 11) == 4)
        return dogen::cpp::formattables::forward_declarations_info_generator::create_ptr(position);
    if ((position % 11) == 5)
        return dogen::cpp::formattables::includers_info_generator::create_ptr(position);
    if ((position % 11) == 6)
        return dogen::cpp::formattables::namespace_info_generator::create_ptr(position);
    if ((position % 11) == 7)
        return dogen::cpp::formattables::odb_options_info_generator::create_ptr(position);
    if ((position % 11) == 8)
        return dogen::cpp::formattables::primitive_info_generator::create_ptr(position);
    if ((position % 11) == 9)
        return dogen::cpp::formattables::registrar_info_generator::create_ptr(position);
    if ((position % 11) == 10)
        return dogen::cpp::formattables::visitor_info_generator::create_ptr(position);
    return dogen::cpp::formattables::class_info_generator::create_ptr(position);
}


} } }
