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
#include "dogen/quilt.cpp/types/formatters/source_cmakelists_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include <boost/algorithm/string/case_conv.hpp>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

dogen::formatters::artefact source_cmakelists_formatter_stitch(
    assistant& a, const fabric::cmakelists& c) {

    {
        a.make_decoration_preamble();
        const auto model_name(a.get_identifiable_model_name(c.name()));
        const auto product_name(a.get_product_name(c.name()));
a.stream() << "set(files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE files RELATIVE" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp\")" << std::endl;
a.stream() << std::endl;
a.stream() << "add_library(" << model_name << " STATIC ${files})" << std::endl;
a.stream() << "set_target_properties(" << model_name << " PROPERTIES" << std::endl;
a.stream() << "    OUTPUT_NAME " << product_name << (product_name.empty() ? "" : ".") << model_name << ")" << std::endl;
a.stream() << std::endl;
a.stream() << "install(TARGETS " << model_name << " ARCHIVE DESTINATION lib COMPONENT libraries)" << std::endl;
    } // sbf
        return a.make_artefact();
}
} } } }
