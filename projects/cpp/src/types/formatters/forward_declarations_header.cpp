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
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/qname.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/forward_declarations_header.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.forward_declarations_header"));

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
const std::string invalid_aspect_type("Invalid value for aspect_types");
const std::string invalid_category_type("Invalid value for category_types");

const std::string invalid_facet_types("Invalid value for facet_types");
const std::string missing_class_info(
    "Meta type is pod but class view model is empty");
const std::string missing_enumeration_info(
    "Meta type is enumeration but enumeration view model is empty");
const std::string missing_exception_info(
    "Meta type is exception but enumeration view model is empty");

}

namespace dogen {
namespace cpp {
namespace formatters {

forward_declarations_header::
forward_declarations_header(std::ostream& stream)
    : stream_(stream), utility_(stream_, indenter_) { }

file_formatter::shared_ptr forward_declarations_header::
create(std::ostream& stream) {
    return file_formatter::shared_ptr(new forward_declarations_header(stream));
}

void forward_declarations_header::
format_serialization_class(const class_info& vm) {
    {
        std::list<std::string> ns({ boost_ns, serialization_ns });
        namespace_helper nsh(stream_, ns);
        utility_.blank_line();

        stream_ << indenter_ << "template<class Archive>" << std::endl
            << indenter_ << "void save(Archive& ar, const ";

        qname qname(stream_);
        qname.format(vm);

        stream_ << indenter_ << "& v, unsigned int version);" << std::endl;
        utility_.blank_line();

        stream_ << indenter_ << "template<class Archive>" << std::endl
                << indenter_ << "void load(Archive& ar, ";
        qname.format(vm);

        stream_ << indenter_ << "& v, unsigned int version);" << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void forward_declarations_header::
format_domain_class(const class_info& vm) {
    {
        namespace_helper nsh(stream_, vm.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "class " << vm.name() << ";" << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void forward_declarations_header::format_class(const file_info& vm) {
    boost::optional<class_info> o(vm.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    const auto ft(vm.facet_type());
    const class_info& cvm(*o);
    if (ft == config::cpp_facet_types::serialization)
        format_serialization_class(cvm);
    else if (ft == config::cpp_facet_types::types)
        format_domain_class(cvm);
    else {
        using dogen::utility::exception::invalid_enum_value;
        BOOST_LOG_SEV(lg, error) << invalid_facet_types;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_facet_types));
    }
}

void forward_declarations_header::
format_enumeration(const file_info& vm) {
    const auto o(vm.enumeration_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enumeration_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enumeration_info));
    }

    const auto evm(*o);
    {
        namespace_helper nsh(stream_, evm.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "enum class " << evm.name()
                << " : unsigned int;";
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void forward_declarations_header::format_exception(const file_info& vm) {
    const auto o(vm.exception_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_exception_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_exception_info));
    }

    const auto evm(*o);
    {
        namespace_helper nsh(stream_, evm.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "class " << evm.name() << ";" << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void forward_declarations_header::format(const file_info& vm) {
    if (vm.aspect_type() != aspect_types::forward_decls) {
        using dogen::utility::exception::invalid_enum_value;
        BOOST_LOG_SEV(lg, error) << invalid_facet_types;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_facet_types));
    }

    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

    includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration)
        format_enumeration(vm);
    else if (vm.meta_type() == sml::meta_types::pod)
        format_class(vm);
    else if (vm.meta_type() == sml::meta_types::exception)
        format_exception(vm);

    guards.format_end();
}

} } }
