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
#include "dogen/cpp/io/file_info_io.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/cpp/types/formatters/qname.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/cpp/types/formatters/hash_header.hpp"
#include "dogen/utility/log/logger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.hash_header"));

const std::string std_ns("std");

const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");

}

namespace dogen {
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

void hash_header::operator_bracket_method(const class_info& ci) {
    stream_ << indenter_ << "size_t operator()(const ";

    qname qname(stream_);
    qname.format(ci);

    stream_ << "& v) const ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        stream_ << indenter_ << "return ";
        qname.format(ci);
        stream_ << "_hasher::hash(v);" << std::endl;
    }
    utility_.close_scope();
}

void hash_header::hash_helper_class(const class_info& ci) {
    stream_ << indenter_ << indenter_ << "class " << ci.name()
            << "_hasher ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        utility_.public_access_specifier();
        stream_ << indenter_ << "static std::size_t hash(const "
                << ci.name() << "& v);" << std::endl;
    }
    stream_ << indenter_ << "};" << std::endl;
}

void hash_header::hash_class(const class_info& ci) {
    stream_ << indenter_ << "template<>" << std::endl
            << indenter_ << "class hash<";

    qname qname(stream_);
    qname.format(ci);

    stream_ << "> ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        utility_.public_access_specifier();
        operator_bracket_method(ci);
    }
    stream_ << indenter_ << "};" << std::endl;
}

void hash_header::format_enumeration(const file_info& fi) {
    const auto o(fi.enum_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enum_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enum_info));
    }

    const auto ei(*o);
    {
        namespace_helper nsh(stream_, std::list<std::string> { std_ns });
        utility_.blank_line();

        stream_ << indenter_ << "template<>" << std::endl
                << indenter_ << "class hash<";

        qname qnf(stream_);
        qnf.format(ei);

        stream_ << "> ";
        utility_.open_scope();
        utility_.public_access_specifier();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "size_t operator()(const ";
            qnf.format(ei);
            stream_ << "& v) const ";
            utility_.open_scope();
            {
                positive_indenter_scope s(indenter_);
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

void hash_header::format_class(const file_info& fi) {
    const auto o(fi.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    const class_info& ci(*o);
    {
        namespace_helper nsh(stream_, ci.namespaces());
        utility_.blank_line();
        hash_helper_class(ci);
        utility_.blank_line();
    }

    utility_.blank_line(2);
    {
        std::list<std::string> namespaces;
        namespaces.push_back(std_ns);
        namespace_helper nsh(stream_, namespaces);

        utility_.blank_line();
        hash_class(ci);
        utility_.blank_line();
    }
    utility_.blank_line();
}

void hash_header::format(const file_info& fi) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(fi.header_guard());
    stream_ << std::endl;

    includes includes(stream_);
    includes.format(fi);

    if (fi.descriptor().content_type() == content_types::unversioned_key ||
        fi.descriptor().content_type() == content_types::versioned_key ||
        fi.descriptor().content_type() == content_types::value_object ||
        fi.descriptor().content_type() == content_types::entity ||
        fi.descriptor().content_type() == content_types::keyed_entity)
        format_class(fi);
    else if (fi.descriptor().content_type() == content_types::enumeration)
        format_enumeration(fi);

    guards.format_end();
}

} } }
