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
#include "dogen/cpp/test_data/class_info_td.hpp"
#include "dogen/cpp/test_data/class_specifier_td.hpp"
#include "dogen/cpp/test_data/entity_td.hpp"
#include "dogen/cpp/test_data/enum_info_td.hpp"
#include "dogen/cpp/test_data/exception_info_td.hpp"
#include "dogen/cpp/test_data/namespace_info_td.hpp"
#include "dogen/cpp/test_data/registrar_info_td.hpp"
#include "dogen/cpp/test_data/visitor_info_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace cpp {


void entity_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
}

entity_generator::result_type*
entity_generator::create_ptr(const unsigned int position) {
    if ((position % 6) == 0)
        return dogen::cpp::enum_info_generator::create_ptr(position);
    if ((position % 6) == 1)
        return dogen::cpp::exception_info_generator::create_ptr(position);
    if ((position % 6) == 2)
        return dogen::cpp::registrar_info_generator::create_ptr(position);
    if ((position % 6) == 3)
        return dogen::cpp::namespace_info_generator::create_ptr(position);
    if ((position % 6) == 4)
        return dogen::cpp::visitor_info_generator::create_ptr(position);
    if ((position % 6) == 5)
        return dogen::cpp::class_specifier_generator::create_ptr(position);
    return dogen::cpp::class_info_generator::create_ptr(position);
}


} }
