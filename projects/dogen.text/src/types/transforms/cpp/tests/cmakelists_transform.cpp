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
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/cpp/tests/cmakelists_transform.hpp"
#include "dogen.text/types/transforms/cpp/tests/cmakelists_factory.hpp"

namespace dogen::text::transforms::cpp::tests {
namespace {

const std::string transform_id("text.transforms.tests.cmakelists_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& cmakelists_transform::static_archetype() {
    static auto r(cmakelists_factory::make());
    return r;
}

const physical::entities::archetype& cmakelists_transform::archetype() const {
    return static_archetype();
}

void cmakelists_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "cmakelists",
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
ast.stream() << "set(lib_target_name ${name}.lib)" << std::endl;
ast.stream() << "set(tests_binary_name ${name}." << c.tests_directory_name() << ")" << std::endl;
ast.stream() << "set(tests_target_name ${name}." << c.tests_directory_name() << ")" << std::endl;
ast.stream() << std::endl;
ast.stream() << "set(files \"\")" << std::endl;
ast.stream() << "file(GLOB_RECURSE files RELATIVE" << std::endl;
ast.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
ast.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*." << c.implementation_file_extension() << "\")" << std::endl;
ast.stream() << std::endl;
ast.stream() << "add_executable(${tests_target_name} ${files})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "set_target_properties(${tests_target_name} PROPERTIES" << std::endl;
        if (ast.is_cpp_standard_98()) {
ast.stream() << "    CXX_STANDARD 98" << std::endl;
        }
ast.stream() << "    OUTPUT_NAME ${tests_binary_name})" << std::endl;
ast.stream() << std::endl;
        if (ast.is_cpp_standard_98()) {
ast.stream() << "target_compile_options(${tests_target_name} PRIVATE" << std::endl;
ast.stream() << "    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:" << std::endl;
ast.stream() << "    -Wno-c99-extensions>)" << std::endl;
        }
ast.stream() << std::endl;
ast.stream() << "target_link_libraries(${tests_target_name}" << std::endl;
ast.stream() << "    ${lib_target_name}" << std::endl;
ast.stream() << "    ${CMAKE_REQUIRED_LIBRARIES}" << std::endl;
ast.stream() << "    ${CMAKE_THREAD_LIBS_INIT}" << std::endl;
ast.stream() << "    ${Boost_LIBRARIES})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "set(command $<TARGET_FILE:${tests_target_name}> ${boost_test_parameters})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "add_custom_target(run_${tests_target_name}" << std::endl;
ast.stream() << "    COMMENT \"Running ${tests_target_name}\" VERBATIM" << std::endl;
ast.stream() << "    COMMAND ${command}" << std::endl;
ast.stream() << "    WORKING_DIRECTORY ${stage_bin_dir}" << std::endl;
ast.stream() << "    DEPENDS ${tests_target_name})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "add_dependencies(run_all_tests run_${tests_target_name})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "add_boost_tests(${tests_binary_name} ${files})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "install(TARGETS ${tests_target_name} RUNTIME DESTINATION bin COMPONENT tests)" << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
