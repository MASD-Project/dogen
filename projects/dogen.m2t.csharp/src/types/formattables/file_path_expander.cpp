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
#include "dogen.m2t.csharp/types/formatters/model_to_text_transform.hpp"
#include "dogen.m2t.csharp/types/formattables/expansion_error.hpp"
#include "dogen.m2t.csharp/types/formattables/file_path_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "m2t.csharp.formattables.file_path_expander"));

const std::string missing_archetype("Archetype not found: ");

}

namespace dogen::m2t::csharp::formattables {

void file_path_expander::
expand(const formatters::repository& frp, const locator& l, model& fm) const {
    const auto safba(frp.stock_artefact_formatters_by_archetype());
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        auto& formattable(pair.second);

        const auto& e(*formattable.element());
        const auto n(e.name());
        auto& eprops(formattable.element_properties());

        /*
         * Go thorough all the artefact properties and, for each, find
         * the associated formatter.
         */
        for (auto& pair : eprops.artefact_properties()) {
            const auto arch(pair.first);
            auto& art_props(pair.second);

            const auto i(safba.find(arch));
            if (i == safba.end()) {
                BOOST_LOG_SEV(lg, error) << missing_archetype << arch;
                BOOST_THROW_EXCEPTION(
                    expansion_error(missing_archetype + arch));
            }

            /*
             * Ask the formatter to generate the full path for the
             * artefact.
             */
            const auto& fmt(i->second);
            art_props.file_path(fmt->full_path(l, n));

            const auto rp(l.make_relative_path(art_props.file_path()));
            art_props.relative_path(rp);
        }
    }
}

}
