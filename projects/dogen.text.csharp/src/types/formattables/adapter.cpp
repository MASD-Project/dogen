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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.text.csharp/types/formattables/artefact_properties.hpp"
#include "dogen.text.csharp/types/formattables/adaptation_error.hpp"
#include "dogen.text.csharp/types/transforms/model_to_text_transform.hpp"
#include "dogen.text.csharp/types/formattables/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.csharp.formattables.adapter"));

}

namespace dogen::text::csharp::formattables {

std::unordered_map<std::string, formattable>
adapter::adapt(const transforms::repository& frp,
    const text::entities::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming yarn to formattables."
                             << " Elements in model: " << m.elements().size();

    std::unordered_map<std::string, formattable> r;
    for (const auto& ea : m.elements()) {
        auto ptr(ea.element());
        formattable fbl;
        fbl.element(ea.element());
        fbl.artefacts(ea.artefacts());

        const auto& e(*ptr);
        const auto id(e.name().qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        /*
         * Check to see if the element has any formatters.
         */
        const auto mn(e.meta_name().id());
        const auto j(frp.stock_artefact_formatters_by_meta_name().find(mn));
        if (j == frp.stock_artefact_formatters_by_meta_name().end()) {
            BOOST_LOG_SEV(lg, debug) << "Element has no formatters: " << id;
            continue;
        }
        BOOST_LOG_SEV(lg, debug) << "Element has formatters " << id;

        /*
         * Perform the artefact expansion by looking at all the
         * archetypes available via the formatters.
         */
        auto& art_props(fbl.element_properties().artefact_properties());
        for (const auto& fmt : j->second) {
            const auto pmn(fmt->archetype().meta_name());
            const auto arch(pmn.id());
            art_props[arch] = artefact_properties();

            BOOST_LOG_SEV(lg, debug) << "Added formatter: " << arch
                                     << " to element: " << id;
        }

        r[id] = fbl;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming yarn to formattables."
                             << "Size: " << r.size();
    return r;
}

}
