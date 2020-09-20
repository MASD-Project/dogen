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

}

namespace dogen::orchestration::transforms {

physical::entities::model_set text_model_to_physical_model_transform::
apply(const text::transforms::context& ctx,
    const text::entities::model_set& tms) {
    const auto id(tms.provenance().logical_name().id());
    tracing::scoped_transform_tracer stp(lg, "logical to text model",
        transform_id, id.value(), *ctx.tracer(), tms);

    /*
     * Extract the physical models from the text model.
     */
    physical::entities::model_set r;
    for (const auto& tm : tms.models())
        r.models().push_back(tm.physical());

    return r;
}

}
