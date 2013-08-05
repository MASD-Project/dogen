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
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/inserter_implementation.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/io_implementation.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.io_implementation"));

const std::string ostream("ostream");
const std::string spaced_inserter(" << ");
const std::string type("__type__");
const std::string colon(": ");
const std::string comma(", ");
const std::string semi_colon(";");

const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");

}

namespace dogen {
namespace cpp_formatters {

io_implementation::
io_implementation(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) { }

file_formatter::shared_ptr io_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new io_implementation(stream));
}

void io_implementation::io_helper_methods(const cpp::class_info& ci) {
    if (ci.is_parent() || !ci.parents().empty())
        return;

    const bool inside_class(false);
    inserter_implementation i(stream_, indenter_, inside_class);
    i.format_helper_methods(ci);
}

void io_implementation::format_enumeration(const cpp::file_info& fi) {
    const auto o(fi.enum_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enum_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enum_info));
    }

    const auto ei(*o);
    namespace_helper ns_helper(stream_, ei.namespaces());
    utility_.blank_line();

    stream_ << "std::ostream& operator<<(std::ostream& s, "
            << "const " << ei.name() << "& v) ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "s" << spaced_inserter
                << utility_.quote("{ ") << spaced_inserter
                << utility_.quote(utility_.quote_escaped(type) + colon);

        stream_ << spaced_inserter
                << utility_.quote(utility_.quote_escaped(ei.name()) + comma)
                << spaced_inserter
                << utility_.quote(utility_.quote_escaped("value") + colon)
                << ";" << std::endl;
        utility_.blank_line();

        stream_ << indenter_ << "std::string attr;" << std::endl;
        stream_ << indenter_ << "switch (v) ";
        utility_.open_scope();
        {
            for (const auto e : ei.enumerators()) {
                stream_ << indenter_ << "case " << ei.name()
                        << "::" << e.name() << ":"
                        << std::endl;
                {
                    positive_indenter_scope s(indenter_);
                    stream_ << indenter_ << "attr = "
                            << utility_.quote(utility_.quote_escaped(e.name()))
                            << semi_colon
                            << std::endl
                            << indenter_ << "break;" << std::endl;
                }
            }
            stream_ << indenter_ << "default:" << std::endl;
            {
                positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "throw std::invalid_argument("
                        << "\"Invalid value for " << ei.name() << "\");"
                        << std::endl;
            }
            utility_.close_scope();
        }
        stream_ << indenter_ << "s" << spaced_inserter
                << "attr"
                << spaced_inserter << utility_.quote(" }")
                << semi_colon
                << std::endl
                << indenter_ << "return s;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void io_implementation::format_class(const cpp::file_info& fi) {
    const auto o(fi.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    const cpp::class_info& ci(*o);
    io_helper_methods(ci);

    namespace_helper ns_helper(stream_, ci.namespaces());
    utility_.blank_line();

    stream_ << "std::ostream& operator<<(std::ostream& s, ";
    {
        positive_indenter_scope s(indenter_);
        const auto parents(ci.parents());
        const bool no_arg(!ci.is_parent() && parents.empty() &&
            ci.properties().empty());
        stream_ << "const " << ci.name() << "&" << (no_arg ? ") " : " v) ");
        utility_.open_scope();

        if (ci.is_parent() || !parents.empty()) {
            stream_ << indenter_ << "v.to_stream(s);" << std::endl
                    << indenter_ << "return(s);" << std::endl;
        } else {
            const bool inside_class(false);
            inserter_implementation i(stream_, indenter_, inside_class);
            i.format_inserter_implementation(ci);
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void io_implementation::format(const cpp::file_info& fi) {
    licence licence(stream_);
    licence.format();

    includes includes(stream_);
    includes.format(fi);

    using cpp::content_types;
    if (fi.descriptor().content_type() == content_types::unversioned_key ||
        fi.descriptor().content_type() == content_types::versioned_key ||
        fi.descriptor().content_type() == content_types::value_object ||
        fi.descriptor().content_type() == content_types::entity ||
        fi.descriptor().content_type() == content_types::keyed_entity)
        format_class(fi);
    else if (fi.descriptor().content_type() == content_types::enumeration)
        format_enumeration(fi);
}

} }
