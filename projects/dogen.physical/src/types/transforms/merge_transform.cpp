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
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/io/entities/model_set_io.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/merge_transform.hpp"

namespace {

const std::string transform_id("physical.transforms.merge_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_archetype("Duplicate archetype : ");

}

namespace dogen::physical::transforms {

entities::model merge_transform::apply(const physical::transforms::context& ctx,
    const physical::entities::model_set& ms) {
    tracing::scoped_transform_tracer stp(lg, "merge transform", transform_id,
        ms.name().simple(), *ctx.tracer(), ms);

    bool first(true);
    physical::entities::model r;
    for (const auto& m : ms.models()) {
        /*
         * Bit of a hack: we initialise these properties from the
         * first model in the list. They should all be identical
         * anyway.
         */
        if (first) {
            r.provenance(m.provenance());
            r.name(m.name());
            r.configuration(m.configuration());
            first = false;
        }

        /*
         * Now we copy the stuff that actually matters.
         */
        for (const auto& rhs_pr_pair : m.regions_by_logical_id()) {
            const auto& rhs_pr(rhs_pr_pair.second);
            auto& lhs_pr(r.regions_by_logical_id()[rhs_pr_pair.first]);
            auto& lhs_aba(lhs_pr.artefacts_by_archetype());

            for (const auto& rhs_a_pair : rhs_pr.artefacts_by_archetype()) {
                const bool inserted(lhs_aba.insert(rhs_a_pair).second);
                if (!inserted) {
                    const auto& id(rhs_a_pair.first);
                    BOOST_LOG_SEV(lg, error) << duplicate_archetype << id;
                    BOOST_THROW_EXCEPTION(
                        transform_exception(duplicate_archetype + id.value()));
                }
            }
        }

        for (const auto& aptr : m.orphan_artefacts())
            r.orphan_artefacts().push_back(aptr);

        for (const auto& md : m.managed_directories())
            r.managed_directories().push_back(md);
    }

    stp.end_transform(r);
    return r;
}

}
