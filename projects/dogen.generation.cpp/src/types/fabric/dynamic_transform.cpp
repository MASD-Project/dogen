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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.assets/io/meta_model/technical_space_io.hpp"
#include "dogen.generation/types/transforms/transformation_error.hpp"
#include "dogen.generation/types/transforms/context.hpp"
#include "dogen.generation.cpp/types/fabric/injector.hpp"
#include "dogen.generation.cpp/types/fabric/dynamic_transform.hpp"

namespace {

const std::string id("generation.cpp.fabric.dynamic_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen::generation::cpp::fabric {

bool dynamic_transform::
requires_expansion(const generation::meta_model::model& m) const {
    const auto l(m.output_technical_space());
    const auto r(l == assets::meta_model::technical_space::cpp);
    if (!r) {
        BOOST_LOG_SEV(lg, debug) << "Expansion not required: "
                                 << m.name().qualified().dot()
                                 << " for technical space: " << l;
    }
    return r;
}

void dynamic_transform::expand_injection(generation::meta_model::model& m) const {
    injector i;
    i.inject(m);
}

std::string dynamic_transform::id() const {
    return ::id;
}

void dynamic_transform::apply(const generation::transforms::context& /*ctx*/,
    generation::meta_model::model& m) const {

    if (!requires_expansion(m))
        return;

    expand_injection(m);
}

}
