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
#include "dogen/generator/backends/cpp/formatters/cpp_inserter_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_utility.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_io_implementation.hpp"

namespace {

const std::string ostream("ostream");
const std::string spaced_inserter(" << ");

const std::string missing_class_view_model(
    "Meta type is pod but class view model is empty");
const std::string missing_enumeration_view_model(
    "Meta type is enumeration but enumeration view model is empty");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

io_implementation::
io_implementation(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) { }

file_formatter::shared_ptr io_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new io_implementation(stream));
}

void io_implementation::format_enumeration(const file_view_model& vm) {
    const auto o(vm.enumeration_vm());
    if (!o)
        throw generation_failure(missing_enumeration_view_model);

    const auto evm(*o);
    namespace_helper ns_helper(stream_, evm.namespaces());
    utility_.blank_line();

    stream_ << "std::ostream& operator<<(std::ostream& s, "
            << "const " << evm.name() << "& v) ";
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "switch (v) ";
        utility_.open_scope();
        {
            for (const auto e : evm.enumerators()) {
                stream_ << indenter_ << "case " << evm.name()
                        << "::" << e.name() << ":"
                        << std::endl;
                {
                    cpp_positive_indenter_scope s(indenter_);
                    stream_ << indenter_ << "return s"
                            << spaced_inserter << utility_.quote(evm.name())
                            << spaced_inserter << utility_.quote("::")
                            << spaced_inserter << utility_.quote(e.name())
                            << ";"
                            << std::endl;
                }
            }
            stream_ << indenter_ << "default:" << std::endl;
            {
                cpp_positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "throw std::invalid_argument("
                        << "\"Invalid value for " << evm.name() << "\");"
                        << std::endl;
            }
            utility_.close_scope();
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void io_implementation::format_class(const file_view_model& vm) {
    const auto o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    const view_models::class_view_model& cvm(*o);
    namespace_helper ns_helper(stream_, cvm.namespaces());
    utility_.blank_line();

    stream_ << "std::ostream& operator<<(std::ostream& s, ";
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << "const " << cvm.name() << "& v) ";
        utility_.open_scope();

        if (cvm.is_parent() || !cvm.parents().empty()) {
            stream_ << indenter_ << "v.to_stream(s);" << std::endl
                    << indenter_ << "return(s);" << std::endl;
        } else {
            const bool inside_class(false);
            cpp_inserter_implementation i(stream_, indenter_, inside_class);
            i.format(cvm);
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void io_implementation::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    cpp_includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration)
        format_enumeration(vm);
    else if (vm.meta_type() == sml::meta_types::pod)
        format_class(vm);
}

} } } } }
