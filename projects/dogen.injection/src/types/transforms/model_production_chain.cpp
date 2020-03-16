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
#include "dogen.injection/io/entities/model_io.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.injection/types/transforms/compute_sha1_transform.hpp"
#include "dogen.injection/types/transforms/input_technical_space_transform.hpp"
#include "dogen.injection/types/transforms/references_transform.hpp"
#include "dogen.injection/types/transforms/configuration_transform.hpp"
#include "dogen.injection/types/transforms/tagged_values_overrides_transform.hpp"
#include "dogen.injection/types/transforms/model_production_chain.hpp"

namespace {

const std::string transform_id("injection.transforms.model_production_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::injection::transforms {

std::shared_ptr<registrar> model_production_chain::registrar_;

decoding_transform&
model_production_chain::transform_for_model(const boost::filesystem::path& p) {
    /*
     * Ensure the registrar is in a valid state before we proceed.
     */
    auto& rg(registrar());
    rg.validate();
    return rg.decoding_transform_for_path(p);
}

transforms::registrar& model_production_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<transforms::registrar>();

    return *registrar_;
}

entities::model model_production_chain::
apply(const context& ctx, const boost::filesystem::path& p) {
    const auto model_name(p.stem().generic_string());
    tracing::scoped_chain_tracer stp(lg, "injection model production chain",
        transform_id, model_name, *ctx.tracer());
    /*
     * Transform the external model in whatever supported external
     * representation it may be in - Dia, JSON, etc - into the
     * internal representation of an injection model.
     */
    auto& t(transform_for_model(p));
    auto r(t.apply(ctx, p));

    /*
     * Update the SHA1 hash.
     */
    compute_sha1_transform::apply(ctx, p, r);

    /*
     * Process the variability overrides.
     */
    tagged_values_overrides_transform::apply(ctx, r);

    /*
     * Process the configuration
     */
    configuration_transform::apply(ctx, r);

    /*
     * Read the input technical space.
     */
    input_technical_space_transform::apply(ctx, r);

    /*
     * Read the model references.
     */
    references_transform::apply(ctx, r);

    stp.end_chain(r);
    return r;
}

}
