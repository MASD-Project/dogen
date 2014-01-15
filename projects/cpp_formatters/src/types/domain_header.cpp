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
#include "dogen/cpp_formatters/types//formatting_error.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/enum_declaration.hpp"
#include "dogen/cpp_formatters/types/exception_declaration.hpp"
#include "dogen/cpp_formatters/types/class_declaration.hpp"
#include "dogen/cpp_formatters/types/domain_header.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.domain_header"));

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
const std::string invalid_aspect_type("Invalid value for aspect_types");
const std::string invalid_category_type("Invalid value for category_types");
const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");
const std::string missing_exception_info("Exception info is empty");

}

namespace dogen {
namespace cpp_formatters {

domain_header::
domain_header(std::ostream& stream, const bool disable_complete_constructor,
    const bool use_integrated_io, const bool disable_io,
    const bool disable_serialization) :
    stream_(stream),
    utility_(stream_, indenter_),
    disable_complete_constructor_(disable_complete_constructor),
    use_integrated_io_(use_integrated_io),
    disable_io_(disable_io), disable_serialization_(disable_serialization) { }

file_formatter::shared_ptr domain_header::
create(std::ostream& stream, const bool disable_complete_constructor,
    const bool use_integrated_io, const bool disable_io,
    const bool disable_serialization) {
    return file_formatter::shared_ptr(new domain_header(stream,
            disable_complete_constructor, use_integrated_io, disable_io,
            disable_serialization));
}

void domain_header::
equality_operator(const cpp::class_info& ci) {
    if (!ci.is_parent())
        return;

    stream_ << indenter_ << "inline bool operator==(const "
            << ci.name() << "& lhs, const " << ci.name() << "& rhs) ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "return lhs.equals(rhs);" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void domain_header::
inserter_operator(const cpp::class_info& ci) {
    if (!use_integrated_io_ || disable_io_)
        return;

    stream_ << indenter_ << "std::ostream& operator<<(std::ostream& s, "
            << "const " << ci.name() << "& v);" << std::endl;
    utility_.blank_line();
}

void domain_header::
swap_method(const cpp::class_info& ci) {
    // swap overload is only available in leaf classes - MEC++-33
    if (ci.all_properties().empty() || ci.is_parent() || ci.is_immutable())
        return;

    namespace_helper ns(stream_, std::list<std::string> { "std" });
    utility_.blank_line();

    stream_ << indenter_ << "template<>" << std::endl
            << indenter_ << "inline void swap(" << std::endl;

    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_;
        qname qname(stream_);
        qname.format(ci);
        stream_ << "& lhs," << std::endl;

        stream_ << indenter_;
        qname.format(ci);
        stream_ << "& rhs) ";

        utility_.open_scope();
        stream_ << indenter_ << "lhs.swap(rhs);" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void domain_header::class_declaration(const cpp::content_descriptor& cd,
    const cpp::class_info& ci) {
    using dogen::utility::exception::invalid_enum_value;
    using cpp::content_types;
    const auto ct(cd.content_type());
    if (ct == content_types::versioned_key ||
        ct == content_types::unversioned_key ||
        ct == content_types::value_object) {

        cpp_formatters::class_declaration f(stream_, disable_serialization_,
            disable_complete_constructor_, disable_io_);
        f.format(ci);
        return;
    }

    BOOST_LOG_SEV(lg, error) << invalid_category_type;
    BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_category_type));
}

void domain_header::
format_main(const cpp::content_descriptor& cd, const cpp::class_info& ci) {

    {
        namespace_helper ns(stream_, ci.namespaces());
        utility_.blank_line();
        class_declaration(cd, ci);

        if (ci.is_parent()) {
            stream_ << indenter_ << "inline " << ci.name() << "::~"<< ci.name()
                    << "() noexcept { }" << std::endl;
            utility_.blank_line();
        }

        inserter_operator(ci);
        equality_operator(ci);
    }
    utility_.blank_line(2);

    swap_method(ci);
    if (!ci.all_properties().empty())
        utility_.blank_line(2);
}

void domain_header::format_class(const cpp::source_file& f) {
    boost::optional<cpp::class_info> o(f.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }
    const auto at(f.descriptor().aspect_type());
    const cpp::class_info& ci(*o);
    if (at == cpp::aspect_types::main)
        format_main(f.descriptor(), ci);
    else {
        using dogen::utility::exception::invalid_enum_value;
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_aspect_type));
    }
}

void domain_header::format_enumeration(const cpp::source_file& f) {
    const auto o(f.enum_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enum_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enum_info));
    }
    {
        const auto ei(*o);
        namespace_helper ns(stream_, ei.namespaces());
        utility_.blank_line();
        enum_declaration f(stream_);
        f.format(ei);
    }
    utility_.blank_line(2);
}

void domain_header::format_exception(const cpp::source_file& f) {
    const auto o(f.exception_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enum_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_exception_info));
    }
    {
        const auto ei(*o);
        namespace_helper ns(stream_, ei.namespaces());
        utility_.blank_line();
        exception_declaration f(stream_);
        f.format(ei);
    }
    utility_.blank_line(2);
}

void domain_header::format(const cpp::source_file& f) {
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
    else if (f.descriptor().content_type() == content_types::exception)
        format_exception(f);

    guards.format_end();
}

} }
