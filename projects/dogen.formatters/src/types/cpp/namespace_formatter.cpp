/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen.formatters/types/cpp/namespace_formatter.hpp"

namespace {

const std::string empty;

}

namespace dogen {
namespace formatters {
namespace cpp {

namespace_formatter::namespace_formatter(
    const bool create_anonymous_namespace, const bool add_new_line)
    : create_anonymous_namespace_(create_anonymous_namespace),
      add_new_line_(add_new_line) {}

void namespace_formatter::
format_begin(std::ostream& s, const std::string& ns) const {
    if (!create_anonymous_namespace_ && ns.empty())
        return;

    s << "namespace ";
    if (ns.empty())
        s << "{";
    else
        s << ns << " {";

    s << std::endl;
}

void namespace_formatter::
format_end(std::ostream& s, const std::string& ns) const {
    if (!create_anonymous_namespace_ && ns.empty())
        return;

    s << "}"; // no space and no std::endl by design
}

void namespace_formatter::
format_begin(std::ostream& s, const std::list<std::string>& ns) const {
    if (!create_anonymous_namespace_ && ns.empty())
        return;

    if (ns.empty()) {
        format_begin(s, empty);
        return;
    }

    for (auto n : ns)
        format_begin(s, n);
}

void namespace_formatter::
format_end(std::ostream& s, const std::list<std::string>& ns) const {
    if (!create_anonymous_namespace_ && ns.empty())
        return;

    if (ns.empty()) {
        format_end(s, empty);
        return;
    }

    bool first(true);
    for (auto n : ns) {
        if (!first)
            s << " ";

        format_end(s, n);
        first = false;
    }

    if (add_new_line_)
        s << std::endl;
}

} } }
