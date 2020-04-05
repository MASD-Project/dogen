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
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/transforms/write_artefacts_transform.hpp"
#include "dogen.physical/types/transforms/remove_files_transform.hpp"
#include "dogen.physical/types/transforms/code_generation_chain.hpp"

namespace {

const std::string transform_id("physical.transforms.code_generation_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

void code_generation_chain::
apply(const context& ctx, const entities::model& m) {
    tracing::scoped_chain_tracer stp(lg, "code generation chain",
        transform_id, m.name().simple(), *ctx.tracer(), m);

    /*
     * Write all of the artefacts that require writing.
     */
    write_artefacts_transform::apply(ctx, m);

    /*
     * Remove all of the unexpected files.
     */
    remove_files_transform::apply(ctx, m);
}

}
