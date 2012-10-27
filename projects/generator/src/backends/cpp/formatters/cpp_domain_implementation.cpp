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
#include "dogen/generator/backends/cpp/formatters/cpp_inserter_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_utility.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_key_class_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_domain_class_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_domain_implementation.hpp"

namespace {

const std::string inserter("<< ");
const std::string space_inserter(" << ");
const std::string open_bracket(" {");
const std::string close_bracket(" }");
const std::string colon(": ");
const std::string semi_colon(";");
const std::string space(" ");
const std::string comma(",");

const std::string missing_class_view_model(
    "Meta type is pod but class view model is empty");
const std::string missing_enumeration_view_model(
    "Meta type is enumeration but enumeration view model is empty");

const std::string invalid_aspect_type("Invalid value for cpp_aspect_types");
const std::string invalid_category_type("Invalid value for category_types");

// FIXME: until we add support to indenter.
const std::string special_indent("       ");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

domain_implementation::
domain_implementation(std::ostream& stream, bool disable_complete_constructor,
    bool use_integrated_io, bool disable_io) :
    stream_(stream),
    utility_(stream_, indenter_),
    disable_complete_constructor_(disable_complete_constructor),
    use_integrated_io_(use_integrated_io),
    disable_io_(disable_io) { }

file_formatter::shared_ptr domain_implementation::
create(std::ostream& stream, bool disable_complete_constructor,
    bool use_integrated_io, bool disable_io) {
    return file_formatter::shared_ptr(new domain_implementation(stream,
            disable_complete_constructor, use_integrated_io, disable_io));
}

void domain_implementation::
inserter_operator(const class_view_model& vm) {
    if (!use_integrated_io_ || disable_io_)
        return;

    stream_ << indenter_ << "std::ostream& operator<<(std::ostream& s"
            << ", const " << vm.name() << "& v) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);

        if (vm.is_parent() || !vm.parents().empty()) {
            stream_ << indenter_ << "v.to_stream(s);" << std::endl
                    << indenter_ << "return(s);" << std::endl;
        } else {
            const bool inside_class(false);
            cpp_inserter_implementation i(stream_, indenter_, inside_class);
            i.format(vm);
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void domain_implementation::
class_implementation(cpp_aspect_types at, const sml::category_types ct,
    const class_view_model& vm) {

    using utility::exception::invalid_enum_value;
    if (at == cpp_aspect_types::main) {
        if (ct == sml::category_types::versioned_key ||
            ct == sml::category_types::unversioned_key) {
            const bool is_versioned(ct == sml::category_types::versioned_key);
            cpp_key_class_implementation
                f(stream_, is_versioned, disable_complete_constructor_,
                    disable_io_);
            f.format(vm);
            return;
        } else if (ct == sml::category_types::user_defined) {
            cpp_domain_class_implementation
                f(stream_, disable_complete_constructor_, disable_io_);
            f.format(vm);
            return;
        }
        throw invalid_enum_value(invalid_category_type);
    }
    throw invalid_enum_value(invalid_aspect_type);
}

void domain_implementation::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    cpp_includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration) {
        const auto o(vm.enumeration_vm());
        if (!o)
            throw generation_failure(missing_enumeration_view_model);

        const auto evm(*o);
        stream_ << "// FIXME: " << evm.name() << std::endl;
    } else if (vm.meta_type() == sml::meta_types::pod) {
        boost::optional<view_models::class_view_model> o(vm.class_vm());
        if (!o)
            throw generation_failure(missing_class_view_model);

        const view_models::class_view_model& cvm(*o);
        namespace_helper ns_helper(stream_, cvm.namespaces());
        utility_.blank_line();
        class_implementation(vm.aspect_type(), vm.category_type(), cvm);
        inserter_operator(cvm);
    }
}

} } } } }
