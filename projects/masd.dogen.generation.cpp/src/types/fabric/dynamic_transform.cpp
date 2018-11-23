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
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.coding/io/meta_model/languages_io.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.generation.cpp/types/fabric/injector.hpp"
#include "masd.dogen.generation.cpp/types/fabric/decoration_expander.hpp"
#include "masd.dogen.generation.cpp/types/fabric/dynamic_transform.hpp"

namespace {

const std::string id("generation.cpp.fabric.dynamic_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace masd::dogen::generation::cpp::fabric {

bool dynamic_transform::
requires_expansion(const coding::meta_model::model& m) const {
    const auto l(m.output_language());
    const auto r(l == coding::meta_model::languages::cpp);
    if (!r) {
        BOOST_LOG_SEV(lg, debug) << "Expansion not required: "
                                 << m.name().id() << " for language: " << l;
    }
    return r;
}

void dynamic_transform::expand_injection(
    const annotations::type_repository& atrp,
    coding::meta_model::model& m) const {
    injector i;
    i.inject(atrp, m);
}

void dynamic_transform::expand_decoration(
    const dogen::extraction::decoration_properties_factory& dpf,
    coding::meta_model::model& m) const {
    decoration_expander de;
    de.expand(dpf, m);
}

std::string dynamic_transform::id() const {
    return ::id;
}

void dynamic_transform::transform(const coding::transforms::context& ctx,
    const dogen::extraction::decoration_properties_factory& dpf,
    coding::meta_model::model& m) const {

    if (!requires_expansion(m))
        return;

    expand_injection(ctx.type_repository(), m);
    expand_decoration(dpf, m);
}

}
