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
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

dogen::formatters::file include_cmakelists_formatter_stitch(
    assistant& a, const fabric::cmakelists& c) {

    {
        a.make_decoration_preamble();
a.stream() << "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)" << std::endl;
a.stream() << std::endl;
a.stream() << "install(" << std::endl;
a.stream() << "    DIRECTORY include/" << std::endl;
a.stream() << "    DESTINATION include/" << std::endl;
a.stream() << "    COMPONENT headers" << std::endl;
a.stream() << "    FILES_MATCHING PATTERN \"*.hpp\")" << std::endl;
        if (a.is_odb_facet_enabled()) {
            const auto model_name(a.get_identifiable_model_name(c.name()));
            const auto product_name(a.get_product_name(c.name()));
            const auto odb_folder(a.get_odb_facet_directory());
a.stream() << std::endl;
a.stream() << "set(include_dir \"${CMAKE_CURRENT_SOURCE_DIR}/include/" << product_name << "/" << model_name << "\")" << std::endl;
a.stream() << "set(all_odb_files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE all_odb_files RELATIVE" << std::endl;
a.stream() << "    \"${include_dir}/" << odb_folder << "/\"" << std::endl;
a.stream() << "    \"${include_dir}/" << odb_folder << "/*_pragmas.hpp\")" << std::endl;
a.stream() << std::endl;
a.stream() << "set(src_odb_dir \"${CMAKE_CURRENT_SOURCE_DIR}/src/" << odb_folder << "/\")" << std::endl;
a.stream() << "if(NOT EXISTS \"${src_odb_dir}\")" << std::endl;
a.stream() << "    file(MAKE_DIRECTORY \"${src_odb_dir}\")" << std::endl;
a.stream() << "endif()" << std::endl;
a.stream() << std::endl;
a.stream() << "add_custom_target(codegen_" << model_name << "_odb" << std::endl;
a.stream() << "    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}" << std::endl;
a.stream() << "    COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/include/" << product_name << "/" << model_name << "/" << odb_folder << "/*.cpp" << std::endl;
a.stream() << "    ${src_odb_dir})" << std::endl;
a.stream() << std::endl;
a.stream() << "set(ignore_file false)" << std::endl;
a.stream() << "foreach(odb_file ${all_odb_files})" << std::endl;
a.stream() << "    if (odb_file MATCHES \"all_pragmas.hpp\")" << std::endl;
a.stream() << "        set(ignore_file true)" << std::endl;
a.stream() << "    endif()" << std::endl;
a.stream() << std::endl;
a.stream() << "    if(NOT ignore_file)" << std::endl;
a.stream() << "        set(type_name \"\")" << std::endl;
a.stream() << "        string(REPLACE \"_pragmas.hpp\" \"\" type_name ${odb_file})" << std::endl;
a.stream() << "        string(REPLACE \"\\\\\" \"_\" type_name ${type_name})" << std::endl;
a.stream() << "        string(REPLACE \"/\" \"_\" type_name ${type_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "        set(pfh_dir \"$ENV{PFH_LOCATION}\")" << std::endl;
a.stream() << "        set(target_name \"codegen_" << model_name << "_odb_${type_name}\")" << std::endl;
a.stream() << "        add_custom_target(${target_name}" << std::endl;
a.stream() << "            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}" << std::endl;
a.stream() << "            COMMAND odb" << std::endl;
a.stream() << "            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/src/options.odb" << std::endl;
a.stream() << "            --std c++11" << std::endl;
a.stream() << "            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/include/" << product_name << "/" << model_name << "/" << odb_folder << "/" << std::endl;
a.stream() << "            --odb-epilogue '\\#include \\\"" << product_name << "/" << model_name << "/" << odb_folder << "/${odb_file}\\\"'" << std::endl;
a.stream() << "            -I ${pfh_dir}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/include" << std::endl;
a.stream() << "            ${include_dir}/types/${type_name}.hpp)" << std::endl;
a.stream() << std::endl;
a.stream() << "        add_dependencies(codegen_" << model_name << "_odb ${target_name})" << std::endl;
a.stream() << "    endif()" << std::endl;
a.stream() << "    add_dependencies(codegen_" << model_name << "_odb codegen_" << model_name << ")" << std::endl;
a.stream() << "    set(ignore_file false)" << std::endl;
a.stream() << "endforeach()" << std::endl;
        }
    } // sbf
    return a.make_file();
}
} } } }
