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
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/cpp/types/formatters/nested_type_formatting_assistant.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

nested_type_formatting_assistant::nested_type_formatting_assistant(
    std::ostream& s, const formattables::nested_type_info& nt)
    : stream_(s), nested_type_(nt) {}

dogen::formatters::cpp::scoped_namespace_formatter
nested_type_formatting_assistant::make_scoped_namespace_formatter() {
    return dogen::formatters::cpp::scoped_namespace_formatter(
        stream_, nested_type_.namespaces(),
        false/*create_anonymous_namespace*/,
        true/*add_new_line*/);
}

void nested_type_formatting_assistant::quote(const std::string& /*s*/) const {
/*    dogen::formatters::utility_formatter uf(stream_);
    uf.insert_quoted

    void insert_escaped(const std::string& content_to_escape,
        const quote_types quote_to_escape = quote_types::double_quote,
        const spacing_types st = spacing_types::no_space) const;

    void (const std::string& content_to_quote,
        const bool escape_content = false,
        const quote_types qt = quote_types::double_quote,
        const spacing_types st = spacing_types::no_space) const;
*/
}

void nested_type_formatting_assistant::
quote_and_quote_escaped(const std::string& /*s*/) const {
}

} } }
