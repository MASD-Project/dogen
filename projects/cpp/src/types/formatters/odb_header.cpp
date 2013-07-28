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
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/odb_header.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.odb_header"));

const std::string std_ns("std");
const std::string odb_pragma("#pragma db");
const std::string odb_key("ODB_PRAGMA");

const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");

}

namespace dogen {
namespace cpp {
namespace formatters {

odb_header::
odb_header(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr odb_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new odb_header(stream));
}

void odb_header::format_enumeration(const file_info& fi) {
    const auto o(fi.enum_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enum_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enum_info));
    }

    const auto ei(*o);
    {
        namespace_helper ns(stream_, ei.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "#ifdef ODB_COMPILER" << std::endl;
        utility_.blank_line();
        stream_ << indenter_ << "#endif" << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void odb_header::format_class(const file_info& fi) {
    const auto o(fi.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    const auto ei(*o);
    {
        if (ei.implementation_specific_parameters().empty()) {
            stream_ << indenter_ << "// class has no ODB pragmas defined."
                    << std::endl;
            utility_.blank_line();
            return;
        }

        std::ostringstream odb_stream;
        bool has_odb_parms(false);
        odb_stream << indenter_ << "#ifdef ODB_COMPILER" << std::endl
                   << std::endl;

        for (const auto kvp : ei.implementation_specific_parameters()) {
            if (kvp.first == odb_key) {
                has_odb_parms = true;
                odb_stream << indenter_
                           << odb_pragma << " object(" << ei.name() << ") "
                           << kvp.second << std::endl;
            }
        }

        odb_stream << std::endl;
        for (const auto p : ei.properties()) {
            for (const auto kvp : p.implementation_specific_parameters()) {
                if (kvp.first == odb_key) {
                    has_odb_parms = true;
                    odb_stream << indenter_
                               << odb_pragma << " member(" << ei.name() << "::"
                               << utility_.as_member_variable(p.name()) << ") "
                               << kvp.second << std::endl;
                }
            }
        }
        odb_stream << std::endl
                   << indenter_ << "#endif" << std::endl
                   << std::endl;

        if (!has_odb_parms) {
            stream_ << indenter_ << "// class has no ODB pragmas defined."
                    << std::endl;
            utility_.blank_line();
            return;
        }

        {
            namespace_helper ns(stream_, ei.namespaces());
            utility_.blank_line();
            stream_ << odb_stream.str();
        }
        utility_.blank_line(2);
    }
}

void odb_header::format(const file_info& fi) {
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
