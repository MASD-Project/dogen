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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.injection/types/transforms/model_set_production_chain.hpp"
#include "masd.dogen.coding/types/transforms/model_generation_chain.hpp"
#include "masd.dogen.generation/types/transforms/model_generation_chain.hpp"
#include "masd.dogen.generation/types/transforms/model_to_extraction_model_chain.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/types/helpers/filesystem_writer.hpp"
#include "masd.dogen.extraction/types/helpers/file_linter.hpp"
#include "masd.dogen.orchestration/types/transforms/context.hpp"
#include "masd.dogen.orchestration/types/transforms/code_generation_chain.hpp"

#define NEW_WORLD 1

namespace {

const std::string
transform_id("orchestration.transforms.code_generation_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::orchestration::transforms {

void code_generation_chain::write(const extraction::meta_model::model& m) {

    if (m.artefacts().empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, so no output.";
        return;
    }

    const auto& w = extraction::helpers::filesystem_writer();
    if (m.force_write())
        w.force_write(m.artefacts());
    else
        w.write(m.artefacts());
}

void code_generation_chain::lint(const extraction::meta_model::model& m) {
    /*
     * If we're not going to delete the files, don't bother linting..
     */
    if (!m.delete_extra_files())
        return;

    const auto lint(extraction::helpers::file_linter::lint(m));
    if (lint.empty())
        return;

    utility::filesystem::remove(lint);
}

void code_generation_chain::transform(const context& ctx) {
    BOOST_LOG_SEV(lg, info) << "Starting code generation.";

    const auto& o(ctx.coding_context().transform_options());
    const auto model_name(o.target().filename().string());
    const auto& tracer(*ctx.injection_context().tracer());
    tracing::scoped_chain_tracer stp(lg, "code generation chain",
        transform_id, model_name, tracer);

    const auto& to(ctx.coding_context().transform_options());
    BOOST_LOG_SEV(lg, debug) << "Target: " << to.target().generic();

    /*
     * Obtain the injection model set.
     */
    using injection::transforms::model_set_production_chain;
#ifndef NEW_WORLD
    model_set_production_chain::transform(ctx.injection_context(),
        ctx.coding_context().transform_options().target());
#else
    const auto ims(model_set_production_chain::transform(
            ctx.injection_context(),
            ctx.coding_context().transform_options().target()));
#endif

    /*
     * Obtain the coding models.
     */
#ifndef NEW_WORLD
    const auto cms(coding::transforms::model_generation_chain::transform(
            ctx.coding_context()));
#else
    const auto cms(coding::transforms::model_generation_chain::transform(
            ctx.coding_context(), ims));
#endif

    /*
     * Obtain the generation models.
     */
    const auto gms(
        generation::transforms::model_generation_chain::transform(
            ctx.generation_context(), cms));

    /*
     * Obtain the extraction models.
     */
    using generation::transforms::model_to_extraction_model_chain;
    const auto m(model_to_extraction_model_chain::transform(
            ctx.generation_context(), gms));

    /*
     * Write the artefacts.
     */
    write(m);

    /*
     * Perform any housekeeping if need be.
     */
    lint(m);
    stp.end_chain(m);

    BOOST_LOG_SEV(lg, info) << "Finished code generation.";
}

}
