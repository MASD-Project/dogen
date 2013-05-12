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
#include <boost/throw_exception.hpp>
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/cpp/types/formatters/qname.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/serialization_header.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.serialization_header"));

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
const std::string missing_class_info(
    "Meta type is pod but class view model is empty");
const std::string missing_enumeration_info(
    "Meta type is enumeration but enumeration view model is empty");

}

namespace dogen {
namespace cpp {
namespace formatters {

serialization_header::
serialization_header(std::ostream& stream,
    const bool disable_xml_serialization) :
    stream_(stream), utility_(stream_, indenter_),
    disable_xml_serialization_(disable_xml_serialization) { }

file_formatter::shared_ptr
serialization_header::create(std::ostream& stream,
    const bool disable_xml_serialization) {
    return file_formatter::shared_ptr(
        new serialization_header(stream, disable_xml_serialization));
}

void serialization_header::load_and_save_functions(const class_info& vm) {
    qname qname(stream_);
    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void save(Archive& ar, const ";
    qname.format(vm);
    stream_ << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void load(Archive& ar" << ", ";
    qname.format(vm);
    stream_ << "& v, unsigned int version);" << std::endl;
}

void serialization_header::format_class(const file_info& vm) {
    const auto o(vm.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    const class_info& cvm(*o);
    qname qname(stream_);
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
                    positive_indenter_scope s(indenter_);
                    stream_ << indenter_;
                    qname.format(p);
                    stream_ << "," << std::endl
                            << indenter_;
                    qname.format(cvm);
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
    qname.format(cvm);
    stream_ << ")" << std::endl;

    if (cvm.is_parent()) {
        stream_ << indenter_ << "BOOST_SERIALIZATION_ASSUME_ABSTRACT(";
        qname.format(cvm);
        stream_ << ")" << std::endl;
        utility_.blank_line();
    }

    {
        std::list<std::string> ns { boost_ns, serialization_ns };
        namespace_helper nsh(stream_, ns);
        utility_.blank_line();
        load_and_save_functions(cvm);
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void serialization_header::format_enumeration(const file_info& vm) {
    const auto o(vm.enumeration_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enumeration_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enumeration_info));
    }

    const auto evm(*o);
    stream_ << indenter_ << "template<class Archive>" << std::endl
            << "void serialize(Archive& ar, ";

    qname qnf(stream_);
    qnf.format(evm);

    stream_ << "& v, unsigned int /*version*/)";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        if (disable_xml_serialization_) {
            stream_ << indenter_ << "ar & v;" << std::endl;
        } else {
            stream_ << indenter_ << "using boost::serialization::make_nvp;"
                    << std::endl
                    << indenter_ << "ar & make_nvp(\""
                    << evm.name() << "\", v);" << std::endl;
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void serialization_header::format(const file_info& vm) {
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

    guards.format_end();
}

} } }
