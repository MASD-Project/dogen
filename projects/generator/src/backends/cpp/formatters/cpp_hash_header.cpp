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
#include <boost/throw_exception.hpp>
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_hash_header.hpp"
#include "dogen/utility/log/logger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("hash_header"));

const std::string std_ns("std");

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

hash_header::
hash_header(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr hash_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new hash_header(stream));
}

void hash_header::operator_bracket_method(const class_view_model& vm) {
    stream_ << indenter_ << "size_t operator()(const ";

    cpp_qualified_name qualified_name(stream_);
    qualified_name.format(vm);

    stream_ << "& v) const ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);

        stream_ << indenter_ << "return ";
        qualified_name.format(vm);
        stream_ << "_hasher::hash(v);" << std::endl;
    }
    utility_.close_scope();
}

void hash_header::hash_helper_class(const class_view_model& vm) {
    stream_ << indenter_ << indenter_ << "class " << vm.name()
            << "_hasher ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        utility_.public_access_specifier();
        stream_ << indenter_ << "static std::size_t hash(const "
                << vm.name() << "& v);" << std::endl;
    }
    stream_ << indenter_ << "};" << std::endl;
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

void hash_header::format_class(const file_view_model& vm) {
    const auto o(vm.enumeration_vm());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enumeration_view_model;
        BOOST_THROW_EXCEPTION(generation_failure(missing_enumeration_view_model));
    }

    const auto evm(*o);
    {
        namespace_helper nsh(stream_, std::list<std::string> { std_ns });
        utility_.blank_line();

        stream_ << indenter_ << "template<>" << std::endl
                << indenter_ << "class hash<";

        cpp_qualified_name qnf(stream_);
        qnf.format(evm);

        stream_ << "> ";
        utility_.open_scope();
        utility_.public_access_specifier();
        {
            cpp_positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "size_t operator()(const ";
            qnf.format(evm);
            stream_ << "& v) const ";
            utility_.open_scope();
            {
                cpp_positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "return std::hash<unsigned int>()("
                        << "static_cast<unsigned int>(v));" << std::endl;
            }
            stream_ << indenter_;
        }
        utility_.close_scope();
        stream_ << "};" << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void hash_header::format_enumeration(const file_view_model& vm) {
    const auto o(vm.class_vm());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_view_model;
        BOOST_THROW_EXCEPTION(generation_failure(missing_class_view_model));
    }

    const view_models::class_view_model& cvm(*o);
    {
        namespace_helper nsh(stream_, cvm.namespaces());
        utility_.blank_line();
        hash_helper_class(cvm);
        utility_.blank_line();
    }

    utility_.blank_line(2);
    {
        std::list<std::string> namespaces;
        namespaces.push_back(std_ns);
        namespace_helper nsh(stream_, namespaces);

        utility_.blank_line();
        hash_class(cvm);
        utility_.blank_line();
    }
    utility_.blank_line();
}

void hash_header::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    stream_ << std::endl;

    cpp_includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration)
        format_class(vm);
    else if (vm.meta_type() == sml::meta_types::pod)
        format_enumeration(vm);
    guards.format_end();
}

} } } } }
