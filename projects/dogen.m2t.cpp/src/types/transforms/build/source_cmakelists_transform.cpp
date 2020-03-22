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
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/transforms/build/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/build/source_cmakelists_transform.hpp"

namespace dogen::m2t::cpp::transforms::build {

std::string source_cmakelists_transform::static_id() {
    return traits::source_cmakelists_archetype();
}

std::string source_cmakelists_transform::id() const {
    return static_id();
}

physical::entities::location source_cmakelists_transform::
archetype_location() const {
    static physical::entities::location
        r(cpp::traits::backend(), traits::facet(),
          source_cmakelists_transform::static_id());
    return r;
}

const logical::entities::name& source_cmakelists_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_build_cmakelists_name());
    return r;
}

inclusion_support_types source_cmakelists_transform::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path source_cmakelists_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::m2t::cpp::transforms;
    static logger lg(logger_factory(source_cmakelists_transform::static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path source_cmakelists_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_source_cmakelists(n, static_id());
}

std::list<std::string> source_cmakelists_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

physical::entities::artefact source_cmakelists_transform::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    using logical::entities::build::cmakelists;
    const auto& c(a.as<cmakelists>(e));

    {
        const auto ts(logical::entities::technical_space::cmake);
        a.make_decoration_preamble(e, ts);
        const auto model_name(a.get_dot_separated_model_name(c.name()));
        const auto product_name(a.get_product_name(c.name()));
a.stream() << "set(name \"" << model_name << "\")" << std::endl;
a.stream() << "set(lib_binary_name ${name})" << std::endl;
a.stream() << "set(lib_target_name ${name}.lib)" << std::endl;
a.stream() << std::endl;
a.stream() << "set(files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE files RELATIVE" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*." << c.implementation_file_extension() << "\")" << std::endl;
a.stream() << std::endl;
        if (a.is_odb_facet_enabled() && !c.odb_targets().targets().empty()) {
a.stream() << "set(odb_files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE odb_files RELATIVE" << std::endl;
a.stream() << "   \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
a.stream() << "   \"${CMAKE_CURRENT_SOURCE_DIR}/*.cxx\")" << std::endl;
a.stream() << "set(files ${files} ${odb_files})" << std::endl;
a.stream() << std::endl;
        }
a.stream() << "set(lib_files ${files})" << std::endl;
a.stream() << "add_library(${lib_target_name} ${lib_files})" << std::endl;
a.stream() << "set_target_properties(${lib_target_name} PROPERTIES" << std::endl;
        if (a.is_cpp_standard_98()) {
a.stream() << "    CXX_STANDARD 98" << std::endl;
        }
a.stream() << "    OUTPUT_NAME ${lib_binary_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "install(TARGETS ${lib_target_name}" << std::endl;
a.stream() << "    ARCHIVE DESTINATION lib" << std::endl;
a.stream() << "    LIBRARY DESTINATION lib" << std::endl;
a.stream() << "    COMPONENT libraries)" << std::endl;
        if (a.is_odb_facet_enabled() && !c.odb_targets().targets().empty()) {
            const auto targets(c.odb_targets());
a.stream() << std::endl;
a.stream() << "#" << std::endl;
a.stream() << "# ODB Executable Targets" << std::endl;
a.stream() << "#" << std::endl;
a.stream() << "if (ODB_EXECUTABLE)" << std::endl;
a.stream() << "    # Top-level targets" << std::endl;
a.stream() << "    add_custom_target(" << targets.main_target_name() << ")" << std::endl;
a.stream() << "    add_dependencies(odb_all " << targets.main_target_name() << ")" << std::endl;
a.stream() << std::endl;
a.stream() << "    if (NOT ODB_EXECUTABLE_GLOBAL_ARGS)" << std::endl;
a.stream() << "        message(WARNING \"ODB_EXECUTABLE_GLOBAL_ARGS not defined. Inclusion errors likely when running ODB targets.\")" << std::endl;
a.stream() << "    endif()" << std::endl;
a.stream() << std::endl;
            for (const auto& target : targets.targets()) {
a.stream() << std::endl;
a.stream() << "    add_custom_target(" << target.name() << std::endl;
a.stream() << "        COMMENT \"" << target.comment() << "\"" << std::endl;
a.stream() << "        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}" << std::endl;
a.stream() << "        COMMAND ${ODB_EXECUTABLE}" << std::endl;
a.stream() << "            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/" << targets.common_odb_options() << std::endl;
a.stream() << "            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/" << target.object_odb_options() << std::endl;
a.stream() << "            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/" << target.output_directory() << std::endl;
a.stream() << "            ${ODB_EXECUTABLE_GLOBAL_ARGS}" << std::endl;
a.stream() << "            ${CMAKE_CURRENT_SOURCE_DIR}/" << target.types_file() << std::endl;
                for (const auto& pair : target.move_parameters())
a.stream() << "        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/" << pair.first << " ${CMAKE_CURRENT_SOURCE_DIR}/" << pair.second << std::endl;
a.stream() << "        VERBATIM" << std::endl;
a.stream() << "    )" << std::endl;
a.stream() << "    add_dependencies(" << targets.main_target_name() << " " << target.name() << ")" << std::endl;
            }
a.stream() << "endif()" << std::endl;
        }
    } // sbf
        return a.make_artefact();
}
}
