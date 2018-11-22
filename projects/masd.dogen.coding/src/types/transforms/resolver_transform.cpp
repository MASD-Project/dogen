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
#include "masd.dogen.modeling/types/helpers/resolver.hpp"
#include "masd.dogen.modeling/io/meta_model/endomodel_io.hpp"
#include "masd.dogen.modeling/types/transforms/resolver_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.resolver_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::modeling::transforms {

void resolver_transform::transform(const context& ctx,
    const helpers::indices& idx, meta_model::endomodel& em) {
    probing::scoped_transform_prober stp(lg, "resolver transform",
        transform_id, em.name().id(), ctx.prober(), em);
    helpers::resolver::resolve(idx, em);
    stp.end_transform(em);
}

}
