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
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_generator_implementation.hpp"

namespace {

const bool is_system(true);
const bool is_user(false);
const std::string detail_ns("detail");

const std::string missing_class_view_model(
    "File view model must contain a class view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

generator_implementation::
generator_implementation(std::ostream& stream) :
    stream_(stream),
    facet_type_(cpp_facet_types::test_data),
    file_type_(cpp_file_types::implementation),
    utility_(stream_, indenter_),
    generator_length_(3) { }

file_formatter::shared_ptr
generator_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new generator_implementation(stream));
}

void generator_implementation::
next_term_method(const class_view_model& vm) {
    const std::string name(vm.name() + "_generator");
    stream_ << indenter_ << name << "::value_type" << std::endl
            << indenter_ << name << "::next_term(const unsigned int position) ";
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << vm.name() << " r;" << std::endl;
        utility_.blank_line();

        bool is_first(true);
        for (unsigned int i(0); i < generator_length_; ++i) {
            stream_ << indenter_ << (is_first ? "" : "} else ")
                    << "if (position == " << i << ") ";
            utility_.open_scope();
            {
                cpp_positive_indenter_scope s(indenter_);
                unsigned int j(0);
                for (const auto p : vm.properties()) {
                    if (p.is_primitive()) {
                        stream_ << indenter_ << "r." << p.name()
                                << "(" << "static_cast<" << p.type()
                                << ">("
                                << (i * 30 + j) << "));"
                                << std::endl;
                    }
                    ++j;
                }
            }
            is_first = false;
        }
        utility_.close_scope();
        utility_.blank_line();

        stream_ << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
}

void generator_implementation::length_method(const class_view_model& vm) {
    stream_ << indenter_ << "unsigned int "
            << vm.name() << "_generator::length() const { return("
            << generator_length_ << "); }" << std::endl;
}

void generator_implementation::format(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    licence licence(stream_);
    licence.format();

    cpp_includes includes(stream_);
    includes.format(vm.system_includes(), is_system);
    includes.format(vm.user_includes(), is_user);
    utility_.blank_line();

    {
        const view_models::class_view_model& cvm(*o);
        std::list<std::string> ns(cvm.namespaces());
        ns.push_back(detail_ns);
        namespace_helper ns_helper(stream_, ns);

        utility_.blank_line();
        next_term_method(cvm);
        utility_.blank_line();
        length_method(cvm);
        utility_.blank_line();
    }
    utility_.blank_line();
}

} } } } }
