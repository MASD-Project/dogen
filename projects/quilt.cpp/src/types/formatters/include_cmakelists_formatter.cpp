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
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

std::string include_cmakelists_formatter::static_artefact() {
    return traits::include_cmakelists_archetype();
}

std::string include_cmakelists_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location include_cmakelists_formatter::
archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(), cpp::traits::kernel(),
          traits::cmake_facet(),
          include_cmakelists_formatter::static_artefact());
    return r;
}

std::type_index include_cmakelists_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::cmakelists)));
    return r;
}

inclusion_support_types include_cmakelists_formatter::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path include_cmakelists_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::quilt::cpp::formatters;
    static logger lg(
        logger_factory(include_cmakelists_formatter::static_artefact()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path include_cmakelists_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_include_cmakelists(n, static_artefact());
}

std::list<std::string> include_cmakelists_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const yarn::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

dogen::formatters::artefact include_cmakelists_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& c(a.as<fabric::cmakelists>(static_artefact(), e));

    {
        a.make_decoration_preamble();
a.stream() << "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" << c.source_directory_name() << ")" << std::endl;
a.stream() << std::endl;
a.stream() << "install(" << std::endl;
a.stream() << "    DIRECTORY " << c.include_directory_name() << "/" << std::endl;
a.stream() << "    DESTINATION " << c.include_directory_name() << "/" << std::endl;
a.stream() << "    COMPONENT headers" << std::endl;
a.stream() << "    FILES_MATCHING PATTERN \"*." << c.header_file_extension() << "\")" << std::endl;
        if (a.is_odb_facet_enabled()) {
            const auto model_name(a.get_identifiable_model_name(c.name()));
            const auto product_name(a.get_product_name(c.name()));
            const auto odb_folder(a.get_odb_facet_directory());
a.stream() << std::endl;
a.stream() << "set(include_odb_dir \"${CMAKE_CURRENT_SOURCE_DIR}/" << c.odb_include_directory_path() << "\")" << std::endl;
a.stream() << "set(all_odb_files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE all_odb_files RELATIVE" << std::endl;
a.stream() << "    \"${include_odb_dir}/\"" << std::endl;
a.stream() << "    \"${include_odb_dir}/*_" << c.odb_postfix() << "." << c.header_file_extension() << "\")" << std::endl;
a.stream() << std::endl;
a.stream() << "set(src_odb_dir \"${CMAKE_CURRENT_SOURCE_DIR}/" << c.odb_source_directory_path() << "/\")" << std::endl;
a.stream() << "if(NOT EXISTS \"${src_odb_dir}\")" << std::endl;
a.stream() << "    file(MAKE_DIRECTORY \"${src_odb_dir}\")" << std::endl;
a.stream() << "endif()" << std::endl;
a.stream() << std::endl;
a.stream() << "add_custom_target(odb_" << model_name << std::endl;
a.stream() << "    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}" << std::endl;
a.stream() << "    COMMAND mv ${include_odb_dir}/*.cpp ${src_odb_dir})" << std::endl;
a.stream() << std::endl;
a.stream() << "set(ignore_file false)" << std::endl;
a.stream() << "set(include_types_dir \"${CMAKE_CURRENT_SOURCE_DIR}/" << c.types_include_directory_path() << "\")" << std::endl;
a.stream() << "foreach(odb_file ${all_odb_files})" << std::endl;
a.stream() << "    if (odb_file MATCHES \"all_" << c.odb_postfix() << "." << c.header_file_extension() << "\")" << std::endl;
a.stream() << "        set(ignore_file true)" << std::endl;
a.stream() << "    endif()" << std::endl;
a.stream() << std::endl;
a.stream() << "    if(NOT ignore_file)" << std::endl;
a.stream() << "        set(type_name \"\")" << std::endl;
a.stream() << "        string(REPLACE \"_" << c.odb_postfix() << "." << c.header_file_extension() << "\" \"\" type_name ${odb_file})" << std::endl;
a.stream() << "        string(REPLACE \"\\\\\" \"_\" type_name ${type_name})" << std::endl;
a.stream() << "        string(REPLACE \"/\" \"_\" type_name ${type_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "        set(target_name \"odb_" << model_name << "_${type_name}\")" << std::endl;
a.stream() << "        add_custom_target(${target_name}" << std::endl;
a.stream() << "            COMMENT \"ODB ${type_name}\"" << std::endl;
a.stream() << "            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}" << std::endl;
a.stream() << "            COMMAND ${ODB_EXECUTABLE}" << std::endl;
a.stream() << "            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/" << c.odb_options_file_path() << std::endl;
a.stream() << "            --output-dir ${include_odb_dir}/" << std::endl;
a.stream() << "            --odb-epilogue '\\#include \\\"" << c.odb_inclusion_directory_path() << "/${odb_file}\\\"'" << std::endl;
a.stream() << "            -I ${ODB_INCLUDE_DIRS} -I ${CMAKE_CURRENT_SOURCE_DIR}/" << c.include_directory_name() << std::endl;
a.stream() << "            ${include_types_dir}/${type_name}." << c.header_file_extension() << ")" << std::endl;
a.stream() << std::endl;
a.stream() << "        add_dependencies(odb_" << model_name << " ${target_name})" << std::endl;
a.stream() << "    endif()" << std::endl;
a.stream() << "    set(ignore_file false)" << std::endl;
a.stream() << "endforeach()" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
} } } }
