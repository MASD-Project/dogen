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
#include "dogen/cpp/types/formatters/qname.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/io_header.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.io_header"));

const std::string missing_class_info(
    "Meta type is pod but class view model is empty");
const std::string missing_enumeration_info(
    "Meta type is enumeration but enumeration view model is empty");

}

namespace dogen {
namespace cpp {
namespace formatters {

io_header::
io_header(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr io_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new io_header(stream));
}

void io_header::format_class(const file_info& fi) {
    boost::optional<class_info> o(fi.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    {
        const class_info& ci(*o);
        namespace_helper helper1(stream_, ci.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "std::ostream&" << std::endl
                << indenter_ << "operator<<(std::ostream& s,"
                << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << " const ";

            qname qname(stream_);
            qname.format(ci);
            stream_ << "& v);" << std::endl;
            utility_.blank_line();
        }
    }
    utility_.blank_line(2);
}

void io_header::format_enumeration(const file_info& fi) {
    const auto o(fi.enumeration_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enumeration_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enumeration_info));
    }

    const auto ei(*o);
    {
        namespace_helper ns_helper(stream_, ei.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "std::ostream& operator<<(std::ostream& s, "
                << "const " << ei.name() << "& v);" << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void io_header::format(const file_info& fi) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(fi.header_guard());
    utility_.blank_line();

    includes includes(stream_);
    includes.format(fi);

    if (fi.meta_type() == sml::meta_types::enumeration)
        format_enumeration(fi);
    else if (fi.meta_type() == sml::meta_types::pod)
        format_class(fi);

    guards.format_end();
}

} } }
