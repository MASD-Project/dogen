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
#include "dogen/quilt.cpp/types/formatters/test_data/variant_helper_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

void variant_helper_stitch(
    formatters::nested_type_formatting_assistant& fa,
    const formattables::nested_type_info& t) {
fa.stream() << std::endl;
fa.stream() << t.complete_name() << std::endl;
fa.stream() << "create_" << t.complete_identifiable_name() << "(unsigned int position) {" << std::endl;
fa.stream() << "    " << t.complete_name() << " r;" << std::endl;
fa.stream() << std::endl;
    unsigned int i(0);
    for (const auto& c : t.children()) {
        if (i == 0)
fa.stream() << "    if (position == 0 || ((position % " << t.children().size() << ") == 0))" << std::endl;
        else if (i == 1)
fa.stream() << "    else if (position == 1 || ((position % " << t.children().size() + 1 << ") == 0))" << std::endl;
        else
fa.stream() << "    else if ((position % " << i << ") == 0)" << std::endl;
fa.stream() << "        r = create_" << c.complete_identifiable_name() << "(position);" << std::endl;
        ++i;
    }
fa.stream() << std::endl;
fa.stream() << "    return r;" << std::endl;
fa.stream() << "}" << std::endl;
}
} } } } }
