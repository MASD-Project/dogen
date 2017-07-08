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

void external_transforms_chain::
transform(const context& ctx, intermediate_model& im) {
    const auto id(im.name().id());
    BOOST_LOG_SEV(lg, debug) << "Performing external transforms on: " << id;

    auto& rg(registrar());
    rg.validate();

    for (const auto& et : rg.external_transforms())
        et->transform(ctx, im);

    BOOST_LOG_SEV(lg, debug) << "Finished performing external transforms.";
}

} } }
