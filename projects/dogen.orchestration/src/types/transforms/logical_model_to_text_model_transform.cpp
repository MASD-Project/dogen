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
#include "dogen.logical/io/entities/output_model_set_io.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.text/io/entities/model_set_io.hpp"
#include "dogen.orchestration/types/helpers/logical_to_physical_projector.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/logical_model_to_text_model_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.logical_model_to_text_model_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::orchestration::transforms {

text::entities::model
logical_model_to_text_model_transform::apply(
    const text::transforms::context& ctx, const logical::entities::model& lm) {
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

    helpers::logical_to_physical_projector p;
    r.logical_physical_regions(p.project(*ctx.physical_meta_model(), lm));

    return r;
}

text::entities::model_set logical_model_to_text_model_transform::
apply(const text::transforms::context& ctx,
    const logical::entities::output_model_set& loms) {
    tracing::scoped_transform_tracer stp(lg,
        "logical model to text model transform",
        transform_id, loms.name().qualified().dot(), *ctx.tracer(), loms);

    text::entities::model_set r;
    for(const auto& lm : loms.models())
        r.models().push_back(apply(ctx, lm));

    stp.end_transform(r);
    return r;
}

}
