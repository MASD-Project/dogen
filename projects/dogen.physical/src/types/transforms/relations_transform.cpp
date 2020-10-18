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
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/relations_transform.hpp"

namespace {

const std::string transform_id("physical.transforms.relations_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_archetype("Duplicate archetype id: ");
const std::string missing_archetype("Missing archetype id: ");

}

namespace dogen::physical::transforms {

using identification::entities::physical_meta_id;

std::unordered_map<physical_meta_id, entities::relations> relations_transform::
obtain_relations_for_archetype(const entities::meta_model& pmm) {
    std::unordered_map<physical_meta_id, entities::relations> r;
    for (const auto& be : pmm.backends()) {
        for (const auto& arch_pair : be.archetypes()) {
            const auto& arch(arch_pair.second);

            const auto id(arch.meta_name().id());
            const auto pair(std::make_pair(id, arch.relations()));
            const auto inserted(r.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_archetype << id.value();
                BOOST_THROW_EXCEPTION(
                    transform_exception(duplicate_archetype + id.value()));
            }
        }

        for (const auto& fct_pair : be.facets()) {
            const auto& fct(fct_pair.second);
            for (const auto& arch_pair : fct.archetypes()) {
                const auto& arch(arch_pair.second);

                const auto id(arch.meta_name().id());
                const auto pair(std::make_pair(id, arch.relations()));
                const auto inserted(r.insert(pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_archetype
                                             << id.value();
                    BOOST_THROW_EXCEPTION(
                        transform_exception(duplicate_archetype + id.value()));
                }
            }
        }

        for (const auto& part_pair : be.parts()) {
            const auto& part(part_pair.second);
            for (const auto& arch_pair : part.archetypes()) {
                const auto& arch(arch_pair.second);

                const auto id(arch.meta_name().id());
                const auto pair(std::make_pair(id, arch.relations()));
                const auto inserted(r.insert(pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_archetype
                                             << id.value();
                    BOOST_THROW_EXCEPTION(
                        transform_exception(duplicate_archetype + id.value()));
                }
            }
        }
    }
    return r;
}

void relations_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "relations",
        transform_id, m.name().id().value(), *ctx.tracer(), m);

    const auto& pmm(*ctx.meta_model());
    const auto rfa(obtain_relations_for_archetype(pmm));

    for (auto& region_pair : m.regions_by_logical_id()) {
        auto& region(region_pair.second);
        for (auto& art_pair : region.artefacts_by_archetype()) {
            const auto& pmid(art_pair.first);
            const auto i(rfa.find(pmid));
            if (i == rfa.end()) {
                BOOST_LOG_SEV(lg, error) << missing_archetype << pmid.value();
                BOOST_THROW_EXCEPTION(
                    transform_exception(missing_archetype + pmid.value()));
            }

            const auto& meta_relations(i->second);
            auto& a(*art_pair.second);
            a.relations().status(meta_relations.status());
        }
    }

    stp.end_transform(m);
}

}
