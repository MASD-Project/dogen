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
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/types/entities/logical_provenance.hpp"
#include "dogen.identification/io/entities/physical_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/physical_id_factory.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/region.hpp"
#include "dogen.text/io/entities/model_set_io.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/text_model_to_physical_model_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.text_model_to_physical_model_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty_path("Artefact has an empty path. ID: ");
const std::string duplicate_archetype(
    "Found more than one artefact for archetype:");
const std::string duplicate_logical_element(
    "Found more than one artefact set for logical model ID: ");

}

namespace dogen::orchestration::transforms {

physical::entities::model_set text_model_to_physical_model_transform::
apply(const text::transforms::context& ctx,
    const text::entities::model_set& ms) {
    const auto id(ms.provenance().logical_name().id());
    tracing::scoped_transform_tracer stp(lg, "logical to text model",
        transform_id, id.value(), *ctx.tracer(), ms);

    /*
     * FIXME: this code is still required because we are filtering out
     * empty paths. This needs to be investigated.
     */
    physical::entities::model_set r;
    for (const auto& m : ms.models()) {
        /*
         * Update the main model properties.
         */
        physical::entities::model pm;
        pm.configuration(m.logical().root_module()->configuration());
        pm.name().simple(m.logical().name().simple());
        pm.managed_directories(m.physical().managed_directories());
        pm.provenance(ms.provenance());

        identification::helpers::physical_id_factory f;
        using namespace identification::entities;
        logical_id id(m.logical().name().id());
        pm.name().id(f.make(id, m.logical().output_technical_spaces().front()));

        /*
         * Obtain artefact sets from the text model.
         */
        for (const auto& regions : m.logical_physical_regions()) {
            const auto& e(*regions.logical_element());
            physical::entities::region pr;
            const auto& artefacts(regions.physical_region());
            pr.provenance(artefacts.provenance());

            for (const auto& pair : artefacts.artefacts_by_archetype()) {
                const auto archetype_id(pair.first);
                const auto aptr(pair.second);

                /*
                 * FIXME: we are still generating artefacts for global
                 * module.
                 */
                if (aptr->file_path().empty()) {
                    BOOST_LOG_SEV(lg, error) << empty_path
                                             << aptr->name().id();
                    // BOOST_THROW_EXCEPTION(transform_exception(empty_path +
                    //         aptr->name().id().value()));
                    continue;
                }

                auto& aba(pr.artefacts_by_archetype());
                const auto aa_pair(std::make_pair(archetype_id, aptr));
                const bool inserted(aba.insert(aa_pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_archetype
                                             << archetype_id;
                    BOOST_THROW_EXCEPTION(transform_exception(
                            duplicate_archetype + archetype_id.value()));
                }
            }

            if (!pr.artefacts_by_archetype().empty()) {
                auto& asbli(pm.regions_by_logical_id());
                const auto& leid(e.name().qualified().dot());
                auto pair(std::make_pair(leid, pr));
                const bool inserted(asbli.insert(pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_logical_element
                                             << leid;
                    BOOST_THROW_EXCEPTION(transform_exception(
                            duplicate_logical_element + leid));
                }
            }
        }
        r.models().push_back(pm);
    }
    return r;
}

}
