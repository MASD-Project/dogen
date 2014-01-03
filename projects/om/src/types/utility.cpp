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
#include "dogen/om/types/indent_filter.hpp"
#include "dogen/om/types/utility.hpp"

namespace  {

const std::string member_variable_postfix("_");
const std::string open_bracket("{");
const std::string close_bracket("}");
const std::string function_brackets("()");
const std::string quote_escaped("\\\"");
const std::string quote("\"");
const std::string inserter("<< ");
const std::string space(" ");

const std::string public_access_specifier("public:");
const std::string protected_access_specifier("protected:");
const std::string private_access_specifier("private:");

}

namespace dogen {
namespace om {

utility::utility(std::ostream& stream) : stream_(stream) {}

void utility::handle_padding_before(const padding_types padding) {
    if (padding == padding_types::before)
        stream_ << space;
}

void utility::handle_padding_after(const padding_types padding) {
    if (padding == padding_types::after)
        stream_ << space;
    else if (padding == padding_types::new_line)
        stream_ << std::endl;
}

void utility::public_access_specifier(const padding_types padding) {
    negative_indenter_scope s(stream_);
    handle_padding_before(padding);
    stream_ << ::public_access_specifier;
    handle_padding_after(padding);
}

void utility::protected_access_specifier(const padding_types padding) {
    negative_indenter_scope s(stream_);
    handle_padding_before(padding);
    stream_ << ::protected_access_specifier;
    handle_padding_after(padding);
}

void utility::private_access_specifier(const padding_types padding) {
    negative_indenter_scope s(stream_);
    handle_padding_before(padding);
    stream_ << ::private_access_specifier;
    handle_padding_after(padding);
}

void utility::open_scope(const padding_types padding) {
    handle_padding_before(padding);
    stream_ << open_bracket;
    handle_padding_after(padding);
}

void utility::close_scope(const padding_types padding) {
    handle_padding_before(padding);
    stream_ << close_bracket;
    handle_padding_after(padding);

}

void utility::
blank_line(const bool is_managed, const unsigned int how_many) {
    if (is_managed)
        stream_ << manage_blank_lines;

    for (unsigned int i(0); i < how_many; ++i)
        stream_ << std::endl;
}

void utility::managed_blank_line() {
    blank_line(true);
}

std::string utility::
as_member_variable(const std::string& property_name) const {
    return property_name + member_variable_postfix;
}

std::string utility::as_getter(const std::string& property_name) const {
    return property_name + function_brackets;
}

std::string utility::quote(const std::string& original) const {
    return ::quote + original + ::quote;
}

std::string utility::quote_escaped(const std::string& original) const {
    return ::quote_escaped + original + ::quote_escaped;
}

std::string utility::quote_escaped_streamed(const std::string& original) const {
    std::ostringstream s;
    s << ::quote << ::quote_escaped << ::quote << space
      << inserter << original << space
      << inserter << ::quote << ::quote_escaped << ::quote;
    return s.str();
}

} }
