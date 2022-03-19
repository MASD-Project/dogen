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
#include "dogen.orchestration/types/transforms/code_generation_chain.hpp"
#include "dogen.orchestration/types/transforms/context_bootstrapping_chain.hpp"
#include "dogen.orchestration/types/generator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("orchestration.generator"));

const std::string generation_activity("generation");

}

namespace dogen::orchestration {

void generator::generate(const configuration& cfg,
    const boost::filesystem::path& target,
    const std::vector<boost::filesystem::path>& reference_directories,
    const boost::filesystem::path& output_directory) const {

    BOOST_LOG_SEV(lg, debug) << "Started generation.";

    {
        /*
         * Bootstrap the top-level context.
         */
        using cbc = transforms::context_bootstrapping_chain;
        const auto& od(output_directory);
        const auto& a(generation_activity);
        const auto& rds(reference_directories);
        const auto ctx(cbc::bootstrap_full_context(cfg, a, rds, od));

        /*
         * Bind the tracer to the current scope.
         */
        tracing::scoped_tracer st(*ctx.codec_context().tracer());

        /*
         * Apply the code generation chain.
         */
        transforms::code_generation_chain::apply(ctx, target);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generation.";
}

}
