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
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/entities/templating/logic_less_template.hpp"
#include "dogen.logical/types/transforms/logic_less_templates_population_transform.hpp"

namespace {

const std::string transform_id(
    "logical.transforms.logic_less_templates_population_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string missing_logic_less_template(
    "Could not locate referenced logic-less template: ");

}

namespace dogen::logical::transforms {

void logic_less_templates_population_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "parsing transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& pe(m.physical_elements());
    auto& archs(pe.archetypes());
    for (auto& pair : archs) {
        auto& arch(*pair.second);
        if (!arch.wale_template())
            continue;

        /*
         * Resolve logic-less template references to its content.
         */
        const auto tid(arch.wale_template()->qualified().dot());
        const auto& llt(m.templating_elements().logic_less_templates());
        const auto k(llt.find(tid));
        if (k != llt.end())
            arch.wale_template_content(k->second->content());

        BOOST_LOG_SEV(lg, error) << missing_logic_less_template << tid;
        BOOST_THROW_EXCEPTION(
            transformation_error(missing_logic_less_template + tid));
    }

    stp.end_transform(m);
}

}
