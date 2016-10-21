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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formattables/artefact_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/transformation_error.hpp"
#include "dogen/quilt.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.transformer"));

const std::string duplicate_archetype("Duplicate archetype: ");
const std::string duplicate_element("Duplicate element id: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::unordered_map<std::string, formattable> transformer::
transform(const formatters::repository& frp, const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming yarn to formattables."
                             << " Elements in model: " << m.elements().size();

    std::unordered_map<std::string, formattable> r;
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        /*
         * We need to check to see if we've already inserted an
         * element due to the segmentation of elements - we may need
         * to process the master element and one or more extensions.
         */
        auto i(r.find(id));
        if (i == r.end()) {
            formattable fbl;
            const auto pair(std::make_pair(id, fbl));
            const auto ret(r.insert(pair));
            i = ret.first;
            BOOST_LOG_SEV(lg, debug) << "Inserted element: " << id;
        } else
            BOOST_LOG_SEV(lg, debug) << "Element already inserted. ";

        /*
         * Setup the master segment depending on the extension flag.
         */
        auto& fbl(i->second);
        fbl.all_segments().push_back(ptr);
        if (!e.is_element_extension())
            fbl.master_segment(ptr);

        /*
         * Check to see if the element has any formatters. Some
         * elements such as concepts do not have formatters at
         * present.
         */
        const auto ti(std::type_index(typeid(e)));
        const auto j(frp.stock_artefact_formatters_by_type_index().find(ti));
        if (j == frp.stock_artefact_formatters_by_type_index().end()) {
            BOOST_LOG_SEV(lg, debug) << "Element has no formatters: " << id;
            continue;
        }
        BOOST_LOG_SEV(lg, debug) << "Element has formatters " << id;

        /*
         * Perform the artefact expansion by looking at all the
         * archetypes available via the formatters. Note that we check
         * for duplicates on insertion because of the element
         * segmentation scenario. Its there just to ensure we don't
         * have a formatter processing both a master and an extension.
         */
        auto& art_props(fbl.element_properties().artefact_properties());
        for (const auto& fmt : j->second) {
            const auto arch(fmt->archetype_location().archetype());
            const auto pair(std::make_pair(arch, artefact_properties()));
            const auto inserted(art_props.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_archetype << arch;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_archetype + arch));
            }

            BOOST_LOG_SEV(lg, trace) << "Added formatter: " << arch
                                     << " to element: " << id;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming yarn to formattables."
                             << "Size: " << r.size();
    return r;
}

} } } }
