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
#include <unordered_set>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.text/types/entities/logical_physical_region.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"
#include "dogen.identification/types/helpers/physical_id_factory.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.logical/io/entities/output_model_set_io.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/types/transforms/model_population_chain.hpp"
#include "dogen.text/io/entities/model_set_io.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"
#include "dogen.orchestration/types/helpers/logical_to_physical_projector.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/logical_model_to_text_model_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.logical_model_to_text_model_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_id("Duplicate logical name: ");

}

namespace dogen::orchestration::transforms {

physical::entities::model
logical_model_to_text_model_transform::
create_physical_model(const logical::entities::model& lm,
    const identification::entities::logical_provenance& provenance,
    const std::list<text::entities::logical_physical_region>& regions) {

    physical::entities::model r;
    identification::helpers::physical_id_factory f;
    using namespace identification::entities;
    logical_id id(lm.name().id());
    r.name().id(f.make(id, lm.output_technical_spaces().front()));
    r.name().simple(lm.name().simple());
    r.configuration(lm.root_module()->configuration());
    r.provenance(provenance);

    auto& rbli(r.regions_by_logical_id());
    for (const auto& region : regions) {
        const auto lid(region.logical_element()->name().id());
        const auto pair(std::make_pair(lid, region.physical_region()));
        const auto inserted(rbli.insert(pair).second);
        if (inserted)
            continue;

        BOOST_LOG_SEV(lg, error) << duplicate_id << lid;
        BOOST_THROW_EXCEPTION(transform_exception(duplicate_id + lid.value()));
    }
    return r;
}

text::entities::model logical_model_to_text_model_transform::
apply(const context& ctx, const logical::entities::model& lm) {
    /*
     * The logical model can simply be copied across.
     */
    text::entities::model r;
    r.logical(lm);

    /*
     * Create the logical provenance.
     */
    identification::entities::logical_provenance prov;
    prov.logical_name(lm.name());
    prov.codec(lm.provenance());
    prov.logical_meta_name(lm.meta_name());
    r.provenance(prov);

    /*
     * Project logical elements into physical space.
     */
    helpers::logical_to_physical_projector p;
    const auto& pmm(*ctx.text_context().physical_meta_model());
    r.logical_physical_regions(p.project(pmm, lm));

    /*
     * Now create the physical model from these components.
     */
    auto pm(create_physical_model(lm, prov, r.logical_physical_regions()));

    /*
     * Finally, execute the physical model population chain.
     */
    using physical::transforms::model_population_chain;
    model_population_chain::apply(ctx.physical_context(), pm);
    r.physical(pm);

    return r;
}

text::entities::model_set logical_model_to_text_model_transform::
apply(const context& ctx, const logical::entities::output_model_set& loms) {
    const auto id(loms.name().id());
    const auto& tracer(*ctx.text_context().tracer());
    tracing::scoped_transform_tracer stp(lg,
        "logical model to text model transform", transform_id, id.value(),
        tracer, loms);

    text::entities::model_set r;
    for(const auto& lm : loms.models())
        r.models().push_back(apply(ctx, lm));

    stp.end_transform(r);
    return r;
}

}
