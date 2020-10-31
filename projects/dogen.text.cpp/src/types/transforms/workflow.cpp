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
#include "dogen.text.cpp/types/workflow_error.hpp"
#include "dogen.physical/io/entities/formatting_styles_io.hpp"
#include "dogen.text.cpp/types/transforms/context.hpp"
#include "dogen.text.cpp/types/transforms/wale_transform.hpp"
#include "dogen.text.cpp/types/transforms/stitch_transform.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.transforms.workflow"));

const std::string archetype_not_found("Archetype not found: ");
const std::string invalid_formatting_style("Invalid formatting style");

}

namespace dogen::text::cpp::transforms {

std::shared_ptr<cpp::transforms::registrar> workflow::registrar_;

workflow::workflow(const physical::entities::model& pm,
    const variability::entities::feature_model& fm,
    const variability::helpers::configuration_factory& cf,
    const std::unordered_map<identification::entities::logical_id,
    logical::entities::streaming_properties>&
    streaming_properties)
    : physical_model_(pm), feature_model_(fm), configuration_factory_(cf),
      streaming_properties_(streaming_properties) { }

cpp::transforms::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::transforms::registrar>();

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
    const formattables::model& fm, formattables::formattable& fbl) const {

    const auto& e(*fbl.element());
    const auto id(e.name().qualified().dot());
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

    const auto& ep(fbl.element_properties());
    const auto& fmts(i->second);
    for (const auto& ptr : fmts) {
        const auto& fmt(*ptr);
        const auto pn(fmt.archetype().meta_name());
        const auto arch(pn.id());
        auto aptr(get_artefact(fbl.artefacts().artefacts_by_archetype(), arch));
        if (!aptr->enablement_properties().enabled()) {
            BOOST_LOG_SEV(lg, debug) << "Archetype is disabled: " << arch;
            continue;
        }
        BOOST_LOG_SEV(lg, debug) << "Archetype is enabled: " << arch;

        using physical::entities::formatting_styles;
        const auto& frp(registrar().formatter_repository());
        context ctx(ep, physical_model_, fm, frp.helper_formatters(),
            streaming_properties_, tracer);

        auto& a(*aptr);
        const auto fs(aptr->formatting_style());
        if (fs == formatting_styles::stock) {
             const auto id(fmt.archetype().meta_name().id().value());
             BOOST_LOG_SEV(lg, debug) << "Using the stock formatter: " << id;
             fmt.apply(ctx, e, a);

             const auto& p(aptr->file_path());
             BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
         } else if (fs == formatting_styles::wale) {
             BOOST_LOG_SEV(lg, debug) << "Using the wale formatter.";
             wale_transform f;
             f.apply(templates_directory, fmt, ctx, e, a);

             const auto& p(aptr->file_path());
             BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
         } else if (fs == formatting_styles::stitch) {
             BOOST_LOG_SEV(lg, debug) << "Using the stitch formatter.";
             stitch_transform f(templates_directory, feature_model_,
                 configuration_factory_);
             f.apply(fmt, e, a);

             const auto& p(aptr->file_path());
             BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
             if (!a.content().empty()) {
                 BOOST_LOG_SEV(lg, debug) << "Template has content.";
             } else {
                 BOOST_LOG_SEV(lg, debug) << "Template has no content.";
             }
         } else {
             BOOST_LOG_SEV(lg, error) << invalid_formatting_style << fs;
             BOOST_THROW_EXCEPTION(formatting_error(invalid_formatting_style));
        }
    }
}

void workflow::execute(boost::shared_ptr<tracing::tracer> tracer,
    formattables::model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started formatting. Model "
                             << fm.name().qualified().dot();

    for (auto& pair : fm.formattables()) {
        auto& fbl(pair.second);
        execute(tracer, fm, fbl);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished formatting.";
}

}
