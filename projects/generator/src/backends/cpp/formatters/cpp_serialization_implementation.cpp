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
#include <list>
#include <string>
#include <ostream>
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_serialization_implementation.hpp"

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

serialization_implementation::
serialization_implementation(std::ostream& stream,
    const bool disable_xml_serialization) :
    stream_(stream),
    utility_(stream_, indenter_),
    disable_xml_serialization_(disable_xml_serialization) { }

file_formatter::shared_ptr
serialization_implementation::create(std::ostream& stream,
    const bool disable_xml_serialization) {
    return file_formatter::shared_ptr(
        new serialization_implementation(stream, disable_xml_serialization));
}

void serialization_implementation::save_function(const class_view_model& vm) {
    const auto parents(vm.parents());
    const auto props(vm.properties());
    const bool has_properties(!props.empty());
    const bool has_parents(!parents.empty());
    const bool has_properties_or_parents(has_properties || has_parents);

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void save(Archive& "
            << (has_properties_or_parents ? "ar," : "/*ar*/,")
            << std::endl;

    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "const ";
        cpp_qualified_name qualified_name(stream_);
        qualified_name.format(vm);

        stream_ << (has_properties_or_parents ? "& v," : "& /*v*/,")
                << std::endl
                << indenter_ << "const unsigned int /*version*/) ";

        utility_.open_scope();
        {
            for (const auto p : parents) {
                if (disable_xml_serialization_) {
                    stream_ << indenter_ << "ar << base_object<";
                    qualified_name.format(p);
                    stream_ << ">(v);" << std::endl;
                } else {
                    stream_ << indenter_ << "ar << make_nvp("
                            << utility_.quote(p.name()) << ", base_object<";
                    qualified_name.format(p);
                    stream_ << ">(v));" << std::endl;
                }
            }

            if (has_properties && has_parents)
                utility_.blank_line();

            for (const auto p : props) {
                if (disable_xml_serialization_) {
                    stream_ << indenter_ << "ar << v."
                            << utility_.as_member_variable(p.name())
                            << ";"
                            << std::endl;
                } else {
                    stream_ << indenter_ << "ar << make_nvp("
                            << utility_.quote(p.name())
                            << ", v."
                            << utility_.as_member_variable(p.name())
                            << ");"
                            << std::endl;
                }
            }
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void serialization_implementation::load_function(const class_view_model& vm) {
    const auto parents(vm.parents());
    const auto props(vm.properties());
    const bool has_properties(!props.empty());
    const bool has_parents(!parents.empty());
    const bool has_properties_or_parents(has_properties || has_parents);

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void load(Archive& "
            << (has_properties_or_parents ? "ar," : "/*ar*/,")
            << std::endl;

    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_;
        cpp_qualified_name qualified_name(stream_);
        qualified_name.format(vm);

        stream_ << (has_properties_or_parents ? "& v," : "& /*v*/,")
                << std::endl
                << indenter_ << "const unsigned int /*version*/) ";

        utility_.open_scope();
        {
            for (const auto p : parents) {
                if (disable_xml_serialization_) {
                    stream_ << indenter_
                            << "ar >> "
                            << utility_.quote(p.name())
                            << ", base_object<";
                    qualified_name.format(p);
                    stream_ << ">(v);" << std::endl;
                } else {
                    stream_ << indenter_
                            << "ar >> make_nvp("
                            << utility_.quote(p.name())
                            << ", base_object<";
                    qualified_name.format(p);
                    stream_ << ">(v));" << std::endl;
                }
            }

            if (has_properties && has_parents)
                utility_.blank_line();

            for (const auto p : props) {
                if (disable_xml_serialization_) {
                    stream_ << indenter_ << "ar >> v."
                            << utility_.as_member_variable(p.name())
                            << ";"
                            << std::endl;
                } else {
                    stream_ << indenter_ << "ar >> make_nvp("
                            << utility_.quote(p.name())
                            << ", v."
                            << utility_.as_member_variable(p.name())
                            << ");"
                            << std::endl;
                }
            }
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void serialization_implementation::
template_instantiations(const class_view_model& vm) {
    stream_ << indenter_ << "template void save(archive::text_oarchive& ar, "
            << "const ";
    cpp_qualified_name qualified_name(stream_);
    qualified_name.format(vm);
    stream_ << "& v, unsigned int version);" << std::endl;
    stream_ << indenter_ << "template void load(archive::text_iarchive& ar, ";
    qualified_name.format(vm);
    stream_ << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();

    stream_ << indenter_ << "template void save(archive::binary_oarchive& ar, "
            << "const ";
    qualified_name.format(vm);
    stream_ << "& v, unsigned int version);" << std::endl;
    stream_ << indenter_ << "template void load(archive::binary_iarchive& ar, ";
    qualified_name.format(vm);
    stream_ << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();

    if (!disable_xml_serialization_) {
        stream_ << indenter_ << "template void save(archive::xml_oarchive& ar, "
                << "const ";
        qualified_name.format(vm);
        stream_ << "& v, unsigned int version);" << std::endl;
        stream_ << indenter_ << "template void load(archive::xml_iarchive& ar, ";
        qualified_name.format(vm);
        stream_ << "& v, unsigned int version);" << std::endl;
        utility_.blank_line();
    }
}

void serialization_implementation::format(const file_view_model& vm) {
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
        cpp_qualified_name qualified_name(stream_);
        if (cvm.is_parent() || !cvm.parents().empty()) {
            stream_ << indenter_ << "BOOST_CLASS_TRACKING(" << std::endl;
            {
                cpp_positive_indenter_scope s(indenter_);
                stream_ << indenter_;
                qualified_name.format(cvm);
                stream_ << "," << std::endl;
                stream_ << indenter_ << "boost::serialization"
                        << "::track_selectively)"
                        << std::endl;
            }
            utility_.blank_line();
        }

        {
            std::list<std::string> ns { boost_ns, serialization_ns };
            namespace_helper nsh(stream_, ns);
            utility_.blank_line();
            save_function(cvm);
            load_function(cvm);
        }
        utility_.blank_line(2);

        if (!cvm.is_parent()) {
            stream_ << indenter_ << "BOOST_CLASS_EXPORT_IMPLEMENT(";
            qualified_name.format(cvm);
            stream_ << ")" << std::endl;
            utility_.blank_line();
        }

        {
            std::list<std::string> ns { boost_ns, serialization_ns };
            namespace_helper nsh(stream_, ns);
            utility_.blank_line();
            template_instantiations(cvm);
        }
    }
}

} } } } }
