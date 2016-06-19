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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/printing_error.hpp"
#include "dogen/yarn/types/pretty_printer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.pretty_printer"));

const std::string double_colon("::");
const std::string start_marker("<");
const std::string end_marker(">");
const std::string unsupported_separator("Unsupported separator");

}

namespace dogen {
namespace yarn {

pretty_printer::pretty_printer() : separator_(separators::angle_brackets) { }

pretty_printer::
pretty_printer(const separators s) : separator_(s) { }

std::list<std::string> pretty_printer::to_list(const name& n,
    const bool skip_simple_name) const {
    std::list<std::string> r;
    auto lambda([&](const std::string& s) {
            if (!s.empty())
                r.push_back(s);
        });

    const auto& l(n.location());
    for (const auto& m : l.external_modules())
        lambda(m);

    for (const auto& m : l.model_modules())
        lambda(m);

    for (const auto& m : l.internal_modules())
        lambda(m);

    if (!l.element().empty())
        lambda(l.element());

    if (!skip_simple_name)
        lambda(n.simple());

    return r;
}

void pretty_printer::
print_delimited(std::ostream& s, const std::list<std::string>& l) const {
    for (const auto& c : l)
        s << start_marker << c << end_marker;
}

void pretty_printer::print_scoped(std::ostream& s, const std::string& separator,
    const std::list<std::string>& l) const {
    bool is_first(true);

    for (const auto& c : l) {
        if (!is_first)
            s << separator;
        s << c;
        is_first = false;
    }
}

void pretty_printer::
print(std::ostream& s, const name& n, const bool skip_simple_name) const {
    const auto l(to_list(n, skip_simple_name));

    switch (separator_) {
    case separators::angle_brackets:
        print_delimited(s, l);
        break;
    case separators::double_colons:
        print_scoped(s, double_colon, l);
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_separator << ": "
                                 << static_cast<unsigned int>(separator_);
        BOOST_THROW_EXCEPTION(printing_error(unsupported_separator));
    }
}

std::string pretty_printer::
print(const name& n, const bool skip_simple_name) const {
    std::ostringstream s;
    print(s, n,skip_simple_name);
    return s.str();
}

} }
