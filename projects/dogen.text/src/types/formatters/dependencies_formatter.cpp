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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.text/types/formatters/formatting_error.hpp"
#include "dogen.utility/types/formatters/indent_filter.hpp"
#include "dogen.text/types/formatters/dependencies_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("text.formatters.dependencies_formatter"));

const std::string using_keyword("using ");
const std::string include_keyword("#include ");

const std::string unsupported_technical_space(
    "Technical space is unsupported or invalid: ");

}

namespace dogen::text::formatters {

void dependencies_formatter::format_cpp_includes(std::ostream& s,
    const std::list<std::string>& dependencies) const {
    for (const auto& d : dependencies)
        s << include_keyword << d << std::endl;
}

void dependencies_formatter::format_csharp_usings(std::ostream& s,
    const std::list<std::string>& dependencies) const {

    for (const auto& d : dependencies)
        s << using_keyword << d << std::endl;
}

void dependencies_formatter::format(std::ostream& s,
    const identification::entities::technical_space ts,
    const std::list<std::string>& dependencies) const {

    using identification::entities::technical_space;
    switch(ts) {
    case technical_space::cpp:
        format_cpp_includes(s, dependencies);
        break;
    case technical_space::csharp:
        format_csharp_usings(s, dependencies);
        break;
    default:
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(
            formatting_error(unsupported_technical_space + s));
    }

    using namespace dogen::utility::formatters;
    if (!dependencies.empty())
        s << manage_blank_lines << std::endl;
}

}
