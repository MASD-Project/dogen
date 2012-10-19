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
#include "dogen/generator/backends/cpp/formatters/cpp_inserter_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_class_implementation.hpp"

namespace {

// FIXME: until we add support to indenter.
const std::string special_indent("       ");
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
    const auto props(vm.all_properties());
    if (props.empty())
        return;

    stream_ << indenter_ << vm.name() << "::" << vm.name() << "(";

    if (props.size() == 1) {
        const auto p(*props.begin());
        stream_ << "const " << p.type();

        if (!p.is_primitive())
            stream_ << "&";

        stream_ << " " << p.name() << ")" << std::endl;
    } else {
        cpp_positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto p : props) {
            stream_ << (is_first ? "" : ",") << std::endl;
            stream_ << indenter_ << "const " << p.type();

            if (!p.is_primitive())
                stream_ << "&";

            stream_ << " " << p.name();
            is_first = false;
        }
        stream_ << ")" << std::endl;
    }

    {
        cpp_positive_indenter_scope s(indenter_);
        bool is_first(true);
        stream_ << indenter_ << ": ";

        for (const auto p : vm.parents()) {
            stream_ << p.name() << "(";
            for (const auto prop : p.properties()) {
                if (!is_first)
                    stream_ << "," << std::endl << indenter_ << "  ";

                stream_ << prop.name();
                is_first = false;
            }
            stream_ << ")";
        }

        for (const auto p : vm.properties()) {
            if (!is_first)
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
    if (!vm.is_parent() && vm.parents().empty())
        return;

    stream_ << "std::ostream& " << vm.name()
            << "::to_stream(std::ostream& stream) const ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);

        const bool inside_class(true);
        cpp_inserter_implementation inserter(stream_, indenter_, inside_class);
        inserter.format(vm);
    }
    utility_.close_scope();
    utility_.blank_line();
}

void cpp_class_implementation::swap(const class_view_model& vm) {
    if (vm.all_properties().empty())
        return;

    stream_ << indenter_ << "void " << vm.name() << "::swap("
            << vm.name() << "& other) noexcept ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        const auto parents(vm.parents());
        for (const auto p : parents)
            stream_ << indenter_ << p.name() << "::swap(other);" << std::endl;

        if (!parents.empty())
            utility_.blank_line();

        const auto props(vm.properties());
        if (!props.empty()) {
            stream_ << indenter_ << "using std::swap;" << std::endl;
            for (const auto p : props) {
                stream_ << indenter_ << "swap("
                        << utility_.as_member_variable(p.name())
                        << ", other."
                        << utility_.as_member_variable(p.name())
                        << ");" << std::endl;
            }
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void cpp_class_implementation::equals_operator(const class_view_model& vm) {
    stream_ << indenter_ << "bool " << vm.name() << "::operator==(const "
            << vm.name() <<  "& ";

    if (vm.all_properties().empty())
        stream_ << "/*rhs*/";
    else
        stream_ << "rhs";

    stream_ << ") const ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        if (vm.all_properties().empty())
            stream_ << indenter_ << "return true";
        else {
            stream_ << indenter_ << "return ";
            bool is_first(true);
            {
                cpp_positive_indenter_scope s(indenter_);
                const auto parents(vm.parents());
                for (const auto p : parents) {
                    if (!is_first)
                        stream_ << " &&" << std::endl << indenter_;
                    {
                        cpp_positive_indenter_scope s(indenter_);
                        stream_ << indenter_ << p.name() << "::operator==(rhs)"
                                << std::endl;
                    }
                    is_first = false;
                }

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
    // assignment is only available in leaf classes - MEC++-33
    if (vm.all_properties().empty() || vm.is_parent())
        return;

    stream_ << indenter_ << vm.name() << "& "
            << vm.name() << "::operator=(" << vm.name()
            << " other) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "using std::swap;" << std::endl;
        stream_ << indenter_ << "swap(*this, other);"
                << std::endl
                << indenter_ << "return *this;"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

} } } } }
