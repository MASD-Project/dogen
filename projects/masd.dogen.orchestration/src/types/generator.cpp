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
#include "masd.dogen.coding/types/transforms/options.hpp"
#include "masd.dogen.coding/types/transforms/context_factory.hpp"
#include "masd.dogen.coding/types/transforms/code_generation_chain.hpp"
#include "masd.dogen.orchestration/types/generator.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("orchestration.generator"));

using masd::dogen::coding::transforms::options;
options make_options(const masd::dogen::configuration& cfg,
    const boost::filesystem::path& target,
    const boost::filesystem::path& output_directory,
    const boost::filesystem::path& tracing_output_directory) {
    options r;

    r.target(target);
    r.output_directory_path(output_directory);

    if (cfg.error_handling()) {
        const auto& eh(*cfg.error_handling());
        r.compatibility_mode(eh.compatibility_mode_enabled());
    }

    if (cfg.tracing()) {
        r.tracing(cfg.tracing());
        r.probe_directory(tracing_output_directory);
    }

    return r;
}

}

namespace masd::dogen::orchestration {

void generator::generate(const configuration& cfg,
    const boost::filesystem::path& target,
    const boost::filesystem::path& output_directory,
    const boost::filesystem::path& tracing_output_directory) const {
    BOOST_LOG_SEV(lg, debug) << "Started generation.";

    const auto o(make_options(cfg, target, output_directory,
            tracing_output_directory));

    using namespace coding::transforms;
    const auto ctx(context_factory::make(o));
    code_generation_chain::transform(ctx);

    BOOST_LOG_SEV(lg, debug) << "Finished generation.";
}

}
