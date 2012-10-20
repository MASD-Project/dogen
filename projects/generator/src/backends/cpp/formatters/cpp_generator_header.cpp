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
#include "dogen/generator/backends/cpp/formatters/cpp_generator_header.hpp"

namespace {

const bool is_system(false);
const bool is_user(false);
const std::string missing_class_view_model(
    "File view model must contain a class view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

generator_header::
generator_header(std::ostream& stream) :
    stream_(stream),
    facet_type_(cpp_facet_types::test_data),
    file_type_(cpp_file_types::header),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr generator_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new generator_header(stream));
}

void generator_header::generator_class(const class_view_model& vm) {
    const std::string class_name(vm.name() + "_generator");

    stream_ << indenter_ << "class " << class_name << " ";
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);

        utility_.public_access_specifier();
        stream_ << indenter_ << class_name << "();" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();

        stream_ << indenter_ << "typedef ";
        cpp_qualified_name qualified_name(stream_);
        qualified_name.format(vm);
        stream_ << " result_type;" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();
        stream_ << indenter_
                << "static void populate(const unsigned int position,"
                <<" result_type& v);"
                << std::endl;

        if (!vm.is_parent()) {
            stream_ << indenter_
                    << "static result_type create(const unsigned int position);"
                    << std::endl;

            stream_ << indenter_ << "result_type operator()();" << std::endl;
            utility_.blank_line();

            utility_.private_access_specifier();
            stream_ << indenter_ << "unsigned int "
                    << utility_.as_member_variable("position") << ";"
                    << std::endl;
        }
    }
    stream_ << "};";
}

void generator_header::format(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

    cpp_includes includes(stream_);
    includes.format(vm.system_includes(), is_system);
    includes.format(vm.user_includes(), is_user);
    utility_.blank_line();

    {
        const view_models::class_view_model& cvm(*o);
        std::list<std::string> namespaces(cvm.namespaces());
        namespace_helper ns_helper(stream_, namespaces);
        utility_.blank_line();

        typedef std::list<std::string> list;
        utility_.blank_line();
        generator_class(cvm);
        utility_.blank_line(2);
    }
    utility_.blank_line(2);
    guards.format_end();
}

} } } } }
