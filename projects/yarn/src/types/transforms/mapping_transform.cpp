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
#include "dogen/probing/types/scoped_prober.hpp"
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/types/helpers/mapper.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/mapping_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.mapping_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen {
namespace yarn {
namespace transforms {

bool mapping_transform::is_mappable(const meta_model::languages from,
    const meta_model::languages to) {
    return helpers::mapper::is_mappable(from, to);
}

meta_model::endomodel mapping_transform::transform(const context& ctx,
    const meta_model::endomodel& src, const meta_model::languages to) {
    probing::scoped_transform_prober stp(lg, "mapping transform",
        transform_id, src.name().id(), ctx.new_prober(), src);

    const helpers::mapper mp(ctx.mapping_repository());
    auto r(mp.map(src.input_language(), to, src));

    stp.end_transform(r);
    return r;
}

} } }
