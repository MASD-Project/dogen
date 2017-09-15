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
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/repository_factory.hpp"
#include "dogen/formatters/types/decoration_properties_factory.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/dynamic_transforms_chain.hpp"

namespace {

const std::string id("yarn.transforms.dynamic_transforms_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(id));

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
transform(const context& ctx, meta_model::endomodel& em) {
    const auto model_id(em.name().id());
    BOOST_LOG_SEV(lg, debug) << "Started dynamic transforms chain. Model: "
                             << model_id;
    ctx.prober().start_transform(id, model_id, em);

    auto& rg(registrar());
    rg.validate();

    const auto& ra(em.root_module()->annotation());
    const auto dpf(create_decoration_properties_factory(ctx, ra));
    for (const auto& dt : rg.dynamic_transforms())
        dt->transform(ctx, dpf, em);

    ctx.prober().end_transform(em);
    BOOST_LOG_SEV(lg, debug) << "Finished dynamic transforms chain.";
}

} } }
