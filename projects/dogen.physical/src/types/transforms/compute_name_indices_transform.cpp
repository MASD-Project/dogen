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
#include "dogen.physical/types/helpers/meta_name_index_builder.hpp"
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
update_physical_meta_names_by_logical_meta_name(
    const physical::entities::archetype& arch,
    std::unordered_map<std::string, physical::entities::archetype_name_set>&
    physical_meta_names_by_logical_meta_name) {

    const auto pmn(arch.meta_name());
    const auto lmn(arch.logical_meta_element_id());
    auto& g(physical_meta_names_by_logical_meta_name[lmn]);
    g.logical_meta_element_id(lmn);
    g.meta_names().push_back(pmn);

    auto& cal(g.canonical_locations());
    const auto qn(pmn.qualified());
    using qnb = physical::helpers::qualified_meta_name_builder;
    const auto rs_fd(entities::relation_status::facet_default);
    if (arch.relations().status() == rs_fd) {
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

std::unordered_map<std::string, physical::entities::archetype_name_set>
compute_name_indices_transform::
obtain_physical_meta_names_by_logical_meta_name(
    const physical::entities::meta_model& mm) {

    std::unordered_map<std::string, physical::entities::archetype_name_set> r;
    for (auto& be : mm.backends()) {
        for (auto& fct_pair : be.facets()) {
            auto& fct(fct_pair.second);
            for (auto& arch_pair : fct.archetypes()) {
                auto& arch(arch_pair.second);
                update_physical_meta_names_by_logical_meta_name(arch, r);
            }
        }
    }

    return r;
}

void compute_name_indices_transform::
apply(const physical::transforms::minimal_context& ctx,
    physical::entities::meta_model& mm) {
    tracing::scoped_transform_tracer stp(lg, "compute meta-name indices transform",
        transform_id, mm.meta_name().simple(), *ctx.tracer(), mm);

    /*
     * Obtain the archetypes' physical meta-names by logical model
     * meta-name.
     */
    auto pmn_by_lmn(obtain_physical_meta_names_by_logical_meta_name(mm));

    /*
     * Now compute all of the indices.
     */
    physical::helpers::meta_name_index_builder b;
    b.add(pmn_by_lmn);
    mm.indexed_names(b.build());

    stp.end_transform(mm);
}

}
