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
#include <iterator>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.utility/io/unordered_map_io.hpp"
#include "masd.dogen.generation.cpp/types/workflow_error.hpp"
#include "masd.dogen.coding/io/meta_model/formatting_styles_io.hpp"
#include "masd.dogen.generation.cpp/io/formattables/artefact_properties_io.hpp"
#include "masd.dogen.generation.cpp/types/formatters/context.hpp"
#include "masd.dogen.generation.cpp/types/formatters/wale_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/workflow.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("quit.cpp.formatters.workflow"));

const std::string archetype_not_found("Archetype not found: ");
const std::string invalid_formatting_style("Invalid formatting style");

}

namespace masd::dogen::generation::cpp::formatters {

std::shared_ptr<cpp::formatters::registrar> workflow::registrar_;

workflow::workflow(const annotations::type_repository& atrp,
    const annotations::annotation_factory& af,
    const dogen::extraction::repository& frp)
    : stitch_formatter_(atrp, af, frp) { }

cpp::formatters::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::formatters::registrar>();

    return *registrar_;
}

const coding::meta_model::artefact_properties& workflow::get_artefact_properties(
    const coding::meta_model::element& e, const std::string& archetype) const {

    const auto& ap(e.artefact_properties());
    const auto i(ap.find(archetype));
    if (i == ap.end()) {
        BOOST_LOG_SEV(lg, error) << archetype_not_found << archetype;
        BOOST_THROW_EXCEPTION(workflow_error(archetype_not_found + archetype));
    }
    return i->second;
}

std::list<coding::meta_model::artefact>
workflow::format(const std::unordered_set<coding::meta_model::element_archetype>&
    enabled_archetype_for_element, const formattables::model& fm,
    const coding::meta_model::element& e,
    const formattables::element_properties& ep) const {

    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

    const auto mn(e.meta_name().id());
    BOOST_LOG_SEV(lg, debug) << "Meta name: " << mn;

    std::list<coding::meta_model::artefact> r;
    const auto& frp(registrar().formatter_repository());
    const auto i(frp.stock_artefact_formatters_by_meta_name().find(mn));
    if (i == frp.stock_artefact_formatters_by_meta_name().end()) {
        BOOST_LOG_SEV(lg, debug) << "No formatters for meta name: " << mn;
        return r;
    }

    const auto& fmts(i->second);
    for (const auto& ptr : fmts) {
        const auto& fmt(*ptr);
        const auto arch(fmt.archetype_location().archetype());
        const auto& ap(get_artefact_properties(e, arch));

        if (!ap.enabled()) {
            BOOST_LOG_SEV(lg, debug) << "Archetype is disabled: " << arch;
            continue;
        }

        using coding::meta_model::formatting_styles;
        const auto& frp(registrar().formatter_repository());
        context ctx(enabled_archetype_for_element, ep, fm,
            frp.helper_formatters());

        const auto fs(ap.formatting_style());
         if (fs == formatting_styles::stock) {
            const auto id(fmt.id());
            BOOST_LOG_SEV(lg, debug) << "Using the stock formatter: " << id;

            const auto artefact(fmt.format(ctx, e));
            const auto& p(artefact.path());

            BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
            r.push_front(artefact);
        } else if (fs == formatting_styles::wale) {
            BOOST_LOG_SEV(lg, debug) << "Using the wale formatter.";

            wale_formatter f;
            const auto artefact(f.format(fmt, ctx, e));
            const auto& p(artefact.path());

            BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
            r.push_front(artefact);
        } else if (fs == formatting_styles::stitch) {
            BOOST_LOG_SEV(lg, debug) << "Using the stitch formatter.";

            const auto artefact(stitch_formatter_.format(fmt, ctx, e));
            const auto& p(artefact.path());

            BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
            r.push_front(artefact);
        } else {
            BOOST_LOG_SEV(lg, error) << invalid_formatting_style << fs;
            BOOST_THROW_EXCEPTION(formatting_error(invalid_formatting_style));
        }
    }
    return r;
}

std::list<coding::meta_model::artefact> workflow::
execute(const std::unordered_set<coding::meta_model::element_archetype>&
    enabled_archetype_for_element, const formattables::model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started formatting. Model " << fm.name().id();
    std::list<coding::meta_model::artefact> r;
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& eprops(formattable.element_properties());
        for (const auto& segment : formattable.all_segments()) {
            const auto& e(*segment);
            r.splice(r.end(),
                format(enabled_archetype_for_element, fm, e, eprops));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished formatting.";
    return r;
}

}
