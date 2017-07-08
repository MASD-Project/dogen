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
#include "dogen/yarn/types/transforms/merge_transform.hpp"
#include "dogen/yarn/types/transforms/model_assembly_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.model_assembly_chain"));

}

namespace dogen {
namespace yarn {
namespace transforms {

intermediate_model model_assembly_chain::obtain_merged_model(const context& ctx,
    const languages l, const intermediate_model& target,
    const std::list<intermediate_model>& refs) {

    const mapper mp(ctx.mapping_repository());
    const auto mapped_target(mp.map(target.input_language(), l, target));

    std::list<intermediate_model> mapped_refs;
    for (const auto& ref : refs)
        mapped_refs.push_back(mp.map(ref.input_language(), l, ref));

    return merge_transform::transform(mapped_target, mapped_refs);
}

model model_assembly_chain::transform(const context& ctx, const languages l,
    const intermediate_model& target,
    const std::list<intermediate_model>& refs) {

    auto mm(obtain_merged_model(ctx, l , target, refs));

    model r;
    return r;

}

} } }
