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
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/cpp/types/formatters/nested_type_formatting_assistant.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

nested_type_formatting_assistant::
nested_type_formatting_assistant(std::ostream& s) : stream_(s) {}

dogen::formatters::cpp::scoped_namespace_formatter
nested_type_formatting_assistant::
make_scoped_namespace_formatter(const formattables::nested_type_info& t) {
    return dogen::formatters::cpp::scoped_namespace_formatter(
        stream_, t.namespaces(),
        false/*create_anonymous_namespace*/,
        true/*add_new_line*/);
}

bool nested_type_formatting_assistant::
requires_generic_string(const formattables::nested_type_info& t) const {
    return t.is_filesystem_path();
}

bool nested_type_formatting_assistant::
requires_quoting(const formattables::nested_type_info& t) const {
    return t.is_date() || t.is_ptime() || t.is_time_duration() ||
        t.is_char_like() || t.is_string_like();
}

bool nested_type_formatting_assistant::
requires_tidying_up(const formattables::nested_type_info& t) const {
    return t.is_string_like();
}

bool nested_type_formatting_assistant::requires_hashing_helper_method(
    const formattables::nested_type_info& t) {
    return
        t.is_sequence_container() &&
        t.is_associative_container() &&
        t.is_smart_pointer() &&
        t.is_pair() &&
        t.is_optional_like() &&
        t.is_variant_like() &&
        t.is_date() &&
        t.is_ptime() &&
        t.is_time_duration() &&
        t.is_filesystem_path() &&
        t.is_ptree();
}

std::string nested_type_formatting_assistant::streaming_for_type(
    const formattables::nested_type_info& t, const std::string& s) const {
    std::ostringstream ss;
    dogen::formatters::utility_formatter uf(ss);

    if (requires_tidying_up(t))
        uf.insert_streamed("tidy_up_string(" + s + ")");
    else if (requires_generic_string(t))
        uf.insert_streamed(s + ".generic_string()");
    else if (requires_quoting(t))
        uf.insert_quoted_escaped(s);
    else
        uf.insert(s);

    return ss.str();
}

std::ostream& nested_type_formatting_assistant::stream() {
    return stream_;
}

} } }
