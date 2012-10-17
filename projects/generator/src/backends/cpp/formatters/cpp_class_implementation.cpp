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
#include "dogen/generator/backends/cpp/formatters/cpp_class_implementation.hpp"

namespace {

// FIXME: until we add support to indenter.
const std::string special_indent("       ");
const std::string jsonify_using("using dogen::utility::streaming::jsonify;");
const std::string type("__type__");
const std::string inserter("<< ");
const std::string space_inserter(" << ");
const std::string open_bracket(" {");
const std::string close_bracket(" }");
const std::string colon(": ");
const std::string semi_colon(";");
const std::string space(" ");
const std::string comma(",");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_class_implementation::cpp_class_implementation(std::ostream& stream)
    : stream_(stream), utility_(stream_, indenter_) { }

void cpp_class_implementation::default_constructor(const class_view_model& vm) {
    if (!vm.has_primitive_properties())
        return;

    stream_ << indenter_ << vm.name() << "::"
            << vm.name() << "()" << std::endl;
    {
        cpp_positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto p : vm.properties()) {
            if (!p.is_primitive())
                continue;

            if (is_first)
                stream_ << indenter_ << ": ";
            else
                stream_ << "," << std::endl << indenter_ << "  ";

            stream_ << utility_.as_member_variable(p.name()) << "("
                    << "static_cast<" << p.type() << ">(0))";
            is_first = false;
        }
        stream_ << " { }" << std::endl;
    }
    utility_.blank_line();
}

void cpp_class_implementation::complete_constructor(const class_view_model& vm) {
    const auto props(vm.properties());
    if (props.empty())
        return;

    stream_ << indenter_ << vm.name() << "::" << vm.name() << "(";

    if (props.size() == 1) {
        const auto p(*props.begin());
        stream_ << p.type() << " " << p.name() << ")" << std::endl;
    } else {
        cpp_positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto p : props) {
            stream_ << (is_first ? "" : ",") << std::endl;
            stream_ << indenter_ << p.type() << " " << p.name();
            is_first = false;
        }
        stream_ << ")" << std::endl;
    }

    {
        cpp_positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto p : props) {
            if (is_first)
                stream_ << indenter_ << ": ";
            else
                stream_ << "," << std::endl << indenter_ << "  ";

            stream_ << utility_.as_member_variable(p.name()) << "("
                    << p.name() << ")";
            is_first = false;
        }
        stream_ << " { }" << std::endl;
    }
    utility_.blank_line();
}

void cpp_class_implementation::to_stream(const class_view_model& vm) {
    stream_ << "void " << vm.name()
            << "::to_stream(std::ostream& stream) const ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);

        if (vm.requires_stream_manipulators()) {
            stream_ << indenter_ << "boost::io::ios_flags_saver ifs(stream);"
                    << std::endl;
            stream_ << indenter_ << "stream << std::boolalpha;" << std::endl;
            utility_.blank_line();
        }

        stream_ << indenter_ << jsonify_using << std::endl;
        utility_.blank_line();

        stream_ << indenter_ << "stream " << inserter
                << utility_.quote(open_bracket)
                << std::endl;

        stream_ << indenter_ << special_indent << inserter
                << utility_.quote(utility_.quote_escaped(type) + colon)
                << space_inserter
                << utility_.quote(utility_.quote_escaped(vm.name()));

        for (const auto p : vm.properties()) {
            stream_ << space_inserter << utility_.quote(comma) << std::endl;

            stream_ << indenter_ << special_indent << inserter
                    << utility_.quote(utility_.quote_escaped(p.name())
                        + colon) << space_inserter
                    << "jsonify(" << utility_.as_member_variable(p.name())
                    << ")";
        }
        stream_ << std::endl;
        stream_ << indenter_ << special_indent << inserter
                << utility_.quote(close_bracket) << semi_colon << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void cpp_class_implementation::swap(const class_view_model& vm) {
    if (vm.properties().empty())
        return;

    stream_ << indenter_ << "void " << vm.name() << "::swap("
            << vm.name() << "& other) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        for (const auto p : vm.properties()) {
            stream_ << indenter_ << "std::swap("
                    << utility_.as_member_variable(p.name())
                    << ", other."
                    << utility_.as_member_variable(p.name())
                    << ");" << std::endl;
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void cpp_class_implementation::equals_operator(const class_view_model& vm) {
    stream_ << indenter_ << "bool " << vm.name() << "::operator==(const "
            << vm.name() <<  "& ";

    if (vm.properties().empty())
        stream_ << "/*rhs*/";
    else
        stream_ << "rhs";

    stream_ << ") const ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        if (vm.properties().empty())
            stream_ << indenter_ << "return true";
        else {
            stream_ << indenter_ << "return ";
            bool is_first(true);
            {
                cpp_positive_indenter_scope s(indenter_);
                for (const auto p : vm.properties()) {
                    if (!is_first)
                        stream_ << " &&" << std::endl << indenter_;
                    {
                        cpp_positive_indenter_scope s(indenter_);
                        stream_ << utility_.as_member_variable(p.name())
                                << " == rhs."
                                << utility_.as_member_variable(p.name());
                    }
                    is_first = false;
                }
            }
        }
        stream_ << ";" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void cpp_class_implementation::
assignment_operator(const class_view_model& vm) {
    if (vm.properties().empty())
        return;

    stream_ << indenter_ << vm.name() << "& "
            << vm.name() << "::operator=(" << vm.name()
            << " other) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::swap(*this, other);"
                << std::endl
                << indenter_ << "return *this;"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

} } } } }
