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
#include <typeindex>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_support_types.hpp"
#include "dogen/quilt.cpp/types/formattables/canonical_archetype_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.formattables.canonical_archetype_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void canonical_archetype_expander::
expand(const formatters::container& fc, model& fm) const {

    const auto cs(formatters::inclusion_support_types::canonical_support);
    const auto& ffti(fc.file_formatters_by_type_index());

    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& eprops(pair.second.element_properties());
        for (const auto& segment : formattable.all_segments()) {
            const auto& e(*segment);

            /*
             * For each element segment, find the corresponding
             * formatters.
             */
            const auto ti(std::type_index(typeid(e)));
            BOOST_LOG_SEV(lg, debug) << "Type index: " << ti.name();

            /*
             * Not all elements have formatters; for example, concepts
             * don't have any at present. If so, skip the element.
             */
            const auto i(ffti.find(ti));
            if (i == ffti.end()) {
                BOOST_LOG_SEV(lg, debug) << "Element has no formatters.";
                continue;
            }

            /*
             * Find the canonical formatter for the element and slot
             * it in, pairing the canonical name against the formatter
             * name.
             */
            const auto& formatters(i->second);
            for (const auto& ptr : formatters) {
                const auto& formatter(*ptr);
                if (formatter.inclusion_support_type() != cs)
                    continue;

                const auto& al(formatter.archetype_location());
                const auto arch(al.archetype());
                const auto fctn(al.facet());

                using formatters::traits;
                const auto carch(traits::canonical_archetype(fctn));
                eprops.canonical_archetype_to_archetype()[carch] = arch;
                BOOST_LOG_SEV(lg, debug) << "Mapping " << carch
                                         << " to " << arch;
            }
        }
    }
}

} } } }
