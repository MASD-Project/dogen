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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.assets/types/meta_model/build/cmakelists.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/tests/traits.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/tests/new_cmakelists_formatter.hpp"

namespace dogen::generation::cpp::formatters::tests {

std::string new_cmakelists_formatter::static_id() {
    return tests::traits::new_cmakelists_archetype();
}

std::string new_cmakelists_formatter::id() const {
    return static_id();
}

archetypes::location new_cmakelists_formatter::
archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          new_cmakelists_formatter::static_id());
    return r;
}

const assets::meta_model::name& new_cmakelists_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_build_cmakelists_name());
    return r;
}

std::string new_cmakelists_formatter::family() const {
    return cpp::traits::cmake_family();
}

inclusion_support_types new_cmakelists_formatter::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path new_cmakelists_formatter::inclusion_path(
    const formattables::locator& /*l*/, const assets::meta_model::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::generation::cpp::formatters;
    static logger lg(logger_factory(new_cmakelists_formatter::static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path new_cmakelists_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_tests_cmakelists(n, static_id());
}

std::list<std::string> new_cmakelists_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const assets::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact new_cmakelists_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    using assets::meta_model::build::cmakelists;
    const auto& c(a.as<cmakelists>(e));

    {

        const auto ts(assets::meta_model::technical_space::cmake);
        a.make_decoration_preamble(e, ts);
        const auto model_name(a.get_dot_separated_model_name(c.name()));
        const auto product_name(a.get_product_name(c.name()));
a.stream() << "set(name \"" << model_name << "\")" << std::endl;
a.stream() << "set(lib_target_name ${name}.lib)" << std::endl;
a.stream() << "set(tests_binary_name ${name}." << c.tests_directory_name() << ")" << std::endl;
a.stream() << "set(tests_target_name ${name}." << c.tests_directory_name() << ")" << std::endl;
a.stream() << std::endl;
a.stream() << "set(files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE files RELATIVE" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*." << c.implementation_file_extension() << "\")" << std::endl;
a.stream() << std::endl;
a.stream() << "add_executable(${tests_target_name} ${files})" << std::endl;
a.stream() << std::endl;
a.stream() << "set_target_properties(${tests_target_name} PROPERTIES" << std::endl;
        if (a.is_cpp_standard_98()) {
a.stream() << "    CXX_STANDARD 98" << std::endl;
        }
a.stream() << "    OUTPUT_NAME ${tests_binary_name})" << std::endl;
a.stream() << std::endl;
        if (a.is_cpp_standard_98()) {
a.stream() << "target_compile_options(${tests_target_name} PRIVATE" << std::endl;
a.stream() << "    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:" << std::endl;
a.stream() << "    -Wno-c99-extensions>)" << std::endl;
        }
a.stream() << std::endl;
a.stream() << "target_link_libraries(${tests_target_name}" << std::endl;
a.stream() << "    ${lib_target_name}" << std::endl;
a.stream() << "    ${CMAKE_REQUIRED_LIBRARIES}" << std::endl;
a.stream() << "    ${CMAKE_THREAD_LIBS_INIT}" << std::endl;
a.stream() << "    ${Boost_LIBRARIES})" << std::endl;
a.stream() << std::endl;
a.stream() << "set(command $<TARGET_FILE:${tests_target_name}> ${boost_test_parameters})" << std::endl;
a.stream() << std::endl;
a.stream() << "add_custom_target(run_${tests_target_name}" << std::endl;
a.stream() << "    COMMENT \"Running ${tests_target_name}\" VERBATIM" << std::endl;
a.stream() << "    COMMAND ${command}" << std::endl;
a.stream() << "    WORKING_DIRECTORY ${stage_bin_dir}" << std::endl;
a.stream() << "    DEPENDS ${tests_target_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "add_dependencies(run_all_tests run_${tests_target_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "if(WITH_BENCHMARKS)" << std::endl;
a.stream() << "    set(benchmark_file" << std::endl;
a.stream() << "        ${benchmark_directory}/${benchmark_prefix}${tests_target_name}.csv)" << std::endl;
a.stream() << "    add_custom_target(benchmark_${tests_target_name}" << std::endl;
a.stream() << "        COMMENT \"Benchmarking testing ${tests_target_name}\" VERBATIM" << std::endl;
a.stream() << "        COMMAND ${benchmark_command} ${benchmark_repeats} ${benchmark_file}" << std::endl;
a.stream() << "        ${command}" << std::endl;
a.stream() << "        WORKING_DIRECTORY ${stage_bin_dir}" << std::endl;
a.stream() << "        DEPENDS ${tests_target_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "    add_dependencies(benchmark_all benchmark_${tests_target_name})" << std::endl;
a.stream() << "endif()" << std::endl;
a.stream() << std::endl;
a.stream() << "add_boost_tests(${tests_binary_name} ${files})" << std::endl;
a.stream() << std::endl;
a.stream() << "install(TARGETS ${tests_target_name} RUNTIME DESTINATION bin COMPONENT tests)" << std::endl;
    } // sbf
        return a.make_artefact();
}
}