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
#include "dogen/cpp/types/generation_failure.hpp"
#include "dogen/cpp/types/formatters/inserter_implementation.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/cpp/types/formatters/utility.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/io_implementation.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.io_implementation"));

const std::string ostream("ostream");
const std::string spaced_inserter(" << ");
const std::string type("__type__");
const std::string colon(": ");
const std::string comma(", ");
const std::string semi_colon(";");

const std::string missing_class_view_model(
    "Meta type is pod but class view model is empty");
const std::string missing_enumeration_view_model(
    "Meta type is enumeration but enumeration view model is empty");

}

namespace dogen {
namespace cpp {
namespace formatters {

io_implementation::
io_implementation(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) { }

file_formatter::shared_ptr io_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new io_implementation(stream));
}

void io_implementation::io_helper_methods(const class_view_model& vm) {
    if (vm.is_parent() || !vm.parents().empty())
        return;

    const bool inside_class(false);
    inserter_implementation i(stream_, indenter_, inside_class);
    i.format_helper_methods(vm);
}

void io_implementation::format_enumeration(const file_view_model& vm) {
    const auto o(vm.enumeration_vm());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enumeration_view_model;
        BOOST_THROW_EXCEPTION(generation_failure(missing_enumeration_view_model));
    }

    const auto evm(*o);
    namespace_helper ns_helper(stream_, evm.namespaces());
    utility_.blank_line();

    stream_ << "std::ostream& operator<<(std::ostream& s, "
            << "const " << evm.name() << "& v) ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "s" << spaced_inserter
                << utility_.quote("{ ") << spaced_inserter
                << utility_.quote(utility_.quote_escaped(type) + colon);

        stream_ << spaced_inserter
                << utility_.quote(utility_.quote_escaped(evm.name()) + comma)
                << spaced_inserter
                << utility_.quote(utility_.quote_escaped("value") + colon)
                << ";" << std::endl;
        utility_.blank_line();

        stream_ << indenter_ << "std::string attr;" << std::endl;
        stream_ << indenter_ << "switch (v) ";
        utility_.open_scope();
        {
            for (const auto e : evm.enumerators()) {
                stream_ << indenter_ << "case " << evm.name()
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
                        << "\"Invalid value for " << evm.name() << "\");"
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

void io_implementation::format_class(const file_view_model& vm) {
    const auto o(vm.class_vm());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_view_model;
        BOOST_THROW_EXCEPTION(generation_failure(missing_class_view_model));
    }

    const view_models::class_view_model& cvm(*o);
    io_helper_methods(cvm);

    namespace_helper ns_helper(stream_, cvm.namespaces());
    utility_.blank_line();

    stream_ << "std::ostream& operator<<(std::ostream& s, ";
    {
        positive_indenter_scope s(indenter_);
        const auto parents(cvm.parents());
        const bool no_arg(!cvm.is_parent() && parents.empty() &&
            cvm.properties().empty());
        stream_ << "const " << cvm.name() << "&" << (no_arg ? ") " : " v) ");
        utility_.open_scope();

        if (cvm.is_parent() || !parents.empty()) {
            stream_ << indenter_ << "v.to_stream(s);" << std::endl
                    << indenter_ << "return(s);" << std::endl;
        } else {
            const bool inside_class(false);
            inserter_implementation i(stream_, indenter_, inside_class);
            i.format_inserter_implementation(cvm);
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void io_implementation::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration)
        format_enumeration(vm);
    else if (vm.meta_type() == sml::meta_types::pod)
        format_class(vm);
}

} } }
