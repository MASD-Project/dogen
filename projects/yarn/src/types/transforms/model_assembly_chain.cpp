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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/mapper.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/model_assembly_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.model_assembly_chain"));

}

namespace dogen {
namespace yarn {
namespace transforms {

model model_assembly_chain::transform(const context& ctx, const languages l,
    const std::list<intermediate_model>& ims) {

    const mapper mp(ctx.mapping_repository());
    for (const auto& im : ims) {
        const auto mm(mp.map(im.input_language(), l, im));
    }

    model r;
    return r;

}

} } }
