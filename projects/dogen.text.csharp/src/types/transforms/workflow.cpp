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
#include <boost/make_shared.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.text.csharp/types/workflow_error.hpp"
#include "dogen.text.csharp/types/transforms/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.csharp.transforms.workflow"));

const std::string archetype_not_found("Archetype not found: ");

}

namespace dogen::text::csharp::transforms {

std::shared_ptr<csharp::transforms::registrar> workflow::registrar_;

workflow::workflow() {
    registrar().validate();
}

csharp::transforms::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<csharp::transforms::registrar>();

    return *registrar_;
}

boost::shared_ptr<physical::entities::artefact>
workflow::get_artefact(const physical::entities::region& region,
    const identification::entities::physical_meta_id& archetype) const {

    const auto& aba(region.artefacts_by_archetype());
    const auto i(aba.find(archetype));
    if (i == aba.end()) {
        BOOST_LOG_SEV(lg, error) << archetype_not_found << archetype;
        BOOST_THROW_EXCEPTION(
            workflow_error(archetype_not_found + archetype.value()));
    }
    return i->second;
}

void workflow::execute(const text::transforms::context& ctx,
    const text::entities::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started formatting. Model "
                             << m.provenance().logical_name().id();

    for (const auto& region : m.logical_physical_regions()) {
        const auto& e(*region.logical_element());
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        const auto mn(e.meta_name().id());
        BOOST_LOG_SEV(lg, debug) << "Meta ID: " << mn;

        const auto& frp(registrar().formatter_repository());
        const auto i(frp.stock_artefact_formatters_by_meta_name().find(mn));
        if (i == frp.stock_artefact_formatters_by_meta_name().end()) {
            BOOST_LOG_SEV(lg, debug) << "No formatters for meta name: " << mn;
            continue;
        }

        const auto& fmts(i->second);
        for (const auto& fmt_ptr : fmts) {
            const auto& fmt(*fmt_ptr);
            const auto pmn(fmt.archetype().meta_name());
            const auto arch(pmn.id());
            auto aptr(get_artefact(region.physical_region(), arch));

            BOOST_LOG_SEV(lg, debug) << "Using formatter: " << arch;

            auto& a(*aptr);
            fmt.apply(ctx, m, e, a);
            const auto& p(a.file_path());
            BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished formatting.";
}

}
