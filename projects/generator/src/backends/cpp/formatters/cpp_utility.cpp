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
#include <sstream>
#include <ostream>
#include "dogen/generator/backends/cpp/formatters/cpp_utility.hpp"

namespace  {

const std::string member_variable_postfix("_");
const std::string open_bracket("{");
const std::string close_bracket("}");
const std::string function_brackets("()");
const std::string quote_escaped("\\\"");
const std::string quote("\"");

const std::string public_access_specifier("public:");
const std::string private_access_specifier("private:");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

void cpp_utility::public_access_specifier() {
    cpp_negative_indenter_scope s(indenter_);
    stream_ << ::public_access_specifier << std::endl;
}

void cpp_utility::private_access_specifier() {
    cpp_negative_indenter_scope s(indenter_);
    stream_ << ::private_access_specifier << std::endl;
}

void cpp_utility::open_scope() {
    stream_ << open_bracket << std::endl;
}

void cpp_utility::close_scope() {
    stream_ << indenter_ << close_bracket << std::endl;
}

void cpp_utility::blank_line(unsigned int how_many) {
    for (unsigned int i(0); i < how_many; ++i)
        stream_ << std::endl;
}

std::string
cpp_utility::as_member_variable(const std::string& property_name) const {
    return property_name + member_variable_postfix;
}

std::string
cpp_utility::as_getter(const std::string& property_name) const {
    return property_name + function_brackets;
}

std::string cpp_utility::quote(const std::string& original) const {
    return ::quote + original + ::quote;
}

std::string cpp_utility::quote_escaped(const std::string& original) const {
    return ::quote_escaped + original + ::quote_escaped;
}

} } } } }
