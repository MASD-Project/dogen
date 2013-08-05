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
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/forward_declarations_header.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.forward_declarations_header"));

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
const std::string invalid_aspect_type("Invalid value for aspect_types");
const std::string invalid_category_type("Invalid value for category_types");

const std::string invalid_facet_types("Invalid value for facet_types");
const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");
const std::string missing_exception_info("Exception info is empty");

}

namespace dogen {
namespace cpp_formatters {

forward_declarations_header::
forward_declarations_header(std::ostream& stream)
    : stream_(stream), utility_(stream_, indenter_) { }

file_formatter::shared_ptr forward_declarations_header::
create(std::ostream& stream) {
    return file_formatter::shared_ptr(new forward_declarations_header(stream));
}

void forward_declarations_header::
format_serialization_class(const cpp::class_info& ci) {
    {
        std::list<std::string> ns({ boost_ns, serialization_ns });
        namespace_helper nsh(stream_, ns);
        utility_.blank_line();

        stream_ << indenter_ << "template<class Archive>" << std::endl
            << indenter_ << "void save(Archive& ar, const ";

        qname qname(stream_);
        qname.format(ci);

        stream_ << indenter_ << "& v, unsigned int version);" << std::endl;
        utility_.blank_line();

        stream_ << indenter_ << "template<class Archive>" << std::endl
                << indenter_ << "void load(Archive& ar, ";
        qname.format(ci);

        stream_ << indenter_ << "& v, unsigned int version);" << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void forward_declarations_header::
format_domain_class(const cpp::class_info& ci) {
    {
        namespace_helper nsh(stream_, ci.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "class " << ci.name() << ";" << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void forward_declarations_header::format_class(const cpp::file_info& fi) {
    boost::optional<cpp::class_info> o(fi.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    const auto ft(fi.descriptor().facet_type());
    const cpp::class_info& ci(*o);
    if (ft == config::cpp_facet_types::serialization)
        format_serialization_class(ci);
    else if (ft == config::cpp_facet_types::types)
        format_domain_class(ci);
    else {
        using dogen::utility::exception::invalid_enum_value;
        BOOST_LOG_SEV(lg, error) << invalid_facet_types;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_facet_types));
    }
}

void forward_declarations_header::
format_enumeration(const cpp::file_info& fi) {
    const auto o(fi.enum_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enum_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enum_info));
    }

    const auto ei(*o);
    {
        namespace_helper nsh(stream_, ei.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "enum class " << ei.name()
                << " : unsigned int;";
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void forward_declarations_header::format_exception(const cpp::file_info& fi) {
    const auto o(fi.exception_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_exception_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_exception_info));
    }

    const auto ei(*o);
    {
        namespace_helper nsh(stream_, ei.namespaces());
        utility_.blank_line();

        stream_ << indenter_ << "class " << ei.name() << ";" << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void forward_declarations_header::format(const cpp::file_info& fi) {
    using cpp::aspect_types;
    if (fi.descriptor().aspect_type() != aspect_types::forward_decls) {
        using dogen::utility::exception::invalid_enum_value;
        BOOST_LOG_SEV(lg, error) << invalid_facet_types;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_facet_types));
    }

    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(fi.header_guard());
    utility_.blank_line();

    includes includes(stream_);
    includes.format(fi);

    using cpp::content_types;
    if (fi.descriptor().content_type() == content_types::unversioned_key ||
        fi.descriptor().content_type() == content_types::versioned_key ||
        fi.descriptor().content_type() == content_types::user_defined_service ||
        fi.descriptor().content_type() == content_types::value_object ||
        fi.descriptor().content_type() == content_types::entity ||
        fi.descriptor().content_type() == content_types::keyed_entity)
        format_class(fi);
    else if (fi.descriptor().content_type() == content_types::enumeration)
        format_enumeration(fi);
    else if (fi.descriptor().content_type() == content_types::exception)
        format_exception(fi);

    guards.format_end();
}

} }
