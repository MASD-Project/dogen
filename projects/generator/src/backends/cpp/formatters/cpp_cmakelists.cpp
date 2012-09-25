/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
