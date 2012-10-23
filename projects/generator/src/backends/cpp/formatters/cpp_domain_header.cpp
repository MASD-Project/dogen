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
#include "dogen/generator/backends/cpp/formatters/cpp_domain_header.hpp"

namespace {

const std::string invalid_aspect_type("Invalid value for cpp_aspect_types");
const std::string invalid_category_type("Invalid value for category_types");
const std::string missing_class_view_model(
    "File view model must contain a class view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

domain_header::
domain_header(std::ostream& stream, bool disable_complete_constructor,
    bool use_integrated_io, bool disable_io) :
    stream_(stream),
    utility_(stream_, indenter_),
    disable_complete_constructor_(disable_complete_constructor),
    use_integrated_io_(use_integrated_io),
    disable_io_(disable_io) { }

file_formatter::shared_ptr domain_header::
create(std::ostream& stream, bool disable_complete_constructor,
    bool use_integrated_io, bool disable_io) {
    return file_formatter::shared_ptr(new domain_header(stream,
            disable_complete_constructor, use_integrated_io, disable_io));
}

void domain_header::inserter_operator(const class_view_model& vm) {
    if (!use_integrated_io_ || disable_io_)
        return;

    stream_ << indenter_ << "std::ostream& operator<<(std::ostream& s, "
            << "const " << vm.name() << "& v);" << std::endl;
    utility_.blank_line();
}

void domain_header::swap_method(const class_view_model& vm) {
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
class_declaration(const cpp_aspect_types at, const sml::category_types ct,
    const class_view_model& vm) {

    using utility::exception::invalid_enum_value;
    if (at == cpp_aspect_types::main) {

        if (ct == sml::category_types::versioned_key ||
            ct == sml::category_types::unversioned_key) {
            const bool is_versioned(ct == sml::category_types::versioned_key);
            cpp_key_class_declaration
                f(stream_, disable_complete_constructor_, is_versioned,
                    disable_io_);
            f.format(vm);
            return;
        } else if (ct == sml::category_types::user_defined) {
            cpp_domain_class_declaration
                f(stream_, disable_complete_constructor_, disable_io_);
            f.format(vm);
            return;
        }
        throw invalid_enum_value(invalid_category_type);
    }
    throw invalid_enum_value(invalid_aspect_type);
}

void domain_header::format(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

    cpp_includes includes(stream_);
    includes.format(vm);
    utility_.blank_line();

    const view_models::class_view_model& cvm(*o);
    {
        namespace_helper ns(stream_, cvm.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "class " << cvm.name()
                << "_serializer;" << std::endl;
        utility_.blank_line();

        class_declaration(vm.aspect_type(), vm.category_type(), cvm);
        utility_.blank_line();

        inserter_operator(cvm);
    }
    utility_.blank_line(2);

    swap_method(cvm);
    if (!cvm.all_properties().empty())
        utility_.blank_line(2);

    guards.format_end();
}

} } } } }
