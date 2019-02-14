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
#include "masd.dogen.extraction/types/repository_factory.hpp"
#include "masd.dogen.extraction/types/decoration_properties_factory.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/dynamic_transforms_chain.hpp"

namespace {

const std::string transform_id("coding.transforms.dynamic_transforms_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::coding::transforms {

std::shared_ptr<dynamic_transform_registrar>
dynamic_transforms_chain::registrar_;

dynamic_transform_registrar& dynamic_transforms_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<dynamic_transform_registrar>();

    return *registrar_;
}

dogen::extraction::decoration_properties_factory
dynamic_transforms_chain::create_decoration_properties_factory(
    const context& ctx, const annotations::annotation& ra) {
    using masd::dogen::extraction::decoration_properties_factory;
    decoration_properties_factory
        r(ctx.type_repository(), ctx.formatting_repository(), ra);
    return r;
}

void dynamic_transforms_chain::
transform(const context& ctx, meta_model::model& m) {
    tracing::scoped_chain_tracer stp(lg, "dynamic transforms chain",
        transform_id, m.name().id(), ctx.tracer(), m);

    auto& rg(registrar());
    rg.validate();

    const auto& ra(m.root_module()->annotation());
    const auto dpf(create_decoration_properties_factory(ctx, ra));
    for (const auto& dt : rg.dynamic_transforms())
        dt->transform(ctx, dpf, m);

    stp.end_chain(m);
}

}
