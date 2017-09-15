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
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/types/transforms/generability_transform.hpp"

namespace {

const std::string id("yarn.transforms.generability_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(id));

}

namespace dogen {
namespace yarn {
namespace transforms {

bool generability_transform::is_generatable(const meta_model::element& e) {
    const auto ot(e.origin_type());
    return ot == meta_model::origin_types::target;
}

bool generability_transform::
has_generatable_types(const meta_model::endomodel& em) {
    /*
     * Note: we are deliberately excluding modules since we do not
     * want to generate an empty model with just a module because its
     * documented.
     */
    for (const auto pair : em.objects()) {
        if (is_generatable(*pair.second))
            return true;
    }

    for (const auto pair : em.enumerations()) {
        if (is_generatable(*pair.second))
            return true;
    }

    for (const auto pair : em.enumerations()) {
        if (is_generatable(*pair.second))
            return true;
    }

    for (const auto pair : em.exceptions()) {
        if (is_generatable(*pair.second))
            return true;
    }

    for (const auto pair : em.builtins()) {
        if (is_generatable(*pair.second))
            return true;
    }

    for (const auto pair : em.object_templates()) {
        if (is_generatable(*pair.second))
            return true;
    }

    for (const auto pair : em.primitives()) {
        if (is_generatable(*pair.second))
            return true;
    }

    return false;
}

void generability_transform::
transform(const context& ctx, meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Started generability transform.";
    ctx.prober().start_transform(id, em.name().id(), em);
    em.has_generatable_types(has_generatable_types(em));
    ctx.prober().end_transform(em);
    BOOST_LOG_SEV(lg, debug) << "Finished generability transform.";
}

} } }
