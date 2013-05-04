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
hand_crafted_constructors(const class_view_model& vm) {
    default_constructor(vm);
    destructor(vm);
    move_constructor(vm);
    if (!disable_complete_constructor_)
        complete_constructor(vm);
}

void domain_class_declaration::visitor_method(const class_view_model& vm) {
    if (vm.is_visitable()) {
        utility_.public_access_specifier();
        stream_ << indenter_ << "virtual void accept(const " << vm.name()
                << "_visitor& v) const = 0;" << std::endl;
        stream_ << indenter_ << "virtual void accept(" << vm.name()
                << "_visitor& v) const = 0;" << std::endl;
        stream_ << indenter_ << "virtual void accept(const " << vm.name()
                << "_visitor& v) = 0;" << std::endl;
        stream_ << indenter_ << "virtual void accept(" << vm.name()
                << "_visitor& v) = 0;" << std::endl;
        utility_.blank_line();
    } else if (vm.is_original_parent_visitable() && !vm.is_parent()) {
        utility_.public_access_specifier();
        stream_ << indenter_ << "virtual void accept(const "
                << vm.original_parent_name()
                << "_visitor& v) const override {" << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "v.visit(*this);" << std::endl;
        }
        stream_ << indenter_ << "}" << std::endl;
        utility_.blank_line();
        stream_ << indenter_ << "virtual void accept("
                << vm.original_parent_name()
                << "_visitor& v) const override {" << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "v.visit(*this);" << std::endl;
        }
        stream_ << indenter_ << "}" << std::endl;
        utility_.blank_line();
        stream_ << indenter_ << "virtual void accept(const "
                << vm.original_parent_name()
                << "_visitor& v) override {" << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "v.visit(*this);" << std::endl;
        }
        stream_ << indenter_ << "}" << std::endl;
        utility_.blank_line();
        stream_ << indenter_ << "virtual void accept("
                << vm.original_parent_name()
                << "_visitor& v) override {" << std::endl;

        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "v.visit(*this);" << std::endl;
        }
        stream_ << indenter_ << "}" << std::endl;
        utility_.blank_line();
    }
}

void domain_class_declaration::format(const class_view_model& vm) {
    open_class(vm);
    {
        positive_indenter_scope s(indenter_);
        compiler_generated_constuctors(vm);
        hand_crafted_constructors(vm);
        friends(vm);
        visitor_method(vm);
        if (!disable_io_)
            to_stream(vm);
        getters_and_setters(vm);
        equality(vm);
        swap_and_assignment(vm);
        member_variables(vm);
    }
    close_class();
}

} } }
