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
#include "dogen/generator/backends/cpp/formatters/cpp_enumeration_declaration.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_domain_header.hpp"

namespace {

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
const std::string invalid_aspect_type("Invalid value for cpp_aspect_types");
const std::string invalid_category_type("Invalid value for category_types");
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

domain_header::
domain_header(std::ostream& stream, const bool disable_complete_constructor,
    const bool use_integrated_io, const bool disable_io,
    const bool disable_serialization) :
    stream_(stream),
    utility_(stream_, indenter_),
    disable_complete_constructor_(disable_complete_constructor),
    use_integrated_io_(use_integrated_io),
    disable_io_(disable_io), disable_serialization_(disable_serialization) { }

file_formatter::shared_ptr domain_header::
create(std::ostream& stream, const bool disable_complete_constructor,
    const bool use_integrated_io, const bool disable_io,
    const bool disable_serialization) {
    return file_formatter::shared_ptr(new domain_header(stream,
            disable_complete_constructor, use_integrated_io, disable_io,
            disable_serialization));
}

void domain_header::
inserter_operator(const class_view_model& vm) {
    if (!use_integrated_io_ || disable_io_)
        return;

    stream_ << indenter_ << "std::ostream& operator<<(std::ostream& s, "
            << "const " << vm.name() << "& v);" << std::endl;
    utility_.blank_line();
}

void domain_header::
swap_method(const class_view_model& vm) {
    // swap overload is only available in leaf classes - MEC++-33
    if (vm.all_properties().empty() || vm.is_parent())
        return;

    namespace_helper ns(stream_, std::list<std::string> { "std" });
    utility_.blank_line();

    stream_ << indenter_ << "template<>" << std::endl
            << indenter_ << "inline void swap(" << std::endl;

    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_;
        cpp_qualified_name qualified_name(stream_);
        qualified_name.format(vm);
        stream_ << "& lhs," << std::endl;

        stream_ << indenter_;
        qualified_name.format(vm);
        stream_ << "& rhs) ";

        utility_.open_scope();
        stream_ << indenter_ << "lhs.swap(rhs);" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void domain_header::
class_declaration(const sml::category_types ct, const class_view_model& vm) {

    using utility::exception::invalid_enum_value;
    if (ct == sml::category_types::versioned_key ||
        ct == sml::category_types::unversioned_key) {
        const bool is_versioned(ct == sml::category_types::versioned_key);
        cpp_key_class_declaration
            f(stream_, disable_complete_constructor_, is_versioned,
                disable_io_, disable_serialization_);
        f.format(vm);
        return;
    } else if (ct == sml::category_types::user_defined) {
        cpp_domain_class_declaration
            f(stream_, disable_complete_constructor_, disable_io_,
                disable_serialization_);
        f.format(vm);
        return;
    }

    throw invalid_enum_value(invalid_category_type);
}

void domain_header::format_main(const sml::category_types ct,
    const class_view_model& vm) {

    {
        namespace_helper ns(stream_, vm.namespaces());
        utility_.blank_line();
        class_declaration(ct, vm);

        if (vm.is_parent()) {
            utility_.blank_line();
            stream_ << indenter_ << "inline " << vm.name() << "::~"<< vm.name()
                    << "() noexcept { }" << std::endl;
            utility_.blank_line();
        }

        inserter_operator(vm);
    }
    utility_.blank_line(2);

    swap_method(vm);
    if (!vm.all_properties().empty())
        utility_.blank_line(2);
}

void domain_header::format_class(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    const auto at(vm.aspect_type());
    const auto ct(vm.category_type());
    const view_models::class_view_model& cvm(*o);
    if (at == cpp_aspect_types::main)
        format_main(ct, cvm);
    else {
        using utility::exception::invalid_enum_value;
        throw invalid_enum_value(invalid_aspect_type);
    }
}

void domain_header::format_enumeration(const file_view_model& vm) {
    const auto o(vm.enumeration_vm());
    if (!o)
        throw generation_failure(missing_enumeration_view_model);

    {
        const auto evm(*o);
        namespace_helper ns(stream_, evm.namespaces());
        utility_.blank_line();
        cpp_enumeration_declaration f(stream_);
        f.format(evm);
    }
    utility_.blank_line(2);
}

void domain_header::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

    cpp_includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration)
        format_enumeration(vm);
    else if (vm.meta_type() == sml::meta_types::pod)
        format_class(vm);

    guards.format_end();
}

} } } } }
