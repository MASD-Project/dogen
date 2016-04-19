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
#include "dogen/yarn/types/name_pretty_printer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.name_pretty_printer"));

const std::string scope("::");
const std::string start_component("<");
const std::string end_component(">");
const std::string unsupported_style("Printing style is unsupported");

}

namespace dogen {
namespace yarn {

name_pretty_printer::name_pretty_printer(const printing_styles style)
    : style_(style) {
}

void name_pretty_printer::
add_with_delimiters(std::ostream& s, const std::string& c) const {
    if (c.empty())
        return;

    s << start_component << c << end_component;
}

void name_pretty_printer::
print_delimited(std::ostream& s, const name& n) const {
    const auto& l(n.location());

    for (const auto& m : l.external_modules())
        add_with_delimiters(s, m);

    for (const auto& m : l.model_modules())
        add_with_delimiters(s, m);

    for (const auto& m : l.internal_modules())
        add_with_delimiters(s, m);

    add_with_delimiters(s, l.element());
    add_with_delimiters(s, n.simple());
}

void name_pretty_printer::print_scoped(std::ostream& /*s*/, const name& /*n*/) const {
    
}

std::string name_pretty_printer::print(const name& n) const {
    std::ostringstream s;

    switch (style_) {
    case printing_styles::delimited:
        print_delimited(s, n);
        break;
    case printing_styles::scoped:
        print_scoped(s, n);
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_style << ": "
                                 << static_cast<unsigned int>(style_);
        BOOST_THROW_EXCEPTION(printing_error(unsupported_style));
    }
    return s.str();
}

} }
