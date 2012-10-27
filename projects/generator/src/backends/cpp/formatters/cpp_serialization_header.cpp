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
#include <string>
#include <list>
#include <ostream>
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_serialization_header.hpp"

namespace {

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
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

serialization_header::
serialization_header(std::ostream& stream) :
    stream_(stream), utility_(stream_, indenter_) { }

file_formatter::shared_ptr
serialization_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new serialization_header(stream));
}

void serialization_header::load_and_save_functions(const class_view_model& vm) {
    cpp_qualified_name qualified_name(stream_);
    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void save(Archive& ar, const ";
    qualified_name.format(vm);
    stream_ << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void load(Archive& ar" << ", ";
    qualified_name.format(vm);
    stream_ << "& v, unsigned int version);" << std::endl;
}

void serialization_header::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

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
        cpp_qualified_name qualified_name(stream_);
        const auto parents(cvm.parents());
        if (!cvm.is_parent() && !parents.empty())
        {
            {
                std::list<std::string> ns { boost_ns };
                namespace_helper nsh(stream_, ns);
                utility_.blank_line();

                for (const auto p : parents) {
                    stream_ << indenter_ << "template<>struct" << std::endl
                            << indenter_ << "is_virtual_base_of<" << std::endl;
                    {
                        cpp_positive_indenter_scope s(indenter_);
                        stream_ << indenter_;
                        qualified_name.format(p);
                        stream_ << "," << std::endl
                                << indenter_;
                        qualified_name.format(cvm);
                        stream_ << std::endl;
                    }
                    stream_ << indenter_ << "> : public mpl::true_ {};"
                            << std::endl;
                    utility_.blank_line();
                }
            }
            utility_.blank_line(2);
        }

        stream_ << indenter_ << "BOOST_SERIALIZATION_SPLIT_FREE(";
        qualified_name.format(cvm);
        stream_ << ")" << std::endl;

        if (cvm.is_parent())
            stream_ << indenter_ << "BOOST_SERIALIZATION_ASSUME_ABSTRACT(";
        else
            stream_ << indenter_ << "BOOST_CLASS_EXPORT_KEY(";
        qualified_name.format(cvm);
        stream_ << ")" << std::endl;
        utility_.blank_line();

        {
            std::list<std::string> ns { boost_ns, serialization_ns };
            namespace_helper nsh(stream_, ns);
            utility_.blank_line();
            load_and_save_functions(cvm);
            utility_.blank_line();
        }
        utility_.blank_line(2);
    }
    guards.format_end();
}

} } } } }
