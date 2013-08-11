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
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/generator_header.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.generator_header"));

const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");

}

namespace dogen {
namespace cpp_formatters {

generator_header::
generator_header(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr generator_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new generator_header(stream));
}

void generator_header::generator_class(const cpp::enum_info& ei) {
    const std::string class_name(ei.name() + "_generator");

    stream_ << indenter_ << "class " << class_name << " ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        utility_.public_access_specifier();
        stream_ << indenter_ << class_name << "();" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();

        stream_ << indenter_ << "typedef ";
        qname qname(stream_);
        qname.format(ei);
        stream_ << " result_type;" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();
        stream_ << indenter_
                << "static void populate(const unsigned int position,"
                <<" result_type& v);"
                << std::endl;

        stream_ << indenter_
                << "static result_type create(const unsigned int position);"
                << std::endl;

        stream_ << indenter_ << "result_type operator()();" << std::endl;
        utility_.blank_line();

        utility_.private_access_specifier();
        stream_ << indenter_ << "unsigned int "
                << utility_.as_member_variable("position") << ";"
                << std::endl;
    }
    stream_ << "};";
}

void generator_header::generator_class(const cpp::class_info& ci) {
    const std::string class_name(ci.name() + "_generator");

    stream_ << indenter_ << "class " << class_name << " ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        utility_.public_access_specifier();
        stream_ << indenter_ << class_name << "();" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();

        stream_ << indenter_ << "typedef ";
        qname qname(stream_);
        qname.format(ci);
        stream_ << " result_type;" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();
        if (!ci.is_immutable()) {
            stream_ << indenter_
                    << "static void populate(const unsigned int position,"
                    <<" result_type& v);"
                    << std::endl;
        }

        if (!ci.is_parent()) {
            stream_ << indenter_
                    << "static result_type create(const unsigned int position);"
                    << std::endl;

            stream_ << indenter_ << "result_type operator()();" << std::endl;
            utility_.blank_line();

            utility_.private_access_specifier();
            stream_ << indenter_ << "unsigned int "
                    << utility_.as_member_variable("position") << ";"
                    << std::endl;
        }

        utility_.public_access_specifier();
        stream_ << indenter_
                << "static result_type* create_ptr("
                << "const unsigned int position);"
                << std::endl;
    }
    stream_ << "};";
}

void generator_header::format_enumeration(const cpp::source_file& f) {
    const auto o(f.enum_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enum_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enum_info));
    }

    const auto ei(*o);
    {
        std::list<std::string> namespaces(ei.namespaces());
        namespace_helper ns_helper(stream_, namespaces);
        utility_.blank_line();

        generator_class(ei);
        utility_.blank_line(2);
    }
    utility_.blank_line(2);
}

void generator_header::format_class(const cpp::source_file& f) {
    auto o(f.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    {
        const cpp::class_info& ci(*o);
        std::list<std::string> namespaces(ci.namespaces());
        namespace_helper ns_helper(stream_, namespaces);
        utility_.blank_line();

        generator_class(ci);
        utility_.blank_line(2);
    }
    utility_.blank_line(2);
}

void generator_header::format(const cpp::source_file& f) {
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
