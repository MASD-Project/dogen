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
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/enum_declaration.hpp"
#include "dogen/cpp_formatters/types/exception_declaration.hpp"
#include "dogen/cpp_formatters/types/class_declaration.hpp"
#include "dogen/cpp_formatters/types/types_main_header_file_formatter.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.types_main_header_file_formatter"));

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
const std::string invalid_aspect_type("Invalid value for aspect_types");
const std::string invalid_category_type("Invalid value for category_types");
const std::string missing_entity("Entity is empty");

}

namespace dogen {
namespace cpp_formatters {

types_main_header_file_formatter::
types_main_header_file_formatter(std::ostream& stream,
    const bool disable_complete_constructor,
    const bool use_integrated_io, const bool disable_io,
    const bool disable_serialization) :
    stream_(stream),
    utility_(stream_, indenter_),
    disable_complete_constructor_(disable_complete_constructor),
    use_integrated_io_(use_integrated_io),
    disable_io_(disable_io), disable_serialization_(disable_serialization) { }

file_formatter::shared_ptr types_main_header_file_formatter::
create(std::ostream& stream, const bool disable_complete_constructor,
    const bool use_integrated_io, const bool disable_io,
    const bool disable_serialization) {
    return file_formatter::shared_ptr(new types_main_header_file_formatter(stream,
            disable_complete_constructor, use_integrated_io, disable_io,
            disable_serialization));
}

void types_main_header_file_formatter::
equality_operator(const cpp::formattables::class_info& ci) {
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

void types_main_header_file_formatter::
inserter_operator(const cpp::formattables::class_info& ci) {
    if (!use_integrated_io_ || disable_io_)
        return;

    stream_ << indenter_ << "std::ostream& operator<<(std::ostream& s, "
            << "const " << ci.name() << "& v);" << std::endl;
    utility_.blank_line();
}

void types_main_header_file_formatter::
swap_method(const cpp::formattables::class_info& ci) {
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

void types_main_header_file_formatter::visit(
    cpp::formattables::class_info& ci) {
    {
        namespace_helper ns(stream_, ci.namespaces());
        utility_.blank_line();

        cpp_formatters::class_declaration f(stream_, disable_serialization_,
            disable_complete_constructor_, disable_io_);
        f.format(ci);

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

void types_main_header_file_formatter::visit(cpp::formattables::enum_info& ei) {
    {
        namespace_helper ns(stream_, ei.namespaces());
        utility_.blank_line();
        enum_declaration f(stream_);
        f.format(ei);
    }
    utility_.blank_line(2);
}

void types_main_header_file_formatter::
visit(cpp::formattables::exception_info& ei) {
    {
        namespace_helper ns(stream_, ei.namespaces());
        utility_.blank_line();
        exception_declaration f(stream_);
        f.format(ei);
    }
    utility_.blank_line(2);
}

void types_main_header_file_formatter::format(
    const cpp::formattables::file_info& f) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(f.header_guard());
    utility_.blank_line();

    includes includes(stream_);
    includes.format(f);

    if (!f.formattable()) {
        BOOST_LOG_SEV(lg, error) << missing_entity;
        BOOST_THROW_EXCEPTION(formatting_error(missing_entity));
    }

    f.formattable()->accept(*this);

    guards.format_end();
}

} }
