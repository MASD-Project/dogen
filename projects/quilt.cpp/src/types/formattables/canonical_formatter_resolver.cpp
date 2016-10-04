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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formattables/resolution_error.hpp"
#include "dogen/quilt.cpp/types/formattables/canonical_formatter_resolver.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.canonical_formatter_resolver"));

const std::string missing_element("Element id not found: ");
const std::string missing_canonical_formatter(
    "Canonical formatter name not found: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

canonical_formatter_resolver::canonical_formatter_resolver(
    const std::unordered_map<std::string, formattable>& formattables)
    : formattables_(formattables) { }

bool canonical_formatter_resolver::
is_canonical_formatter(const std::string& formatter_name) const {
    return boost::ends_with(formatter_name, ".canonical_formatter");
}

std::string canonical_formatter_resolver::resolve(const std::string& element_id,
    const std::string& formatter_name) const {

    if (!is_canonical_formatter(formatter_name)) {
        BOOST_LOG_SEV(lg, debug) << "Formatter name is not canonical: "
                                 << formatter_name;
        return formatter_name;
    }

    const auto i(formattables_.find(element_id));
    if (i == formattables_.end()) {
        BOOST_LOG_SEV(lg, error) << missing_element << element_id;
        BOOST_THROW_EXCEPTION(resolution_error(missing_element + element_id));
    }

    const auto& formattable(i->second);
    const auto& ecfg(formattable.element_configuration());
    const auto& cftf(ecfg.canonical_formatter_to_formatter());
    const auto j(cftf.find(formatter_name));
    if (j == cftf.end()) {
        BOOST_LOG_SEV(lg, error) << missing_canonical_formatter
                                 << formatter_name << " for element: "
                                 <<  element_id;
        BOOST_THROW_EXCEPTION(resolution_error(missing_canonical_formatter +
                formatter_name));
    }

    const auto r(j->second);
    BOOST_LOG_SEV(lg, debug) << "Resolved: " << formatter_name << " to: " << r;
    return r;
}

} } } }
