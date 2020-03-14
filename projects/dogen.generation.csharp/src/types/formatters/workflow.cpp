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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.generation.csharp/types/formatters/context.hpp"
#include "dogen.generation.csharp/types/formatters/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.csharp.formatters.workflow"));

}

namespace dogen::generation::csharp::formatters {

std::shared_ptr<csharp::formatters::registrar> workflow::registrar_;

workflow::workflow() {
    registrar().validate();
}

csharp::formatters::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<csharp::formatters::registrar>();

    return *registrar_;
}

std::list<extraction::meta_model::artefact>
workflow::execute(const formattables::model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started formatting. Model "
                             << fm.name().qualified().dot();

    std::list<extraction::meta_model::artefact> r;
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);

        const auto& e(*formattable.element());
        const auto id(e.name().qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        const auto mn(e.meta_name().qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Meta name: " << mn;

        const auto& frp(registrar().formatter_repository());
        const auto i(frp.stock_artefact_formatters_by_meta_name().find(mn));
        if (i == frp.stock_artefact_formatters_by_meta_name().end()) {
            BOOST_LOG_SEV(lg, debug) << "No formatters for meta name: " << mn;
            return r;
        }

        const auto& eprops(formattable.element_properties());
        const auto& hlp_fmts(frp.helper_formatters());
        const context ctx(eprops, fm, hlp_fmts);
        const auto& fmts(i->second);
        for (const auto& fmt_ptr : fmts) {
            const auto& fmt(*fmt_ptr);
            BOOST_LOG_SEV(lg, debug) << "Using formatter: " << fmt.id();

            const auto artefact(fmt.format(ctx, e));
            const auto& p(artefact.path());

            BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
            r.push_back(artefact);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished formatting.";
    return r;
}

}
