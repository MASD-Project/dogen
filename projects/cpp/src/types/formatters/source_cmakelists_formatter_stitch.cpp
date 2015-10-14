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
#include <boost/algorithm/string/case_conv.hpp>
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/cpp/types/formatters/source_cmakelists_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

dogen::formatters::file source_cmakelists_formatter_stitch(
    formatters::trivial_formatting_assistant& fa,
    const formattables::cmakelists_info& s) {

    {
        fa.make_annotation_preamble(s.general_settings());
        const std::string mn(s.model_name());
fa.stream() << "set(all_files \"\")" << std::endl;
fa.stream() << "file(GLOB_RECURSE all_files RELATIVE" << std::endl;
fa.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
fa.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp\")" << std::endl;
fa.stream() << std::endl;
fa.stream() << "add_library(" << mn << " STATIC ${all_files})" << std::endl;
fa.stream() << "set_target_properties(" << mn << " PROPERTIES" << std::endl;
fa.stream() << "    OUTPUT_NAME " << s.product_name() << (s.product_name().empty() ? "" : "_") << mn << ")" << std::endl;
fa.stream() << std::endl;
fa.stream() << "install(TARGETS " << mn << " ARCHIVE DESTINATION lib COMPONENT libraries)" << std::endl;
    } // sbf
    return fa.make_file(s.source_file_path());
}
} } }
