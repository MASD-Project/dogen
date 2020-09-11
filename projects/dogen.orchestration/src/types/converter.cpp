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
#include "dogen.codec.json/types/initializer.hpp"
#include "dogen.codec.dia/types/initializer.hpp"
#include "dogen.codec/types/transforms/model_to_model_chain.hpp"
#include "dogen.orchestration/types/transforms/context_bootstrapping_chain.hpp"
#include "dogen.orchestration/types/converter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("orchestration.converter"));

const std::string conversion_activity("conversion");

}

namespace dogen::orchestration {

void converter::convert(const configuration& cfg,
    const boost::filesystem::path& source,
    const boost::filesystem::path& destination) const {
    BOOST_LOG_SEV(lg, debug) << "Started conversion.";

    {
        /*
         * Bootstrap the codec context.
         */
        using namespace transforms;
        using cbc = context_bootstrapping_chain;
        const auto& a(conversion_activity);
        const auto ctx(cbc::bootstrap_codec_context(cfg, a));

        /*
         * Bind the tracer to the current scope.
         */
        const auto& t(*ctx.tracer());
        tracing::scoped_tracer st(t);

        /*
         * Apply the code generation chain.
         */
        using namespace dogen::codec::transforms;
        model_to_model_chain::apply(ctx, source, destination);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished conversion.";
}

}
