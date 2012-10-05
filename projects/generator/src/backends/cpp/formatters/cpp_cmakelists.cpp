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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <sstream>
#include <ostream>
#include "dogen/generator/backends/cpp/formatters/cpp_cmakelists.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_cmakelists::cpp_cmakelists(std::ostream& stream) : stream_(stream) {
}

void cpp_cmakelists::format(view_models::cmakelists_view_model vm) {
    stream_ << "# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-"
            << std::endl
            << "#" << std::endl
            << "# Copyright (C) 2012 Kitanda" << std::endl
            << "#" << std::endl
            << "# This file is distributed under the Kitanda Proprietary Software"
            << std::endl
            << "# Licence. See doc/LICENCE.TXT for details." << std::endl
            << "#" << std::endl
            << "set(all_files \"\")" << std::endl
            << "file(GLOB_RECURSE all_files RELATIVE" << std::endl
            << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl
            << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp\")" << std::endl
            << std::endl
            << "add_library(" << vm.model_name() << " STATIC ${all_files})"
            << std::endl
            << "set_target_properties(" << vm.model_name() << " PROPERTIES"
            << std::endl << "    OUTPUT_NAME dogen_" << vm.model_name() << ")"
            << std::endl;
}

} } } } }
