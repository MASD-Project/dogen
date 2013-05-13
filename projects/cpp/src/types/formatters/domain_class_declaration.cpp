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
#include "dogen/cpp/types/formatters/domain_class_declaration.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

domain_class_declaration::
domain_class_declaration(std::ostream& stream,
    const bool disable_complete_constructor, const bool disable_io,
    const bool serialization_enabled)
    : class_declaration(stream, serialization_enabled),
      disable_complete_constructor_(disable_complete_constructor),
      disable_io_(disable_io) { }

void domain_class_declaration::
hand_crafted_constructors(const class_info& ci) {
    default_constructor(ci);
    destructor(ci);
    move_constructor(ci);
    if (!disable_complete_constructor_)
        complete_constructor(ci);
}

void domain_class_declaration::visitor_method(const class_info& ci) {
    if (ci.is_visitable()) {
        utility_.public_access_specifier();
        stream_ << indenter_ << "virtual void accept(const " << ci.name()
                << "_visitor& v) const = 0;" << std::endl;
        stream_ << indenter_ << "virtual void accept(" << ci.name()
                << "_visitor& v) const = 0;" << std::endl;
        stream_ << indenter_ << "virtual void accept(const " << ci.name()
                << "_visitor& v) = 0;" << std::endl;
        stream_ << indenter_ << "virtual void accept(" << ci.name()
                << "_visitor& v) = 0;" << std::endl;
        utility_.blank_line();
    } else if (ci.is_original_parent_visitable() && !ci.is_parent()) {
        utility_.public_access_specifier();
        stream_ << indenter_ << "virtual void accept(const "
                << ci.original_parent_name()
                << "_visitor& v) const override {" << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "v.visit(*this);" << std::endl;
        }
        stream_ << indenter_ << "}" << std::endl;
        utility_.blank_line();
        stream_ << indenter_ << "virtual void accept("
                << ci.original_parent_name()
                << "_visitor& v) const override {" << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "v.visit(*this);" << std::endl;
        }
        stream_ << indenter_ << "}" << std::endl;
        utility_.blank_line();
        stream_ << indenter_ << "virtual void accept(const "
                << ci.original_parent_name()
                << "_visitor& v) override {" << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "v.visit(*this);" << std::endl;
        }
        stream_ << indenter_ << "}" << std::endl;
        utility_.blank_line();
        stream_ << indenter_ << "virtual void accept("
                << ci.original_parent_name()
                << "_visitor& v) override {" << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "v.visit(*this);" << std::endl;
        }
        stream_ << indenter_ << "}" << std::endl;
        utility_.blank_line();
    }
}

void domain_class_declaration::format(const class_info& ci) {
    open_class(ci);
    {
        positive_indenter_scope s(indenter_);
        compiler_generated_constuctors(ci);
        hand_crafted_constructors(ci);
        friends(ci);
        visitor_method(ci);
        if (!disable_io_)
            to_stream(ci);
        getters_and_setters(ci);
        equality(ci);
        swap_and_assignment(ci);
        member_variables(ci);
    }
    close_class();
}

} } }
