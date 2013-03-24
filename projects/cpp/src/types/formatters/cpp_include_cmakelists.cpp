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
#include "dogen/cpp/types/formatters/cpp_include_cmakelists.hpp"

namespace {

const std::string empty("");
const std::string underscore("_");
const std::string unnamed_model("unnamed_model");

}

namespace dogen {
namespace cpp {
namespace formatters {

cpp_include_cmakelists::
cpp_include_cmakelists(std::ostream& stream) : stream_(stream) { }

void cpp_include_cmakelists::format(const cmakelists_view_model& vm) {
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
            << std::endl
            << "install(" << std::endl;

    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "DIRECTORY include/" << std::endl
                << indenter_ << "DESTINATION include/" << std::endl
                << indenter_ << "COMPONENT headers" << std::endl
                << indenter_ << "FILES_MATCHING PATTERN \"*.hpp\")"
                << std::endl;
    }
}

} } }
