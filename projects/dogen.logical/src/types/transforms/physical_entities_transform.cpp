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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/features/physical.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/physical/part.hpp"
#include "dogen.logical/types/entities/physical/facet.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/physical_entities_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.physical_entities_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string separator(".");
const std::string kernel_name("masd");

const std::string ambiguous_name("Name maps to more than one element type:");
const std::string unsupported_composition(
    "Physical element composition is not supported: ");
const std::string duplicate_part_id("Duplicate part ID: ");;
const std::string missing_part("Part could not be located: ");

}

namespace dogen::logical::transforms {

void physical_entities_transform::
process_backends(const context& ctx, entities::model& m) {
    using features::physical;
    const auto& pe(m.physical_elements());
    const auto& fm(*ctx.feature_model());
    const auto fg(physical::make_feature_group(fm));

    auto& bs(pe.backends());
    for (auto& pair : bs) {
        auto& b(*pair.second);
        const auto scfg(physical::make_static_configuration(fg, b));
        b.backend_name(scfg.backend_name);
        b.kernel_name(kernel_name);

        std::ostringstream os;
        os << kernel_name << separator << b.backend_name();
        b.id(os.str());

        bool found(false);
        for (const auto& qn : b.contains()) {
            /*
             * Check to see if the contained element is a facet, and
             * if so add it to the facets container.
             */
            const auto& fcts(pe.facets());
            const auto i(fcts.find(qn));
            if (i != fcts.end()) {
                auto& fct(*i->second);
                b.facets().push_back(fct.name());
                fct.backend_name(b.backend_name());
                found = true;
            }

            /*
             * Check to see if the contained element is a part, and
             * if so add it to the parts container.
             */
            const auto& parts(pe.parts());
            const auto j(parts.find(qn));
            if (j != parts.end()) {
                if (found) {
                    BOOST_LOG_SEV(lg, error) << ambiguous_name << qn;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(ambiguous_name + qn));
                }

                auto& part(*j->second);
                b.parts().push_back(part.name());
                part.backend_name(b.backend_name());
                found = true;
            }

            /*
             * Check to see if the contained element is an archetype
             * kind, and if so add it to the archetype kinds
             * container.
             */
            const auto& aks(pe.archetype_kinds());
            const auto k(aks.find(qn));
            if (k != aks.end()) {
                if (found) {
                    BOOST_LOG_SEV(lg, error) << ambiguous_name << qn;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(ambiguous_name + qn));
                }

                auto& ak(*k->second);
                b.archetype_kinds().push_back(ak.name());
                ak.backend_name(b.backend_name());
            }

            /*
             * Backends cannot contain backends or archetypes.
             */
            const bool is_backend(bs.find(qn) != bs.end());
            const auto& archs(pe.archetypes());
            const bool is_archetype(archs.find(qn) != archs.end());
            if (is_backend || is_archetype) {
                BOOST_LOG_SEV(lg, error) << unsupported_composition << qn
                                         << " Container: "
                                         << b.name().qualified().dot();
                BOOST_THROW_EXCEPTION(
                    transformation_error(unsupported_composition + qn));
            }
        }
    }
}

void physical_entities_transform::process_facets(entities::model& m) {
    using features::physical;
    const auto& pe(m.physical_elements());
    auto& fcts(pe.facets());
    for (auto& pair : fcts) {
        auto& fct(*pair.second);
        fct.kernel_name(kernel_name);

        std::ostringstream os;
        os << kernel_name << separator
           << fct.backend_name() << separator
           << fct.name().simple();
        fct.id(os.str());

        bool found(false);
        for (const auto& qn : fct.contains()) {
            /*
             * Check to see if the contained element is an archetype,
             * and if so add it to the facets container.
             */
            const auto& archs(pe.archetypes());
            const auto i(archs.find(qn));
            if (i != archs.end()) {
                auto& arch(*i->second);
                fct.archetypes().push_back(arch.name());
                arch.facet_name(fct.name().simple());
                found = true;
            }

            /*
             * Facets cannot contain any other kind of physical
             * elements.
             */
            const auto& bs(pe.backends());
            const bool is_backend(bs.find(qn) != bs.end());
            const auto& fcts(pe.facets());
            const bool is_facet(fcts.find(qn) != fcts.end());
            const auto& parts(pe.parts());
            const bool is_part(parts.find(qn) != parts.end());
            const auto& aks(pe.archetype_kinds());
            const bool is_ak(aks.find(qn) != aks.end());
            if (is_backend || is_facet || is_part || is_ak) {
                BOOST_LOG_SEV(lg, error) << unsupported_composition << qn
                                         << " Container: "
                                         << fct.name().qualified().dot();
                BOOST_THROW_EXCEPTION(
                    transformation_error(unsupported_composition + qn));
            }
        }
    }
}

void physical_entities_transform::process_archetype_kinds(entities::model& m) {
    const auto& pe(m.physical_elements());
    auto& aks(pe.archetype_kinds());
    for (auto& pair : aks) {
        auto& ak(*pair.second);
        ak.kernel_name(kernel_name);

        std::ostringstream os;
        os << kernel_name << separator
           << ak.backend_name() << separator
           << ak.name().simple();
        ak.id(os.str());
    }
}

void physical_entities_transform::process_parts(entities::model& m) {
    const auto& pe(m.physical_elements());
    auto& parts(pe.parts());
    for (auto& pair : parts) {
        auto& part(*pair.second);
        part.kernel_name(kernel_name);

        std::ostringstream os;
        os << kernel_name << separator
           << part.backend_name() << separator
           << part.name().simple();
        part.id(os.str());
    }
}

void physical_entities_transform::
process_archetypes(const context& ctx, entities::model& m) {
    using features::physical;
    const auto& pe(m.physical_elements());
    const auto& fm(*ctx.feature_model());
    const auto fg(physical::make_feature_group(fm));

    const auto& parts(pe.parts());
    std::unordered_map<std::string, boost::shared_ptr<entities::physical::part>>
        parts_by_ids;
    for (const auto& pair : parts) {
        const auto& part(*pair.second);
        const auto id(part.id());
        const auto new_pair(std::make_pair(id, pair.second));
        const auto inserted(parts_by_ids.insert(new_pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_part_id << part.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_part_id + part.id()));
        }
    }

    auto& archs(pe.archetypes());
    for (auto& pair : archs) {
        auto& arch(*pair.second);
        arch.kernel_name(kernel_name);

        const auto scfg(physical::make_static_configuration(fg, arch));
        arch.part_id(scfg.part_id);

        std::ostringstream os;
        const auto sn(arch.name().simple());
        os << kernel_name << separator
           << arch.backend_name() << separator
           << arch.facet_name() << separator << sn;
        arch.id(os.str());

        const auto qn(arch.name().qualified().dot());
        const auto pid(arch.part_id());
        const auto i(parts_by_ids.find(pid));
        if (i == parts_by_ids.end()) {
            BOOST_LOG_SEV(lg, error) << missing_part << pid;
            BOOST_THROW_EXCEPTION(transformation_error(missing_part + pid));
        }

        auto& part(*i->second);
        part.archetypes().push_back(arch.name());
    }
}

void physical_entities_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "physical entities transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    process_backends(ctx, m);
    process_facets(m);
    process_archetype_kinds(m);
    process_parts(m);
    process_archetypes(ctx, m);

    stp.end_transform(m);
}

}
