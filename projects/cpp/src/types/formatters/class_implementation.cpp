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
#include "dogen/cpp/types/formatters/qualified_name.hpp"
#include "dogen/cpp/types/formatters/inserter_implementation.hpp"
#include "dogen/cpp/types/formatters/class_implementation.hpp"

namespace {

// FIXME: until we add support to indenter.
const std::string special_indent("       ");
const std::string space(" ");

}

namespace dogen {
namespace cpp {
namespace formatters {

class_implementation::class_implementation(std::ostream& stream)
    : stream_(stream), utility_(stream_, indenter_) { }

void class_implementation::default_constructor(const class_view_model& vm) {
    if (!vm.requires_manual_default_constructor())
        return;

    stream_ << indenter_ << vm.name() << "::"
            << vm.name() << "()" << std::endl;
    {
        positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto p : vm.properties()) {
            if (!p.type().is_primitive() && !p.type().is_enumeration())
                continue;

            if (is_first)
                stream_ << indenter_ << ": ";
            else
                stream_ << "," << std::endl << indenter_ << "  ";

            stream_ << utility_.as_member_variable(p.name()) << "("
                    << "static_cast<" << p.type().complete_name() << ">(0))";
            is_first = false;
        }
        stream_ << " { }" << std::endl;
    }
    utility_.blank_line();
}

void class_implementation::move_constructor(const class_view_model& vm) {
    if (!vm.requires_manual_move_constructor())
        return;

    stream_ << indenter_ << vm.name() << "::" << vm.name()
            << "(" << vm.name() << "&& rhs)" << std::endl;
    {
        positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto p : vm.properties()) {
            if (is_first)
                stream_ << indenter_ << ": ";
            else
                stream_ << "," << std::endl << indenter_ << "  ";

            stream_ << utility_.as_member_variable(p.name()) << "("
                    << "std::move(rhs." << utility_.as_member_variable(p.name())
                    << "))";
            is_first = false;
        }
        stream_ << " { }" << std::endl;
    }
    utility_.blank_line();
}

void class_implementation::complete_constructor(const class_view_model& vm) {
    const auto props(vm.all_properties());
    if (props.empty())
        return;

    stream_ << indenter_ << vm.name() << "::" << vm.name() << "(";

    if (props.size() == 1) {
        const auto p(*props.begin());
        stream_ << "const " << p.type().complete_name();

        if (!p.type().is_primitive())
            stream_ << "&";

        stream_ << " " << p.name() << ")" << std::endl;
    } else {
        positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto p : props) {
            stream_ << (is_first ? "" : ",") << std::endl;
            stream_ << indenter_ << "const " << p.type().complete_name();

            if (!p.type().is_primitive())
                stream_ << "&";

            stream_ << " " << p.name();
            is_first = false;
        }
        stream_ << ")" << std::endl;
    }

    {
        positive_indenter_scope s(indenter_);
        bool is_first(true);
        stream_ << indenter_ << ": ";

        for (const auto p : vm.parents()) {
            qualified_name qualified_name(stream_);
            qualified_name.format(p);

            stream_ << "(";
            for (const auto prop : p.properties()) {
                if (!is_first)
                    stream_ << "," << std::endl << indenter_ << "  ";

                stream_ << prop.name();
                is_first = false;
            }
            stream_ << ")";
            is_first = false;
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

void class_implementation::to_stream(const class_view_model& vm) {
    if (!vm.is_parent() && vm.parents().empty())
        return;

    stream_ << "void " << vm.name()
            << "::to_stream(std::ostream& s) const ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        const bool inside_class(true);
        inserter_implementation inserter(stream_, indenter_, inside_class);
        inserter.format_inserter_implementation(vm);
    }
    utility_.close_scope();
    utility_.blank_line();
}

void class_implementation::swap(const class_view_model& vm) {
    if (vm.all_properties().empty() && !vm.is_parent())
        return;

    const bool empty(vm.all_properties().empty() && vm.parents().empty());
    stream_ << indenter_ << "void " << vm.name() << "::swap("
            << vm.name() << "&" << (empty ? "" : " other")
            <<") noexcept ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
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

void class_implementation::equals_method(const class_view_model& vm) {
    if (vm.is_parent() || vm.parents().empty())
        return;

    stream_ << indenter_ << "bool " << vm.name() << "::equals(const "
            << vm.original_parent_name() << "& other) const ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "const " << vm.name()
                << "* const p(dynamic_cast<const " << vm.name()
                << "* const>(&other));"
                << std::endl;
        stream_ << indenter_ << "if (!p) return false;"
                << std::endl;
        stream_ << indenter_ << "return *this == *p;"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void class_implementation::equals_operator(const class_view_model& vm) {
    if (vm.is_parent()) {
        stream_ << indenter_ << "bool " << vm.name() << "::compare(const "
                << vm.name() <<  "& ";
    } else {
        stream_ << indenter_ << "bool " << vm.name() << "::operator==(const "
                << vm.name() <<  "& ";
    }

    if (vm.all_properties().empty())
        stream_ << "/*rhs*/";
    else
        stream_ << "rhs";

    stream_ << ") const ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        if (vm.all_properties().empty())
            stream_ << indenter_ << "return true";
        else {
            stream_ << indenter_ << "return ";
            bool is_first(true);
            {
                positive_indenter_scope s(indenter_);
                const auto parents(vm.parents());
                for (const auto p : parents) {
                    if (!is_first)
                        stream_ << " &&" << std::endl << indenter_;
                    {
                        positive_indenter_scope s(indenter_);
                        stream_ << p.name() << "::compare(rhs)";
                    }
                    is_first = false;
                }

                for (const auto p : vm.properties()) {
                    if (!is_first)
                        stream_ << " &&" << std::endl << indenter_;
                    {
                        positive_indenter_scope s(indenter_);
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

void class_implementation::
non_pod_getters_and_setters(const std::string class_name,
    const property_view_model& vm) {
    stream_ << indenter_ << vm.type().complete_name() << " " << class_name
            << "::" << vm.name() << "() const ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "return "
                << utility_.as_member_variable(vm.name()) << ";"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();

    stream_ << indenter_ << "void " << class_name << "::" << vm.name()
            << "(const " << vm.type().complete_name();

    if (!vm.type().is_primitive())
        stream_ << "&";

    stream_ << " v) ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << utility_.as_member_variable(vm.name())
                << " = v;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void class_implementation::
pod_getters_and_setters(const std::string class_name,
    const property_view_model& vm) {
    // const getter
    stream_ << indenter_ << "const " << vm.type().complete_name()
            << "& " << class_name << "::" << vm.name()
            << "() const ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "return "
                << utility_.as_member_variable(vm.name()) << ";"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();

    // Popsicle immutability
    stream_ << indenter_ << vm.type().complete_name()
            << "& " << class_name << "::" << vm.name()
            << "() ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "return "
                << utility_.as_member_variable(vm.name()) << ";"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();

    // traditional setter
    stream_ << indenter_ << "void " << class_name << "::" << vm.name()
            << "(const " << vm.type().complete_name();

    if (!vm.type().is_primitive())
        stream_ << "&";

    stream_ << " v) ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << utility_.as_member_variable(vm.name())
                << " = v;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();

    // move setter
    stream_ << indenter_ << "void " << class_name << "::" << vm.name()
            << "(const " << vm.type().complete_name();

    if (!vm.type().is_primitive())
        stream_ << "&&";

    stream_ << " v) ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << utility_.as_member_variable(vm.name())
                << " = std::move(v);" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void class_implementation::getters_and_setters(const class_view_model& vm) {
    if (vm.properties().empty())
        return;

    for (const auto p : vm.properties()) {
        if (p.type().is_primitive() || p.type().is_enumeration())
            non_pod_getters_and_setters(vm.name(), p);
        else
            pod_getters_and_setters(vm.name(), p);
    }
}

void class_implementation::
assignment_operator(const class_view_model& vm) {
    // assignment is only available in leaf classes - MEC++-33
    if (vm.all_properties().empty() || vm.is_parent())
        return;

    stream_ << indenter_ << vm.name() << "& "
            << vm.name() << "::operator=(" << vm.name()
            << " other) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "using std::swap;" << std::endl;
        stream_ << indenter_ << "swap(*this, other);"
                << std::endl
                << indenter_ << "return *this;"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

} } }
