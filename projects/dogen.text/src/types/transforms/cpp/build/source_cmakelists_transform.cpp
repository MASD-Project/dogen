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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/cpp/build/source_cmakelists_transform.hpp"
#include "dogen.text/types/transforms/cpp/build/source_cmakelists_factory.hpp"

namespace dogen::text::transforms::cpp::build {
namespace {

const std::string transform_id("text.transforms.build.source_cmakelists_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& source_cmakelists_transform::static_archetype() {
    static auto r(source_cmakelists_factory::make());
    return r;
}

const physical::entities::archetype& source_cmakelists_transform::archetype() const {
    return static_archetype();
}
void source_cmakelists_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "source cmakelists",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    using logical::entities::build::cmakelists;
    const auto& c(ast.as<cmakelists>(e));

    {
        const auto ts(identification::entities::technical_space::cmake);
        ast.make_decoration_preamble(e, ts);
        const auto model_name(ast.get_dot_separated_model_name(c.name()));
        const auto product_name(ast.get_product_name(c.name()));
ast.stream() << "set(name \"" << model_name << "\")" << std::endl;
ast.stream() << "set(lib_binary_name ${name})" << std::endl;
ast.stream() << "set(lib_target_name ${name}.lib)" << std::endl;
ast.stream() << std::endl;
ast.stream() << "set(files \"\")" << std::endl;
ast.stream() << "file(GLOB_RECURSE files RELATIVE" << std::endl;
ast.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
ast.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*." << c.implementation_file_extension() << "\")" << std::endl;
ast.stream() << std::endl;
        if (ast.is_odb_facet_enabled() && !c.odb_targets().targets().empty()) {
ast.stream() << "set(odb_files \"\")" << std::endl;
ast.stream() << "file(GLOB_RECURSE odb_files RELATIVE" << std::endl;
ast.stream() << "   \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
ast.stream() << "   \"${CMAKE_CURRENT_SOURCE_DIR}/*.cxx\")" << std::endl;
ast.stream() << "set(files ${files} ${odb_files})" << std::endl;
ast.stream() << std::endl;
        }
ast.stream() << "set(lib_files ${files})" << std::endl;
ast.stream() << "add_library(${lib_target_name} ${lib_files})" << std::endl;
ast.stream() << "set_target_properties(${lib_target_name} PROPERTIES" << std::endl;
        if (ast.is_cpp_standard_98()) {
ast.stream() << "    CXX_STANDARD 98" << std::endl;
        }
ast.stream() << "    OUTPUT_NAME ${lib_binary_name})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "install(TARGETS ${lib_target_name}" << std::endl;
ast.stream() << "    ARCHIVE DESTINATION lib" << std::endl;
ast.stream() << "    LIBRARY DESTINATION lib" << std::endl;
ast.stream() << "    COMPONENT libraries)" << std::endl;
        if (ast.is_odb_facet_enabled() && !c.odb_targets().targets().empty()) {
            const auto targets(c.odb_targets());
ast.stream() << std::endl;
ast.stream() << "#" << std::endl;
ast.stream() << "# ODB Executable Targets" << std::endl;
ast.stream() << "#" << std::endl;
ast.stream() << "if (ODB_EXECUTABLE)" << std::endl;
ast.stream() << "    # Top-level targets" << std::endl;
ast.stream() << "    add_custom_target(" << targets.main_target_name() << ")" << std::endl;
ast.stream() << "    add_dependencies(odb_all " << targets.main_target_name() << ")" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    if (NOT ODB_EXECUTABLE_GLOBAL_ARGS)" << std::endl;
ast.stream() << "        message(WARNING \"ODB_EXECUTABLE_GLOBAL_ARGS not defined. Inclusion errors likely when running ODB targets.\")" << std::endl;
ast.stream() << "    endif()" << std::endl;
ast.stream() << std::endl;
            for (const auto& target : targets.targets()) {
ast.stream() << std::endl;
ast.stream() << "    add_custom_target(" << target.name() << std::endl;
ast.stream() << "        COMMENT \"" << target.comment() << "\"" << std::endl;
ast.stream() << "        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}" << std::endl;
ast.stream() << "        COMMAND ${ODB_EXECUTABLE}" << std::endl;
ast.stream() << "            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/" << targets.common_odb_options() << std::endl;
ast.stream() << "            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/" << target.object_odb_options() << std::endl;
ast.stream() << "            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/" << target.output_directory() << std::endl;
ast.stream() << "            ${ODB_EXECUTABLE_GLOBAL_ARGS}" << std::endl;
ast.stream() << "            ${CMAKE_CURRENT_SOURCE_DIR}/" << target.types_file() << std::endl;
                for (const auto& pair : target.move_parameters())
ast.stream() << "        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/" << pair.first << " ${CMAKE_CURRENT_SOURCE_DIR}/" << pair.second << std::endl;
ast.stream() << "        VERBATIM" << std::endl;
ast.stream() << "    )" << std::endl;
ast.stream() << "    add_dependencies(" << targets.main_target_name() << " " << target.name() << ")" << std::endl;
            }
ast.stream() << "endif()" << std::endl;
        }
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
