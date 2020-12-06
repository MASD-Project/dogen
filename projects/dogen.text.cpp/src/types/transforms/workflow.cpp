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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.text.cpp/types/workflow_error.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.transforms.workflow"));

const std::string archetype_not_found("Archetype not found: ");

}

namespace dogen::text::cpp::transforms {

std::shared_ptr<cpp::transforms::registrar> workflow::registrar_;

workflow::workflow(const physical::entities::model& pm)
    : physical_model_(pm) { }

cpp::transforms::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::transforms::registrar>();

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
    const text::entities::model& m,
    text::entities::logical_physical_region& region) const {

    const auto& e(*region.logical_element());
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

    const auto mn(e.meta_name().id());
    BOOST_LOG_SEV(lg, debug) << "Meta name: " << mn;

    const auto& frp(registrar().formatter_repository());
    const auto i(frp.stock_artefact_formatters_by_meta_name().find(mn));
    if (i == frp.stock_artefact_formatters_by_meta_name().end()) {
        BOOST_LOG_SEV(lg, debug) << "No formatters for meta name: " << mn;
        return;
    }

    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    const auto templates_directory(ppp.templates_directory_full_path());

    const auto& fmts(i->second);
    for (const auto& ptr : fmts) {
        const auto& fmt(*ptr);
        const auto pn(fmt.archetype().meta_name());
        const auto arch(pn.id());
        auto aptr(get_artefact(region.physical_region(), arch));
        if (!aptr->enablement_properties().enabled()) {
            BOOST_LOG_SEV(lg, debug) << "Archetype is disabled: " << arch;
            continue;
        }
        BOOST_LOG_SEV(lg, debug) << "Archetype is enabled: " << arch;

        auto& a(*aptr);
        const auto id(fmt.archetype().meta_name().id().value());
        fmt.apply(ctx, m, e, a);
        const auto& p(aptr->file_path());
        BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
    }
}

void workflow::execute(const text::transforms::context& ctx,
    text::entities::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started formatting. Model "
                             << m.provenance().logical_name().id();

    for (auto& region : m.logical_physical_regions())
        execute(ctx, m, region);

    BOOST_LOG_SEV(lg, debug) << "Finished formatting.";
}

}
