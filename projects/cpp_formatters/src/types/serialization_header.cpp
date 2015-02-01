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
#include <boost/pointer_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/cpp/types/formattables/enum_info.hpp"
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/serialization_header.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.serialization_header"));

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");

}

namespace dogen {
namespace cpp_formatters {

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

void serialization_header::load_and_save_functions(
    const cpp::formattables::class_info& ci) {
    qname qname(stream_);
    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void save(Archive& ar, const ";
    qname.format(ci);
    stream_ << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void load(Archive& ar" << ", ";
    qname.format(ci);
    stream_ << "& v, unsigned int version);" << std::endl;
}

void serialization_header::format_class(const cpp::formattables::file_info& f) {
    auto o(boost::dynamic_pointer_cast<
            cpp::formattables::class_info>(f.entity()));

    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    const cpp::formattables::class_info& ci(*o);
    qname qname(stream_);
    const auto parents(ci.parents());
    if (!ci.is_parent() && !parents.empty())
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
                    qname.format(ci);
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
    qname.format(ci);
    stream_ << ")" << std::endl;

    if (ci.is_parent()) {
        stream_ << indenter_ << "BOOST_SERIALIZATION_ASSUME_ABSTRACT(";
        qname.format(ci);
        stream_ << ")" << std::endl;
        utility_.blank_line();
    }

    {
        std::list<std::string> ns { boost_ns, serialization_ns };
        namespace_helper nsh(stream_, ns);
        utility_.blank_line();
        load_and_save_functions(ci);
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void serialization_header::format_enumeration(
    const cpp::formattables::file_info& f) {
    auto o(boost::dynamic_pointer_cast<
            cpp::formattables::enum_info>(f.entity()));
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enum_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enum_info));
    }

    const auto ei(*o);
    stream_ << indenter_ << "template<class Archive>" << std::endl
            << "void serialize(Archive& ar, ";

    qname qnf(stream_);
    qnf.format(ei);

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
                    << ei.name() << "\", v);" << std::endl;
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void serialization_header::format(const cpp::formattables::file_info& f) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(f.header_guard());
    utility_.blank_line();

    includes includes(stream_);
    includes.format(f);

    using cpp::formattables::content_types;
    if (f.descriptor().content_type() == content_types::unversioned_key ||
        f.descriptor().content_type() == content_types::versioned_key ||
        f.descriptor().content_type() == content_types::value_object ||
        f.descriptor().content_type() == content_types::entity ||
        f.descriptor().content_type() == content_types::keyed_entity)
        format_class(f);
    else if (f.descriptor().content_type() == content_types::enumeration)
        format_enumeration(f);

    guards.format_end();
}

} }
