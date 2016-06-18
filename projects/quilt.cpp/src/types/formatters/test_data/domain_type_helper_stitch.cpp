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
#include "dogen/quilt.cpp/types/formatters/test_data/domain_type_helper_stitch.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

void domain_type_helper_stitch(
    nested_type_formatting_assistant& a,
    const properties::nested_type_info& t,
    const bool as_pointer) {
a.stream() << std::endl;
a.stream() << t.complete_name() << (as_pointer ? "*" : "") << std::endl;
a.stream() << "create_" << t.complete_identifiable_name() << (as_pointer ? "_ptr" : "") << "(const unsigned int position) {" << std::endl;
a.stream() << "    return " << t.complete_name() << "_generator::create" << (as_pointer ? "_ptr" : "") << "(position);" << std::endl;
a.stream() << "}" << std::endl;
}
} } } } }
