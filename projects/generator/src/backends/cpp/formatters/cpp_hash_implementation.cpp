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
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_hash_implementation.hpp"

namespace {

const std::string std_ns("std");

const std::string missing_class_view_model(
    "Meta type is pod but class view model is empty");
const std::string enumeration_view_model_not_supported(
    "Enumerations do not have an implementation");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

hash_implementation::
hash_implementation(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr hash_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new hash_implementation(stream));
}

void hash_implementation::combine_function() {
    stream_ << indenter_ << "template <typename HashableType>" << std::endl
            << indenter_ << "inline void combine(std::size_t& seed, "
            << "const HashableType& value)" << std::endl;

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::hash<HashableType> hasher;" << std::endl
                << indenter_ << "seed ^= hasher(value) + 0x9e3779b9 + "
                << "(seed << 6) + (seed >> 2);" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::hasher_hash_method(const class_view_model& vm) {
    stream_ << indenter_ << "std::size_t " << vm.name() << "_hasher::"
            << "hash(const "
            << vm.name() <<  "& v) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);

        stream_ << indenter_ << "std::size_t seed(0);" << std::endl;

        const auto parents(vm.parents());
        if (!parents.empty())
            utility_.blank_line();

        for (const auto p : parents) {
            stream_ << indenter_ << "combine(seed, dynamic_cast<const ";
            cpp_qualified_name qualified_name(stream_);
            qualified_name.format(p);
            stream_ << "&>(v));" << std::endl;
        }

        const auto props(vm.properties());
        if (!props.empty())
            utility_.blank_line();

        for (const auto p : props) {
            stream_ << indenter_ << "combine(seed, v." << p.name()
                    << "());" << std::endl;
        }

        if (props.size() > 1)
            utility_.blank_line();

        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::format_class(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);
    {
        namespace_helper nsh(stream_, std::list<std::string> { });
        utility_.blank_line();
        combine_function();
        utility_.blank_line();
    }
    utility_.blank_line(2);
    {
        const class_view_model& cvm(*o);
        namespace_helper ns_helper(stream_, cvm.namespaces());
        utility_.blank_line();

        hasher_hash_method(cvm);
        utility_.blank_line();
    }
    utility_.blank_line();
}

void hash_implementation::format_enumeration(const file_view_model&) {
    throw generation_failure(enumeration_view_model_not_supported);
}

void hash_implementation::format(const file_view_model& vm) {
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
