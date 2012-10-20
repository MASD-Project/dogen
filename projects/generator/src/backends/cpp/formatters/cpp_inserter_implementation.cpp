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
#include <sstream>
#include "dogen/generator/backends/cpp/formatters/cpp_inserter_implementation.hpp"

namespace {

// FIXME: until we add support to indenter.
const std::string special_indent("       ");
const std::string parent("__parent_");
const std::string type("__type__");
const std::string inserter("<< ");
const std::string space_inserter(" << ");
const std::string open_bracket(" {");
const std::string close_bracket(" }");
const std::string colon(": ");
const std::string semi_colon(";");
const std::string space(" ");
const std::string underscore("_");
const std::string spaced_comma(", ");

std::string parent_tag(const unsigned int number) {
    std::ostringstream s;
    s << parent << number << underscore << underscore;
    return s.str();
}

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_inserter_implementation::
cpp_inserter_implementation(std::ostream& stream, cpp_indenter& indenter,
    const bool is_inside_class)
    : is_inside_class_(is_inside_class), stream_(stream), indenter_(indenter),
      utility_(stream_, indenter_) {
}

void cpp_inserter_implementation::format(const class_view_model& vm) {
    if (vm.requires_stream_manipulators()) {
        stream_ << indenter_ << "boost::io::ios_flags_saver ifs(s);"
                << std::endl;
        stream_ << indenter_ << "s << std::boolalpha;"
                << std::endl;
        utility_.blank_line();
    }

    stream_ << indenter_ << "s " << inserter
            << utility_.quote(" { ")
            << std::endl;

    stream_ << indenter_ << special_indent << inserter
            << utility_.quote(utility_.quote_escaped(type) + colon)
            << space_inserter
            << utility_.quote(utility_.quote_escaped(vm.name()));

    unsigned int i(0);
    for (const auto p : vm.parents()) {
        stream_ << space_inserter << utility_.quote(spaced_comma) << std::endl;

        stream_ << indenter_ << special_indent << inserter
                << utility_.quote(utility_.quote_escaped(parent_tag(i)) +
                    colon);

        stream_ << space_inserter << p.name() << "::to_stream(s)";
        ++i;
    }

    for (const auto p : vm.properties()) {
        stream_ << space_inserter << utility_.quote(spaced_comma) << std::endl;

        stream_ << indenter_ << special_indent << inserter
                << utility_.quote(utility_.quote_escaped(p.name())
                    + colon) << space_inserter;

        std::ostringstream ss;
        if (is_inside_class_)
            ss << utility_.as_member_variable(p.name());
        else
            ss << "v." << utility_.as_getter(p.name());

        if (p.is_string_like())
            stream_ << utility_.quote_escaped_streamed(ss.str());
        else if (p.is_primitive())
            stream_ << ss.str();
        else
            stream_ << ss.str();
    }

    stream_ << std::endl;
    stream_ << indenter_ << special_indent << inserter
            << utility_.quote(close_bracket) << semi_colon << std::endl;
    stream_ << indenter_ << "return(s);" << std::endl;
}


} } } } }
