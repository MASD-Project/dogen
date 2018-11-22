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
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.probing/types/scoped_prober.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/model_generation_chain.hpp"

namespace {

const std::string transform_id("injection.transforms.model_generation_chain");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::injection::transforms {

std::shared_ptr<registrar> model_generation_chain::registrar_;

decoding_transform_interface& model_generation_chain::
transform_for_model(const boost::filesystem::path& p) {
    /*
     * Ensure the registrar is in a valid state before we proceed.
     */
    auto& rg(registrar());
    rg.validate();
    return rg.decoding_transform_for_path(p);
}

transforms::registrar& model_generation_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<transforms::registrar>();

    return *registrar_;
}

meta_model::model model_generation_chain::
transform(const context& ctx, const boost::filesystem::path& p) {
    const auto model_name(p.filename().generic_string());
    probing::scoped_chain_prober stp(lg, "injection model generation chain",
        transform_id, model_name, ctx.prober());

    /*
     * Transform the exogenous model - in whatever supported exogenous
     * representation it may be in, Dia, JSON, etc - into the internal
     * representation of an exogenous model.
     */
    auto& t(transform_for_model(p));
    auto r(t.transform(ctx, p));
    stp.end_chain(r);
    return r;
}

}
