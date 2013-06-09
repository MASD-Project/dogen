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
#include "dogen/cpp/types/formatters/qname.hpp"
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

void class_implementation::default_constructor(const class_info& ci) {
    if (!ci.requires_manual_default_constructor())
        return;

    stream_ << indenter_ << ci.name() << "::"
            << ci.name() << "()" << std::endl;
    {
        positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto p : ci.properties()) {
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

void class_implementation::move_constructor(const class_info& ci) {
    if (!ci.requires_manual_move_constructor())
        return;

    stream_ << indenter_ << ci.name() << "::" << ci.name()
            << "(" << ci.name() << "&& rhs)" << std::endl;
    {
        positive_indenter_scope s(indenter_);
        bool is_first(true);

        for (const auto p : ci.parents()) {
            if (is_first)
                stream_ << indenter_ << ": ";
            else
                stream_ << "," << std::endl << indenter_ << "  ";

            qname qname(stream_);
            qname.format(p);
            stream_ << "(" << std::endl;
            {
                positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "std::forward<";
                qname.format(p);
                stream_ << ">(rhs))";
            }
            is_first = false;
        }

        for (const auto p : ci.properties()) {
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

void class_implementation::complete_constructor(const class_info& ci) {
    const auto props(ci.all_properties());
    if (props.empty())
        return;

    stream_ << indenter_ << ci.name() << "::" << ci.name() << "(";

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

        for (const auto p : ci.parents()) {
            qname qname(stream_);
            qname.format(p);

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

        for (const auto p : ci.properties()) {
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

void class_implementation::to_stream(const class_info& ci) {
    if (!ci.is_parent() && ci.parents().empty())
        return;

    stream_ << "void " << ci.name()
            << "::to_stream(std::ostream& s) const ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        const bool inside_class(true);
        inserter_implementation inserter(stream_, indenter_, inside_class);
        inserter.format_inserter_implementation(ci);
    }
    utility_.close_scope();
    utility_.blank_line();
}

void class_implementation::swap(const class_info& ci) {
    if ((ci.all_properties().empty() && !ci.is_parent()) || ci.is_immutable())
        return;

    const bool empty(ci.all_properties().empty() && ci.parents().empty());
    stream_ << indenter_ << "void " << ci.name() << "::swap("
            << ci.name() << "&" << (empty ? "" : " other")
            <<") noexcept ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        const auto parents(ci.parents());
        for (const auto p : parents)
            stream_ << indenter_ << p.name() << "::swap(other);" << std::endl;

        if (!parents.empty())
            utility_.blank_line();

        const auto props(ci.properties());
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

void class_implementation::equals_method(const class_info& ci) {
    if (ci.is_parent() || ci.parents().empty())
        return;

    stream_ << indenter_ << "bool " << ci.name() << "::equals(const "
            << ci.original_parent_name_qualified() << "& other) const ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "const " << ci.name()
                << "* const p(dynamic_cast<const " << ci.name()
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

void class_implementation::equals_operator(const class_info& ci) {
    if (ci.is_parent()) {
        stream_ << indenter_ << "bool " << ci.name() << "::compare(const "
                << ci.name() <<  "& ";
    } else {
        stream_ << indenter_ << "bool " << ci.name() << "::operator==(const "
                << ci.name() <<  "& ";
    }

    if (ci.all_properties().empty())
        stream_ << "/*rhs*/";
    else
        stream_ << "rhs";

    stream_ << ") const ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        if (ci.all_properties().empty())
            stream_ << indenter_ << "return true";
        else {
            stream_ << indenter_ << "return ";
            bool is_first(true);
            {
                positive_indenter_scope s(indenter_);
                const auto parents(ci.parents());
                for (const auto p : parents) {
                    if (!is_first)
                        stream_ << " &&" << std::endl << indenter_;
                    {
                        positive_indenter_scope s(indenter_);
                        stream_ << p.name() << "::compare(rhs)";
                    }
                    is_first = false;
                }

                for (const auto p : ci.properties()) {
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
    const property_info& ci) {
    stream_ << indenter_ << ci.type().complete_name() << " " << class_name
            << "::" << ci.name() << "() const ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "return "
                << utility_.as_member_variable(ci.name()) << ";"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();

    if (!ci.is_immutable()) {
        stream_ << indenter_;
        if (ci.is_fluent())
            stream_ << class_name << "& ";
        else
            stream_ << "void ";

        stream_ << class_name << "::" << ci.name() << "(const "
                << ci.type().complete_name();

        if (!ci.type().is_primitive())
            stream_ << "&";

        stream_ << " v) ";
        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << utility_.as_member_variable(ci.name())
                    << " = v;" << std::endl;

            if (ci.is_fluent())
                stream_ << indenter_ << "return *this;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
}

void class_implementation::
pod_getters_and_setters(const std::string class_name,
    const property_info& ci) {
    // const getter
    stream_ << indenter_ << "const " << ci.type().complete_name()
            << "& " << class_name << "::" << ci.name()
            << "() const ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "return "
                << utility_.as_member_variable(ci.name()) << ";"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();

    if (!ci.is_immutable()) {
        // Popsicle immutability
        stream_ << indenter_ << ci.type().complete_name()
                << "& " << class_name << "::" << ci.name()
                << "() ";
        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "return "
                    << utility_.as_member_variable(ci.name()) << ";"
                    << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();

        // traditional setter
        stream_ << indenter_;
        if (ci.is_fluent())
            stream_ << class_name << "& ";
        else
            stream_ << "void ";
        stream_ << class_name << "::" << ci.name() << "(const "
                << ci.type().complete_name();

        if (!ci.type().is_primitive())
            stream_ << "&";

        stream_ << " v) ";
        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << utility_.as_member_variable(ci.name())
                    << " = v;" << std::endl;
            if (ci.is_fluent())
                stream_ << indenter_ << "return *this;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();

        // move setter
        stream_ << indenter_;
        if (ci.is_fluent())
            stream_ << class_name << "& ";
        else
            stream_ << "void ";
        stream_ << class_name << "::" << ci.name() << "(const "
                << ci.type().complete_name();

        if (!ci.type().is_primitive())
            stream_ << "&&";

        stream_ << " v) ";
        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << utility_.as_member_variable(ci.name())
                    << " = std::move(v);" << std::endl;
            if (ci.is_fluent())
                stream_ << indenter_ << "return *this;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
}

void class_implementation::getters_and_setters(const class_info& ci) {
    if (ci.properties().empty())
        return;

    for (const auto p : ci.properties()) {
        if (p.type().is_primitive() || p.type().is_enumeration())
            non_pod_getters_and_setters(ci.name(), p);
        else
            pod_getters_and_setters(ci.name(), p);
    }
}

void class_implementation::
assignment_operator(const class_info& ci) {
    // assignment is only available in leaf classes - MEC++-33
    if (ci.all_properties().empty() || ci.is_parent() || ci.is_immutable())
        return;

    stream_ << indenter_ << ci.name() << "& "
            << ci.name() << "::operator=(" << ci.name()
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
