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
#include "dogen/generator/backends/cpp/formatters/cpp_serialization_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"

namespace {

const bool is_system(true);
const bool is_user(false);
const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
const std::string nvp("boost/serialization/nvp.hpp");

const std::string missing_class_view_model(
    "File view model must contain a class view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

serialization_header::
serialization_header(std::ostream& stream, bool disable_xml_serialization) :
    stream_(stream),
    facet_type_(cpp_facet_types::serialization),
    file_type_(cpp_file_types::header),
    utility_(stream_, indenter_),
    disable_xml_serialization_(disable_xml_serialization) { }

file_formatter::shared_ptr
serialization_header::create(std::ostream& stream,
    bool disable_xml_serialization) {
    return file_formatter::shared_ptr(
        new serialization_header(stream, disable_xml_serialization));
}

void serialization_header::serialize_method(const class_view_model& vm) {
    stream_ << indenter_ << "template<class Archive>" << std::endl
            << indenter_ << "inline void serialize(Archive & archive,"
            << std::endl;

    {
        cpp_positive_indenter_scope s(indenter_);

        stream_ << indenter_;
        cpp_qualified_name qualified_name(stream_);
        qualified_name.format(vm);

        stream_ << "& value," << std::endl
                << indenter_ << "const unsigned int version) ";
        utility_.open_scope();

        stream_ << indenter_;
        qualified_name.format(vm);

        stream_ << "_serializer serializer;" << std::endl
                << indenter_
                << "serializer.serialize<Archive>(archive, value, version);"
                << std::endl;
    }
    utility_.close_scope();
}

void serialization_header::serializer_class(const class_view_model& vm) {
    stream_ << "class " << vm.name() << "_serializer ";
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        utility_.public_access_specifier();
        const bool has_properties(!vm.properties().empty());

        stream_ << indenter_ << "template<typename Archive>" << std::endl
                << indenter_ << "void serialize(Archive & "
                << (has_properties ? "archive," : "/*archive*/,")
                << std::endl;

        {
            cpp_positive_indenter_scope s(indenter_);
            stream_ << indenter_;
            cpp_qualified_name qualified_name(stream_);
            qualified_name.format(vm);

            stream_ << (has_properties ? "& value," : "& /*value*/,")
                    << std::endl
                    << indenter_ << "const unsigned int /*version*/) ";

            utility_.open_scope();
            {
                if (!disable_xml_serialization_ && has_properties)
                    stream_ << indenter_
                            << "using boost::serialization::make_nvp;"
                            << std::endl;
                utility_.blank_line();

                for (const auto p : vm.properties()) {
                    if (disable_xml_serialization_) {
                        stream_ << indenter_ << "archive & value."
                                << utility_.as_member_variable(p.name())
                                << ";"
                                << std::endl;
                    } else {
                        stream_ << indenter_ << "archive & make_nvp("
                                << utility_.quote(p.name())
                                << ", value."
                                << utility_.as_member_variable(p.name())
                                << ");"
                                << std::endl;
                    }
                }
            }
        }
        utility_.close_scope();
    }
    stream_ << indenter_ << "};" << std::endl;
}

void serialization_header::format(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

    std::list<std::string> system_dependencies(vm.system_dependencies());
    if (!disable_xml_serialization_)
        system_dependencies.push_back(nvp);

    cpp_includes includes(stream_);
    includes.format(system_dependencies, is_system);
    includes.format(vm.user_dependencies(), is_user);
    utility_.blank_line();

    const view_models::class_view_model& cvm(*o);
    {
        namespace_helper helper1(stream_, cvm.namespaces());
        utility_.blank_line();
        serializer_class(cvm);
        utility_.blank_line();
    }
    utility_.blank_line();

    {
        std::list<std::string> namespaces;
        namespaces.push_back(boost_ns);
        namespaces.push_back(serialization_ns);

        utility_.blank_line();
        namespace_helper ns_helper(stream_, namespaces);

        utility_.blank_line();
        serialize_method(cvm);
        utility_.blank_line();
    }

    utility_.blank_line(2);
    guards.format_end();
}

} } } } }
