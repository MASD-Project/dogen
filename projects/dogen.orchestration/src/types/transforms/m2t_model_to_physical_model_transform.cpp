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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.m2t/io/entities/model_io.hpp"
#include "dogen.orchestration/types/transforms/m2t_model_to_physical_model_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.m2t_model_to_physical_model_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::orchestration::transforms {

std::list<physical::entities::model>
m2t_model_to_physical_model_transform::apply(const m2t::transforms::context& ctx,
    const std::list<m2t::entities::model>& ms) {
    tracing::scoped_transform_tracer stp(lg, "logical to m2t model transform",
        transform_id, *ctx.tracer(), ms);

    std::list<physical::entities::model> r;
    for (const auto& m : ms) {
        physical::entities::model pm;
        pm.logical_name().simple(m.name().simple());
        pm.logical_name().qualified(m.name().qualified().dot());
        pm.origin_sha1_hash(m.origin_sha1_hash());
        pm.name().simple(m.name().simple());
        pm.name().qualified(m.name().qualified().dot());
        pm.configuration(m.root_module()->configuration());
        pm.managed_directories(m.managed_directories());

        for (const auto& element : m.elements()) {
            for (const auto& pair : element.artefacts()) {
                const auto aptr(pair.second);
                /*
                 * FIXME: mega-hack: prune empty artefacts. This is
                 * needed for now because of how stitch templates are
                 * handled; if we do not have a template, we are
                 * producing blank artefacts with empty path and
                 * contents. This will be addressed with T2T
                 * transforms.
                 */
                const auto& p(aptr->name().qualified());
                if (!p.empty())
                    pm.artefacts().push_back(aptr);
            }
        }
        r.push_back(pm);
    }

    return r;
}

}
