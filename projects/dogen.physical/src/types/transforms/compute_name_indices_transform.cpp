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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/meta_model_io.hpp"
#include "dogen.physical/types/helpers/qualified_meta_name_builder.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/compute_name_indices_transform.hpp"

namespace {

const std::string
transform_id("physical.transforms.compute_name_indices_transform");
const std::string canonical_archetype_postfix(".canonical_archetype");
const std::string duplicate_archetype("Duplicate archetype id: ");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::physical::transforms {

void compute_name_indices_transform::
apply(const physical::transforms::minimal_context& ctx,
    physical::entities::meta_model& mm) {
    tracing::scoped_transform_tracer stp(lg, "compute name indices transform",
        transform_id, mm.meta_name().simple(), *ctx.tracer(), mm);

    std::unordered_map<std::string, physical::entities::meta_name_group>
        physical_meta_names_by_logical_meta_name_;

    for (auto& be : mm.backends()) {
        for (auto& fct_pair : be.facets()) {
            auto& fct(fct_pair.second);
            for (auto& arch_pair : fct.archetypes()) {
                auto& arch(arch_pair.second);

                const auto pmn(arch.meta_name());
                const auto lmn(arch.logical_meta_element_id());
                auto& g(physical_meta_names_by_logical_meta_name_[lmn]);
                g.meta_names().push_back(pmn);

                auto& cal(g.canonical_locations());
                const auto qn(pmn.qualified());
                using qnb = physical::helpers::qualified_meta_name_builder;
                const auto rs_fd(entities::referencing_status::facet_default);
                if (arch.referencing_status() == rs_fd) {
                    const auto fct_qn(qnb::build_facet(pmn));
                    const auto carch(fct_qn + canonical_archetype_postfix);
                    const auto inserted(cal.insert(std::make_pair(qn, carch)).second);
                    if (!inserted) {
                        BOOST_LOG_SEV(lg, error) << duplicate_archetype << qn;
                        BOOST_THROW_EXCEPTION(transform_exception(duplicate_archetype + qn));
                    }
                    BOOST_LOG_SEV(lg, debug) << "Mapped " << carch << " to " << qn;
                }
            }
        }
    }

    stp.end_transform(mm);
}

}
