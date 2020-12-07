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
#include <boost/lexical_cast.hpp>
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/model_to_text_chain.hpp"

namespace {

const std::string transform_id("text.transforms.model_to_text_chain");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string unsupported_technical_space(
    "Could not find transform for technical space: ");
const std::string disabled_transform(
    "Transform for requested technical space is disabled: ");
const std::string archetype_not_found("Archetype not found: ");

}

namespace dogen::text::transforms {

transforms::text_transform_registrar
model_to_text_chain::text_transform_registrar_;

transforms::text_transform_registrar&
model_to_text_chain::text_transform_registrar() {
    return text_transform_registrar_;
}

boost::shared_ptr<physical::entities::artefact>
model_to_text_chain::get_artefact(const physical::entities::region& region,
    const identification::entities::physical_meta_id& archetype) {

    const auto& aba(region.artefacts_by_archetype());
    const auto i(aba.find(archetype));
    if (i == aba.end()) {
        BOOST_LOG_SEV(lg, error) << archetype_not_found << archetype;
        BOOST_THROW_EXCEPTION(
            transformation_error(archetype_not_found + archetype.value()));
    }
    return i->second;
}

void model_to_text_chain::
apply(const text::transforms::context& ctx, text::entities::model& lps) {
    for (auto& region : lps.logical_physical_regions()) {
        const auto& e(*region.logical_element());
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        const auto mn(e.meta_name().id());
        BOOST_LOG_SEV(lg, debug) << "Meta name: " << mn;

        const auto& rp(text_transform_registrar().repository());
        const auto& m2tts_by_mn(rp.model_to_text_transforms_by_meta_name());
        const auto i(m2tts_by_mn.find(mn));
        if (i == m2tts_by_mn.end()) {
            BOOST_LOG_SEV(lg, debug) << "No text transforms for meta name: "
                                     << mn;
            continue;
        }

        const auto& mmp(lps.physical().meta_model_properties());
        const auto& ppp(mmp.project_path_properties());
        const auto templates_directory(ppp.templates_directory_full_path());

        const auto& m2tts(i->second);
        for (const auto& ptr : m2tts) {
            const auto& m2t(*ptr);
            const auto pmn(m2t.archetype().meta_name());

            /*
             * Ensure the transform for the requested technical space is
             * marked as enabled. If it is disabled, the user has requested
             * conflicting options - output on technical_space X but disable
             * backend for technical space X - so we need to throw to let the
             * user know.
             */
            using identification::helpers::physical_meta_id_builder;
            const auto beid(physical_meta_id_builder::build_backend(pmn));
            const auto& ek(mmp.enabled_backends());
            const auto is_enabled(ek.find(beid) != ek.end());
            if (!is_enabled)
                continue;

            const auto arch(pmn.id());
            BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << arch;

            auto aptr(get_artefact(region.physical_region(), arch));
            if (!aptr->enablement_properties().enabled()) {
                BOOST_LOG_SEV(lg, debug) << "Archetype is disabled.";
                continue;
            }
            BOOST_LOG_SEV(lg, debug) << "Archetype is enabled.";

            auto& a(*aptr);
            m2t.apply(ctx, lps, e, a);
            const auto& p(aptr->file_path());
            BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
        }
    }
}

}
