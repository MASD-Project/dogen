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
#include "dogen.utility/log/logger.hpp"
#include "dogen.formatters/types/repository_factory.hpp"
#include "dogen.formatters/types/decoration_properties_factory.hpp"
#include "dogen.probing/types/scoped_prober.hpp"
#include "dogen.yarn/types/meta_model/module.hpp"
#include "dogen.yarn/io/meta_model/model_io.hpp"
#include "dogen.yarn/types/transforms/context.hpp"
#include "dogen.yarn/types/transforms/dynamic_transforms_chain.hpp"

namespace {

const std::string transform_id("yarn.transforms.dynamic_transforms_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen {
namespace yarn {
namespace transforms {

std::shared_ptr<dynamic_transform_registrar>
dynamic_transforms_chain::registrar_;

dynamic_transform_registrar& dynamic_transforms_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<dynamic_transform_registrar>();

    return *registrar_;
}

dogen::formatters::decoration_properties_factory
dynamic_transforms_chain::create_decoration_properties_factory(
    const context& ctx, const annotations::annotation& ra) {
    using dogen::formatters::decoration_properties_factory;
    decoration_properties_factory
        r(ctx.type_repository(), ctx.formatters_repository(), ra);
    return r;
}

void dynamic_transforms_chain::
transform(const context& ctx, meta_model::model& m) {
    probing::scoped_chain_prober stp(lg, "dynamic transforms chain",
        transform_id, m.name().id(), ctx.prober(), m);

    auto& rg(registrar());
    rg.validate();

    const auto& ra(m.root_module()->annotation());
    const auto dpf(create_decoration_properties_factory(ctx, ra));
    for (const auto& dt : rg.dynamic_transforms())
        dt->transform(ctx, dpf, m);

    stp.end_chain(m);
}

} } }
