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
#include "dogen/generator/backends/cpp/formatters/cpp_hash_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"

namespace {

const bool is_system(true);
const bool is_user(false);
const std::string functional("functional");
const std::string hash_combine("dogen/utility/hash/combine.hpp");
const std::string std_ns("std");

const std::string missing_class_view_model(
    "File view model must contain a class view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

hash_header::
hash_header(std::ostream& stream) :
    stream_(stream),
    facet_type_(cpp_facet_types::hash),
    file_type_(cpp_file_types::header),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr hash_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new hash_header(stream));
}

void hash_header::operator_bracket_method(const class_view_model& vm) {
    stream_ << indenter_ << "size_t operator()(";

    cpp_qualified_name qualified_name(stream_);
    qualified_name.format(vm);

    if (vm.properties().empty())
        stream_ << " /*value*/";
    else
        stream_ << " value";
    stream_ << ") const ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);

        stream_ << indenter_ << "using dogen::utility::hash::combine;"
                << std::endl
                << indenter_ << "std::size_t seed(0);" << std::endl;

        if (!vm.properties().empty()) {
            utility_.blank_line();

            for (const auto p : vm.properties()) {
                stream_ << indenter_ << "combine(seed, value." << p.name()
                        << "());" << std::endl;
            }
            utility_.blank_line();
        }
        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_header::hash_class(const class_view_model& vm) {
    stream_ << indenter_ << "template<>" << std::endl
            << indenter_ << "class hash<";

    cpp_qualified_name qualified_name(stream_);
    qualified_name.format(vm);

    stream_ << "> ";
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        utility_.public_access_specifier();
        operator_bracket_method(vm);
    }
    stream_ << indenter_ << "};" << std::endl;
}

void hash_header::format(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    stream_ << std::endl;

    std::list<std::string> system_dependencies(vm.system_dependencies());
    system_dependencies.push_back(functional);

    std::list<std::string> user_dependencies(vm.user_dependencies());
    user_dependencies.push_back(hash_combine);

    cpp_includes includes(stream_);
    includes.format(system_dependencies, is_system);
    includes.format(user_dependencies, is_user);
    utility_.blank_line();

    {
        std::list<std::string> namespaces;
        namespaces.push_back(std_ns);
        namespace_helper ns_helper(stream_, namespaces);

        utility_.blank_line();
        const view_models::class_view_model& cvm(*o);
        hash_class(cvm);
        utility_.blank_line();
    }

    utility_.blank_line();
    guards.format_end();
}

} } } } }
