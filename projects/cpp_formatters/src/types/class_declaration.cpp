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
#include <iostream>
#include <ostream>
#include "dogen/cpp_formatters/types/doxygen_comments.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/class_declaration.hpp"

namespace dogen {
namespace cpp_formatters {

class_declaration::
class_declaration(std::ostream& stream, const bool disable_serialization)
    : stream_(stream), utility_(stream_, indenter_),
      disable_serialization_(disable_serialization) { }

void class_declaration::open_class(const cpp::class_info& ci) {
    doxygen_comments dc(stream_, indenter_);
    dc.format(ci.documentation());
    stream_ << indenter_ << "class " << ci.name();

    if (!ci.is_parent())
        stream_ << " final";

    const auto parents(ci.parents());
    if (!parents.empty()) {
        stream_ << " :";

        qname qname(stream_);
        if (parents.size() == 1) {
            stream_ << " public ";
            qname.format(parents.front());
        } else {
            bool is_first(true);
            positive_indenter_scope s(indenter_);
            for (const auto p : ci.parents()) {
                stream_ << (is_first ? "" : ",") << std::endl << indenter_;
                stream_ << " public " << p.name();
                is_first = false;
            }
        }
    }
    stream_ << " {" << std::endl;
}

void class_declaration::close_class() {
    stream_ << indenter_ << "};" << std::endl;
    utility_.blank_line();
}

void class_declaration::default_constructor(const cpp::class_info& ci) {
    if (!ci.requires_manual_default_constructor())
        return;

    const auto props(ci.properties());
    utility_.public_access_specifier();
    stream_ << indenter_ << ci.name() << "();" << std::endl;
    utility_.blank_line();
}

void class_declaration::complete_constructor(const cpp::class_info& ci) {
    const auto props(ci.all_properties());
    if (props.empty())
        return;

    utility_.public_access_specifier();
    if (props.size() == 1) {
        const auto p(*props.begin());
        stream_ << indenter_ << "explicit " << ci.name() << "(const "
                << p.type().complete_name();

        if (!p.type().is_primitive())
            stream_ << "&";

        stream_ << " " << p.name() << ");" << std::endl;
        utility_.blank_line();
        return;
    }

    stream_ << indenter_ << ci.name() << "(";
    {
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
        stream_ << ");" << std::endl;
    }
    utility_.blank_line();
}

void class_declaration::move_constructor(const cpp::class_info& ci) {
    if (!ci.requires_manual_move_constructor())
        return;

    const auto props(ci.all_properties());
    if (props.empty())
        return;

    utility_.public_access_specifier();
    const auto p(*props.begin());
    stream_ << indenter_ << ci.name() << "(" << ci.name()
            << "&& rhs);" << std::endl;
    utility_.blank_line();
}

void class_declaration::destructor(const cpp::class_info& ci) {
    /*
     * according to MEC++, item 33, base classes should always be
     * abstract. this avoids all sorts of tricky problems with
     * assignment and swap.
     *
     * incidentally, this also fixes some strange clang errors:
     * undefined reference to `vtable.
     */
    if (ci.is_parent()) {
        stream_ << indenter_ << "virtual ~" << ci.name()
                << "() noexcept = 0;" << std::endl;
        utility_.blank_line();
    } else if (ci.parents().size() != 0) {
        stream_ << indenter_ << "virtual ~" << ci.name()
                << "() noexcept { }" << std::endl;
        utility_.blank_line();
    }
}

void class_declaration::
compiler_generated_constuctors(const cpp::class_info& ci) {
    utility_.public_access_specifier();

    if (!ci.requires_manual_default_constructor())
        stream_ << indenter_ << ci.name() << "() = default;" << std::endl;

    stream_ << indenter_ << ci.name() << "(const " << ci.name()
            << "&) = default;" << std::endl;

    if (!ci.requires_manual_move_constructor()) {
        stream_ << indenter_ << ci.name() << "(" << ci.name()
                << "&&) = default;"
                << std::endl;
    }

    if (!ci.is_parent() && ci.parents().empty()) {
        stream_ << indenter_ << "~" << ci.name() << "() = default;"
                << std::endl;
    }

    if (ci.is_immutable()) {
        stream_ << indenter_ << ci.name() << "& operator=(const " << ci.name()
                << "&) = delete;" << std::endl;
    } else if (ci.all_properties().empty()) {
        stream_ << indenter_ << ci.name() << "& operator=(const " << ci.name()
                << "&) = default;" << std::endl;
    }
    utility_.blank_line();
}

void class_declaration::friends(const cpp::class_info& ci) {
    if (disable_serialization_)
        return;

    utility_.private_access_specifier();

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "friend void boost::serialization::save(Archive& ar"
            << ", const " << ci.name() << "& v, unsigned int version);"
            << std::endl;
    utility_.blank_line();

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "friend void boost::serialization::load(Archive& ar"
            << ", " << ci.name() << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();
}

void class_declaration::
non_object_getters_and_setters(const std::string class_name,
    const cpp::property_info& pi) {
    doxygen_comments dc(stream_, indenter_);
    dc.format(pi.documentation());
    if (!pi.is_immutable())
        dc.format_start_block(pi.documentation());

    stream_ << indenter_ << pi.type().complete_name() << " " << pi.name()
            << "() const;" << std::endl;

    if (!pi.is_immutable()) {
        stream_ << indenter_;
        if (pi.is_fluent())
            stream_ << class_name << "& ";
        else
            stream_ << "void ";

        stream_ << pi.name() << "(const " << pi.type().complete_name();

        if (!pi.type().is_primitive())
            stream_ << "&";

        stream_ << " v);" << std::endl;
    }

    if (!pi.is_immutable())
        dc.format_end_block(pi.documentation());
    utility_.blank_line();
}

void class_declaration::
object_getters_and_setters(const std::string class_name,
    const cpp::property_info& pi) {
    doxygen_comments dc(stream_, indenter_);
    dc.format(pi.documentation());
    if (!pi.is_immutable())
        dc.format_start_block(pi.documentation());

    // const getter
    stream_ << indenter_ << "const " << pi.type().complete_name()
            << "& " << pi.name() << "() const;" << std::endl;

    if (!pi.is_immutable()) {
        // Popsicle immutability
        stream_ << indenter_ << "" << pi.type().complete_name()
                << "& " << pi.name() << "();" << std::endl;

        // traditional setter
        stream_ << indenter_;
        if (pi.is_fluent())
            stream_ << class_name << "& ";
        else
            stream_ << "void ";
        stream_ << pi.name() << "(const " << pi.type().complete_name();

        if (!pi.type().is_primitive())
            stream_ << "&";

        stream_ << " v);" << std::endl;

        // move setter
        stream_ << indenter_;
        if (pi.is_fluent())
            stream_ << class_name << "& ";
        else
            stream_ << "void ";
        stream_ << pi.name() << "(const " << pi.type().complete_name();

        if (!pi.type().is_primitive())
            stream_ << "&&";

        stream_ << " v);" << std::endl;
    }

    if (!pi.is_immutable())
        dc.format_end_block(pi.documentation());
    utility_.blank_line();
}

void class_declaration::getters_and_setters(const cpp::class_info& ci) {
    if (ci.properties().empty())
        return;

    utility_.public_access_specifier();
    for (const auto p : ci.properties()) {
        if (p.type().is_primitive() || p.type().is_enumeration()) {
            non_object_getters_and_setters(ci.name(), p);
            continue;
        }

        object_getters_and_setters(ci.name(), p);
    }
}

void class_declaration::member_variables(const cpp::class_info& ci) {
    if (ci.properties().empty())
        return;

    utility_.private_access_specifier();
    for (const auto p : ci.properties()) {
        stream_ << indenter_ << p.type().complete_name() << " "
                << utility_.as_member_variable(p.name()) << ";"
                << std::endl;
    }
}

void class_declaration::equality(const cpp::class_info& ci) {
    // equality is only public in leaf classes - MEC++-33
    if (ci.is_parent()) {
        utility_.protected_access_specifier();
        stream_ << indenter_ << "bool compare(const " << ci.name()
                <<  "& rhs) const;" << std::endl;
    } else {
        utility_.public_access_specifier();
        stream_ << indenter_ << "bool operator==(const " << ci.name()
                <<  "& rhs) const;" << std::endl;
        stream_ << indenter_ << "bool operator!=(const " << ci.name()
                << "& rhs) const ";
        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "return !this->operator==(rhs);"
                    << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }

    if (!ci.is_parent() && ci.parents().empty())
        return;

    utility_.public_access_specifier();
    if (ci.is_parent() && ci.parents().empty()) {
        stream_ << indenter_
                << "virtual bool equals(const " << ci.name()
                <<  "& other) const = 0;"
                << std::endl;
    } else if (ci.is_parent()) {
        stream_ << indenter_
                << "virtual bool equals(const "
                << ci.original_parent_name_qualified()
                <<  "& other) const = 0;"
                << std::endl;
    } else {
        stream_ << indenter_
                << "bool equals(const "
                << ci.original_parent_name_qualified()
                <<  "& other) const override;"
                << std::endl;
    }
    utility_.blank_line();
}

void class_declaration::to_stream(const cpp::class_info& ci) {
    if (!ci.is_parent() && ci.parents().empty())
        return;

    utility_.public_access_specifier();
    if (ci.is_parent()) {
        stream_ << indenter_
                << "virtual void to_stream("
                << "std::ostream& s) const;"
                << std::endl;
    } else {
        stream_ << indenter_
                << "void to_stream(std::ostream& s) "
                << "const override;"
                << std::endl;
    }
    utility_.blank_line();
}

void class_declaration::swap_and_assignment(const cpp::class_info& ci) {
    if ((ci.all_properties().empty() && !ci.is_parent()) || ci.is_immutable())
        return;

    // swap is only public in leaf classes - MEC++-33
    if (ci.is_parent())
        utility_.protected_access_specifier();
    else
        utility_.public_access_specifier();

    stream_ << indenter_ << "void swap(" << ci.name() << "& other) noexcept;"
            << std::endl;

    // assignment is only available in leaf classes - MEC++-33
    if (!ci.is_parent()) {
        stream_ << indenter_ << ci.name() << "& operator=(" << ci.name()
                << " other);" << std::endl;
    }

    utility_.blank_line();
}

} }
