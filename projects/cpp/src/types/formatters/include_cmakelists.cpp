/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
#include <sstream>
#include <ostream>
#include <boost/algorithm/string/case_conv.hpp>
#include "dogen/cpp/types/formatters/include_cmakelists.hpp"

namespace {

const std::string empty("");
const std::string underscore("_");
const std::string unnamed_model("unnamed_model");

}

namespace dogen {
namespace cpp {
namespace formatters {

include_cmakelists::
include_cmakelists(std::ostream& stream, const bool odb_enabled,
    const std::string odb_folder) : stream_(stream),
                                    odb_enabled_(odb_enabled),
                                    odb_folder_(odb_folder) {}

void include_cmakelists::format(const cmakelists_view_model& vm) {
    const std::string mn(vm.model_name().empty() ?
        unnamed_model :
        vm.model_name());

    stream_ << "# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-"
            << std::endl
            << "#" << std::endl
            << "# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>" << std::endl
            << "#" << std::endl
            << "# This program is free software; you can redistribute it and/or"
            << " modify" << std::endl
            << "# it under the terms of the GNU General Public License as"
            << " published by" << std::endl
            << "# the Free Software Foundation; either version 3 of the License"
            << ", or" << std::endl
            << "# (at your option) any later version." << std::endl
            << "#" << std::endl
            << "# This program is distributed in the hope that it will be "
            << " useful," << std::endl
            << "# but WITHOUT ANY WARRANTY; without even the implied warranty"
            << " of" << std::endl
            << "# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the"
            << std::endl
            << "# GNU General Public License for more details." << std::endl
            << "#" << std::endl
            << "# You should have received a copy of the GNU General "
            << "Public License" << std::endl
            << "# along with this program; if not, write to the Free Software"
            << std::endl
            << "# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,"
            << std::endl << "# MA 02110-1301, USA." << std::endl
            << "#" << std::endl
            << "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)" << std::endl
            << std::endl;

    positive_indenter_scope s(indenter_);
    stream_ << "install(" << std::endl
            << indenter_ << "DIRECTORY include/" << std::endl
            << indenter_ << "DESTINATION include/" << std::endl
            << indenter_ << "COMPONENT headers" << std::endl
            << indenter_ << "FILES_MATCHING PATTERN \"*.hpp\")"
            << std::endl;

    if (!odb_enabled_)
        return;

    stream_  << std::endl
             << "set(include_dir \"${CMAKE_CURRENT_SOURCE_DIR}/include/"
            << vm.product_name() << "/" << vm.model_name() << "\")"
            << std::endl;

    stream_ << "set(all_odb_files \"\")" << std::endl;
    stream_ << "file(GLOB_RECURSE all_odb_files RELATIVE" << std::endl
            << indenter_ << "\"${include_dir}/" << odb_folder_
            << "/\"" << std::endl
            << indenter_ << "\"${include_dir}/" << odb_folder_
            << "/*_pragmas.hpp\")"
            << std::endl << std::endl;

    stream_ << "set(src_odb_dir \"${CMAKE_CURRENT_SOURCE_DIR}/src/"
            << odb_folder_ << "/\")"
            << std::endl
            << "if(NOT EXISTS \"${src_odb_dir}\")" << std::endl
            << indenter_ << "file(MAKE_DIRECTORY \"${src_odb_dir}\")"
            << std::endl
            << "endif()" << std::endl << std::endl;

    stream_ << "add_custom_target(codegen_" << vm.model_name()
            << "_" << odb_folder_ << std::endl
            << indenter_ << "WORKING_DIRECTORY ${CMAKE_BINARY_DIR}" << std::endl
            << indenter_
            << "COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/include/"
            << vm.product_name() << "/"
            << vm.model_name() << "/"
            << odb_folder_ << "/*.cpp" << std::endl
            << indenter_ << "${src_odb_dir})" << std::endl << std::endl;

    stream_ << "set(ignore_file false)" << std::endl
            << "foreach(odb_file ${all_odb_files})" << std::endl;

    stream_ << indenter_ << "if (odb_file MATCHES \"all_pragmas.hpp\")"
            << std::endl;
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "set(ignore_file true)" << std::endl;
    }

    stream_ << indenter_ << "endif()" << std::endl << std::endl
            << indenter_ << "if(NOT ignore_file)" << std::endl;

    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "set(type_name \"\")" << std::endl
                << indenter_ << "string(REPLACE \"_pragmas.hpp\" \"\""
                << " type_name ${odb_file})" << std::endl
                << indenter_ << "string(REPLACE \"\\\\\" \"_\""
                << " type_name ${type_name})" << std::endl
                << indenter_ << "string(REPLACE \"/\" \"_\""
                << " type_name ${type_name})" << std::endl << std::endl;

        stream_ << indenter_ << "set(pfh_dir \"$ENV{PFH_LOCATION}\")"
                << std::endl
                << indenter_ << "set(target_name \"codegen_"
                << vm.model_name() << "_odb_${type_name}\")" << std::endl
                << indenter_ << "add_custom_target(${target_name}"
                << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "WORKING_DIRECTORY ${CMAKE_BINARY_DIR}"
                    << std::endl
                    << indenter_ << "COMMAND odb" << std::endl
                    << indenter_
                    << "--options-file ${CMAKE_CURRENT_SOURCE_DIR}/src/"
                    << "options.odb"
                    << std::endl
                    << indenter_ << "--std c++11" << std::endl
                    << indenter_
                    << "--output-dir ${CMAKE_CURRENT_SOURCE_DIR}/include/"
                    << vm.product_name() << "/" << vm.model_name()
                    << "/" << odb_folder_ << "/" << std::endl
                    << indenter_
                    << "--odb-epilogue '\\#include \\\""
                    << vm.product_name() << "/" << vm.model_name()
                    << "/" << odb_folder_ << "/${odb_file}\\\"'" << std::endl
                    << indenter_
                    << "-I ${pfh_dir}/include -I ${CMAKE_CURRENT_SOURCE_DIR}"
                    << "/include" << std::endl
                    << indenter_
                    << "${include_dir}/types/${type_name}.hpp)" << std::endl
                    << std::endl;
        }

        stream_ << indenter_
                << "add_dependencies(codegen_" << vm.model_name()
                << "_odb ${target_name})" << std::endl;
    }
    stream_ << indenter_ << "endif()" << std::endl
            << indenter_
            << "add_dependencies(codegen_" << vm.model_name() << "_odb "
            << "codegen_" << vm.model_name() << ")"
            << std::endl
            << indenter_ << "set(ignore_file false)" << std::endl;

    stream_ << "endforeach()" << std::endl;
}

} } }
