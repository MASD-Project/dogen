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
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen.quilt.cpp/types/fabric/injector.hpp"
#include "dogen.quilt.cpp/types/fabric/decoration_expander.hpp"
#include "dogen.quilt.cpp/types/fabric/dynamic_transform.hpp"

namespace {

const std::string id("quilt.cpp.fabric.dynamic_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

bool dynamic_transform::
requires_expansion(const yarn::meta_model::model& m) const {
    const auto l(m.output_language());
    const auto r(l == yarn::meta_model::languages::cpp);
    if (!r) {
        BOOST_LOG_SEV(lg, debug) << "Expansion not required: "
                                 << m.name().id() << " for language: " << l;
    }
    return r;
}

void dynamic_transform::expand_injection(
    const annotations::type_repository& atrp,
    yarn::meta_model::model& m) const {
    injector i;
    i.inject(atrp, m);
}

void dynamic_transform::expand_decoration(
    const dogen::formatters::decoration_properties_factory& dpf,
    yarn::meta_model::model& m) const {
    decoration_expander de;
    de.expand(dpf, m);
}

std::string dynamic_transform::id() const {
    return ::id;
}

void dynamic_transform::transform(const yarn::transforms::context& ctx,
    const dogen::formatters::decoration_properties_factory& dpf,
    yarn::meta_model::model& m) const {

    if (!requires_expansion(m))
        return;

    expand_injection(ctx.type_repository(), m);
    expand_decoration(dpf, m);
}

} } } }
