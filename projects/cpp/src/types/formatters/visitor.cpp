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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/cpp/types/formatters/doxygen_comments.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/qname.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/cpp/types/formatters/visitor.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.visitor"));
const std::string missing_visitor_view_model("Visitor view model is empty");
const std::string comments("Accept visits for type ");

}

namespace dogen {
namespace cpp {
namespace formatters {

visitor::visitor(std::ostream& stream)
    : stream_(stream), utility_(stream_, indenter_) { }

file_formatter::shared_ptr visitor::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new visitor(stream));
}

void visitor::format(const visitor_view_model& vm) {
    doxygen_comments dc(stream_, indenter_);
    dc.format(vm.documentation());
    stream_ << indenter_ << "class " << vm.name() << " {" << std::endl;
    utility_.public_access_specifier();
    {
        positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto& t : vm.types()) {
            if (!is_first)
                utility_.blank_line();

            dc.format(comments + t);
            dc.format_start_block(comments);

            stream_ << indenter_ << "virtual void visit(const " << t
                    << "&) const { }"
                    << std::endl;
            stream_ << indenter_ << "virtual void visit(const " << t
                    << "&) { }"
                    << std::endl;
            stream_ << indenter_ << "virtual void visit(" << t
                    << "&) const { }"
                    << std::endl;
            stream_ << indenter_ << "virtual void visit(" << t
                    << "&) { }"
                    << std::endl;

            dc.format_end_block(comments);
            is_first = false;
        }
    }

    stream_ << indenter_ << "};" << std::endl;
    utility_.blank_line();
}

void visitor::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

    includes includes(stream_);
    includes.format(vm);

    const auto o(vm.visitor_vm());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_visitor_view_model;
        BOOST_THROW_EXCEPTION(formatting_error(missing_visitor_view_model));
    }
    format(*o);

    guards.format_end();
}

} } }
