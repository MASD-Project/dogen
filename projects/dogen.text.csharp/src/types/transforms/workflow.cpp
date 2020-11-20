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
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.text.csharp/types/workflow_error.hpp"
#include "dogen.text.csharp/types/transforms/context.hpp"
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
workflow::get_artefact(const std::unordered_map<
    identification::entities::physical_meta_id,
    boost::shared_ptr<physical::entities::artefact>>& artefacts,
    const identification::entities::physical_meta_id& archetype) const {

    const auto i(artefacts.find(archetype));
    if (i == artefacts.end()) {
        BOOST_LOG_SEV(lg, error) << archetype_not_found << archetype;
        BOOST_THROW_EXCEPTION(
            workflow_error(archetype_not_found + archetype.value()));
    }
    return i->second;
}

void workflow::execute(boost::shared_ptr<tracing::tracer> tracer,
    const std::unordered_map<identification::entities::logical_id,
    logical::entities::aspect_properties>& aspect_properties,
    const std::unordered_map<identification::entities::logical_id,
    logical::entities::assistant_properties>& assistant_properties,
    const formattables::model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started formatting. Model "
                             << fm.name().qualified().dot();

    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);

        const auto& e(*formattable.element());
        const auto id(e.name().qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        const auto mn(e.meta_name().id());
        BOOST_LOG_SEV(lg, debug) << "Meta name: " << mn;

        const auto& frp(registrar().formatter_repository());
        const auto i(frp.stock_artefact_formatters_by_meta_name().find(mn));
        if (i == frp.stock_artefact_formatters_by_meta_name().end()) {
            BOOST_LOG_SEV(lg, debug) << "No formatters for meta name: " << mn;
        }

        const auto& hlp_fmts(frp.helper_formatters());
        const context ctx(aspect_properties, assistant_properties, fm, hlp_fmts,
            tracer);
        const auto& fmts(i->second);
        for (const auto& fmt_ptr : fmts) {
            const auto& fmt(*fmt_ptr);
            const auto pmn(fmt.archetype().meta_name());
            const auto arch(pmn.id());
            auto aptr(get_artefact(
                    formattable.artefacts().artefacts_by_archetype(), arch));

            BOOST_LOG_SEV(lg, debug) << "Using formatter: "
                                     << fmt.archetype().meta_name().id().value();

            auto& a(*aptr);
            fmt.apply(ctx, e, a);
            const auto& p(a.file_path());
            BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished formatting.";
}

}
