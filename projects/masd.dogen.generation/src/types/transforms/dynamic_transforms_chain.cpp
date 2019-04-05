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
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.generation/io/meta_model/model_io.hpp"
#include "masd.dogen.generation/types/transforms/context.hpp"
#include "masd.dogen.generation/types/transforms/dynamic_transforms_chain.hpp"

namespace {

const std::string
transform_id("generation.transforms.dynamic_transforms_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::generation::transforms {

std::shared_ptr<dynamic_transform_registrar>
dynamic_transforms_chain::registrar_;

dynamic_transform_registrar& dynamic_transforms_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<dynamic_transform_registrar>();

    return *registrar_;
}

void dynamic_transforms_chain::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_chain_tracer stp(lg, "dynamic transforms chain",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    auto& rg(registrar());
    rg.validate();

    for (const auto& dt : rg.dynamic_transforms())
        dt->apply(ctx, m);

    stp.end_chain(m);
}

}
