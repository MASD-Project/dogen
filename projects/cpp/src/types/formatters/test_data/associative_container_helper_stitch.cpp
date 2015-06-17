/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright(C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/formatters/test_data/associative_container_helper_stitch.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace test_data {

void associative_container_helper_stitch(
    formatters::nested_type_formatting_assistant& fa,
    const formattables::nested_type_info& t) {

    const auto key(t.children().front());
    const auto value(t.children().back());
fa.stream() << std::endl;
fa.stream() << t.complete_name() << " create_" << t.complete_identifiable_name() << "(unsigned int position) {" << std::endl;
fa.stream() << "    " << t.complete_name() << " r;" << std::endl;
fa.stream() << "    for (unsigned int i(0); i < 4; ++i) {" << std::endl;
fa.stream() << "        r.insert(std::make_pair(create_" << key.complete_identifiable_name() << "(position + i)," << std::endl;
fa.stream() << "        create_" << value.complete_identifiable_name() << "(position + i)));" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << "    return r;" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
}
} } } }
