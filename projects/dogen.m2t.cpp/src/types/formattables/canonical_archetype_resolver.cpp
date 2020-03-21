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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.m2t.cpp/types/formattables/resolution_error.hpp"
#include "dogen.m2t.cpp/types/formattables/canonical_archetype_resolver.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "generation.cpp.formattables.canonical_archetype_resolver"));

const auto archetype_postfix(".canonical_archetype");

const std::string missing_element("Cannot find formattables for element id: ");
const std::string missing_canonical_archetype(
    "Canonical archetype not found: ");

}

namespace dogen::m2t::cpp::formattables {

canonical_archetype_resolver::canonical_archetype_resolver(
    const std::unordered_map<std::string, formattable>& formattables)
    : formattables_(formattables) { }

bool canonical_archetype_resolver::
is_canonical_archetype(const std::string& archetype) const {
    return boost::ends_with(archetype, archetype_postfix);
}

std::string canonical_archetype_resolver::resolve(const std::string& element_id,
    const std::string& archetype) const {

    BOOST_LOG_SEV(lg, debug) << "Resolving archetype: " << archetype;
    if (!is_canonical_archetype(archetype)) {
        BOOST_LOG_SEV(lg, debug) << "Archetype name is not canonical: "
                                 << archetype;
        return archetype;
    }

    const auto i(formattables_.find(element_id));
    if (i == formattables_.end()) {
        BOOST_LOG_SEV(lg, error) << missing_element << element_id;
        BOOST_THROW_EXCEPTION(resolution_error(missing_element + element_id));
    }

    const auto& formattable(i->second);
    const auto& eprops(formattable.element_properties());
    const auto& cata(eprops.canonical_archetype_to_archetype());
    const auto j(cata.find(archetype));
    if (j == cata.end()) {
        BOOST_LOG_SEV(lg, error) << missing_canonical_archetype
                                 << archetype << " for element: " << element_id;
        BOOST_THROW_EXCEPTION(
            resolution_error(missing_canonical_archetype + archetype));
    }

    const auto r(j->second);
    BOOST_LOG_SEV(lg, debug) << "Resolved: " << archetype << " to: " << r;
    return r;
}

}
