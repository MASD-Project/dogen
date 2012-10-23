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
#include "dogen/generator/generation_failure.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_domain_class_declaration.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_key_class_declaration.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_class_forward_declaration.hpp"

namespace {

const std::string invalid_facet_types("Invalid value for cpp_facet_types");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class_forward_declaration::
class_forward_declaration(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) { }

void class_forward_declaration::
format(const class_view_model& vm, cpp_facet_types ft) {
    if (ft == cpp_facet_types::domain) {
        stream_ << indenter_ << "class " << vm.name() << ";" << std::endl;
        utility_.blank_line();
        return;
    } else if (ft == cpp_facet_types::serialization) {
        stream_ << indenter_ << "template<class Archive>" << std::endl
                << indenter_ << "void save(Archive& ar, const ";

        cpp_qualified_name qualified_name(stream_);
        qualified_name.format(vm);

        stream_ << indenter_ << "& v, unsigned int version);" << std::endl;
        utility_.blank_line();

        stream_ << indenter_ << "template<class Archive>" << std::endl
                << indenter_ << "void load(Archive& ar, ";
        qualified_name.format(vm);

        stream_ << indenter_ << "& v, unsigned int version);" << std::endl;
        utility_.blank_line();
        return;
    }

    using dogen::utility::exception::invalid_enum_value;
    throw invalid_enum_value(invalid_facet_types);
}

} } } } }
