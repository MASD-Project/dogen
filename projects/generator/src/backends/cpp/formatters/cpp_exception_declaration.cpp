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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <ostream>
#include <sstream>
#include "dogen/generator/backends/cpp/formatters/cpp_doxygen_comments.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_doxygen_comments.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_exception_declaration.hpp"

namespace {

const std::string empty;

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_exception_declaration::
cpp_exception_declaration(std::ostream& stream)
    : stream_(stream), utility_(stream_, indenter_) { }

void cpp_exception_declaration::format(const exception_view_model& vm) {
    cpp_doxygen_comments dc1(stream_, indenter_);
    dc1.format(vm.documentation());

    stream_ << indenter_ << "class " << vm.name()
            << " : public virtual std::exception,"
            << "public virtual boost::exception ";
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        utility_.public_access_specifier();
        stream_ << indenter_ << vm.name() << "() = default;"
                << std::endl;
        stream_ << indenter_ << "~" << vm.name() << "() noexcept = default;"
                << std::endl;

        utility_.blank_line();
        stream_ << indenter_ << vm.name()
                << "(const std::string& message) : message_(message) { }"
                << std::endl;

        utility_.public_access_specifier();
        stream_ << indenter_ << "const char* what() const noexcept() {"
                << "return(message_.c_str()); }"
                << std::endl;

        utility_.private_access_specifier();
        stream_ << indenter_ << "const std::string message_;"
                << std::endl;
    }
    stream_ << indenter_ << "};" << std::endl;
    utility_.blank_line();
}

} } } } }
