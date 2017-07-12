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
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/external_transforms_chain.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.external_transforms_chain"));

}

namespace dogen {
namespace yarn {
namespace transforms {

std::shared_ptr<external_transform_registrar>
external_transforms_chain::registrar_;

external_transform_registrar& external_transforms_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<external_transform_registrar>();

    return *registrar_;
}

dogen::formatters::repository external_transforms_chain::
create_formatters_decoration_repository(
    const std::vector<boost::filesystem::path>& data_directories) {
    dogen::formatters::repository_factory hw;
    return hw.make(data_directories);
}

dogen::formatters::decoration_properties_factory
external_transforms_chain::create_decoration_properties_factory(
    const annotations::type_repository& atrp,
    const dogen::formatters::repository& frp,
    const annotations::annotation& ra) {
    using dogen::formatters::decoration_properties_factory;
    decoration_properties_factory r(atrp, frp, ra);
    return r;
}

void external_transforms_chain::
transform(const context& ctx, meta_model::intermediate_model& im) {
    const auto id(im.name().id());
    BOOST_LOG_SEV(lg, debug) << "Performing external transforms on: " << id;

    auto& rg(registrar());
    rg.validate();

    const auto& dirs(ctx.data_directories());
    const auto& ra(im.root_module().annotation());
    const auto& atrp(ctx.type_repository());
    const auto drp(create_formatters_decoration_repository(dirs));
    const auto dpf(create_decoration_properties_factory(atrp, drp, ra));

    for (const auto& et : rg.external_transforms())
        et->transform(ctx, dpf, im);

    BOOST_LOG_SEV(lg, debug) << "Finished performing external transforms.";
}

} } }
