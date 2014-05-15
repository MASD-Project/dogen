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
#include <boost/pointer_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/io_header.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.io_header"));

const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");

}

namespace dogen {
namespace cpp_formatters {

io_header::
io_header(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr io_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new io_header(stream));
}

void io_header::format_class(const cpp::file_info& f) {
    auto o(boost::dynamic_pointer_cast<cpp::class_info>(f.entity()));
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    {
        const cpp::class_info& ci(*o);
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

void io_header::format_enumeration(const cpp::file_info& f) {
    auto o(boost::dynamic_pointer_cast<cpp::enum_info>(f.entity()));
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enum_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enum_info));
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

void io_header::format(const cpp::file_info& f) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(f.header_guard());
    utility_.blank_line();

    includes includes(stream_);
    includes.format(f);

    using cpp::content_types;
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
