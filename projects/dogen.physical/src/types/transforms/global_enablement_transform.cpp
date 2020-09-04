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
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/io/entities/artefact_repository_io.hpp"
#include "dogen.physical/io/entities/backend_properties_io.hpp"
#include "dogen.physical/io/entities/facet_properties_io.hpp"
#include "dogen.physical/io/entities/archetype_properties_io.hpp"
#include "dogen.physical/io/entities/enablement_properties_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/global_enablement_transform.hpp"

namespace {

const std::string
transform_id("physical.transforms.global_enablement_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

static std::string enabled_feature("enabled");
static std::string overwrite_feature("overwrite");

const std::string root_module_not_found("Could not find root module: ");
const std::string type_group_not_found(
    "Could not find a type group for archetype: ");
const std::string backend_not_found("Could not find backend: ");
const std::string facet_not_found("Could not find facet: ");
const std::string archetype_not_found("Could not find archetype: ");
const std::string missing_configuration(
    "Configuration not available for element: ");

}

namespace dogen::physical::transforms {

std::unordered_map<
    identification::entities::physical_meta_id,
    global_enablement_transform::backend_feature_group>
global_enablement_transform::
make_backend_feature_group(const variability::entities::feature_model& fm,
    const identification::entities::physical_meta_name_indices& idx) {
    std::unordered_map<identification::entities::physical_meta_id,
                       backend_feature_group> r;

    const variability::helpers::feature_selector s(fm);
    for (const auto& pair : idx.facet_names_by_backend_name()) {
        const auto& backend(pair.first);
        backend_feature_group btg;
        btg.enabled = s.get_by_name(backend.value(), enabled_feature);

        r.insert(std::make_pair(backend, btg));
    }
    return r;
}

std::unordered_map<
    identification::entities::physical_meta_id,
    global_enablement_transform::facet_feature_group>
global_enablement_transform::
make_facet_feature_group(const variability::entities::feature_model& fm,
    const identification::entities::physical_meta_name_indices& idx) {
    std::unordered_map<identification::entities::physical_meta_id,
                       facet_feature_group> r;

    const variability::helpers::feature_selector s(fm);
    for (const auto& pair : idx.facet_names_by_backend_name()) {
        for (const auto& fct : pair.second) {
            facet_feature_group ftg;
            ftg.enabled = s.get_by_name(fct.value(), enabled_feature);
            ftg.overwrite = s.get_by_name(fct.value(), overwrite_feature);
            r.insert(std::make_pair(fct, ftg));
        }
    }
    return r;
}

std::unordered_map<
    identification::entities::physical_meta_id,
    global_enablement_transform::global_archetype_feature_group>
global_enablement_transform::make_global_archetype_feature_group(
    const variability::entities::feature_model& fm,
    const identification::entities::physical_meta_name_indices& idx) {
    std::unordered_map<identification::entities::physical_meta_id,
                       global_archetype_feature_group> r;

    const variability::helpers::feature_selector s(fm);
    for (const auto& pmn : idx.all()) {
        const auto id(pmn.id().value());
        global_archetype_feature_group gatg;
        gatg.enabled = s.get_by_name(id, enabled_feature);
        gatg.overwrite = s.get_by_name(id, overwrite_feature);
        r.insert(std::make_pair(id, gatg));
    }
    return r;
}

std::unordered_map<
    identification::entities::physical_meta_id,
    global_enablement_transform::local_archetype_feature_group>
global_enablement_transform::make_local_archetype_feature_group(
    const variability::entities::feature_model& fm,
    const identification::entities::physical_meta_name_indices& idx) {
    std::unordered_map<identification::entities::physical_meta_id,
                       local_archetype_feature_group> r;

    const variability::helpers::feature_selector s(fm);
    identification::helpers::physical_meta_id_builder b;
    for (const auto& mn : idx.all()) {
        local_archetype_feature_group latg;
        const auto id(mn.id());
        const auto pmid(b.build_facet(mn));
        latg.facet_enabled = s.get_by_name(pmid.value(), enabled_feature);
        latg.archetype_enabled = s.get_by_name(id.value(), enabled_feature);
        latg.facet_overwrite = s.get_by_name(pmid.value(), overwrite_feature);
        latg.archetype_overwrite = s.get_by_name(id.value(), overwrite_feature);

        r.insert(std::make_pair(id, latg));
    }
    return r;
}

std::unordered_map<identification::entities::physical_meta_id,
                   entities::backend_properties>
global_enablement_transform::obtain_backend_properties(
    const std::unordered_map<identification::entities::physical_meta_id,
    backend_feature_group>& fgs,
    const variability::entities::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Creating backend properties.";

    std::unordered_map<identification::entities::physical_meta_id,
                       entities::backend_properties> r;
    const variability::helpers::configuration_selector s(cfg);
    for (const auto& pair : fgs) {
        const auto& backend(pair.first);
        const auto& tg(pair.second);

        entities::backend_properties bp;
        bp.enabled(s.get_boolean_content_or_default(tg.enabled));
        r[backend] = bp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created backend properties. Result: " << r;
    return r;
}

std::unordered_map<identification::entities::physical_meta_id,
                   entities::facet_properties>
global_enablement_transform::
obtain_facet_properties(const std::unordered_map<
    identification::entities::physical_meta_id, facet_feature_group>& fgs,
    const variability::entities::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Creating facet properties.";

    std::unordered_map<identification::entities::physical_meta_id,
                       entities::facet_properties> r;
    const variability::helpers::configuration_selector s(cfg);
    for (const auto& pair : fgs) {
        const auto& facet(pair.first);
        const auto& tg(pair.second);

        entities::facet_properties fp;
        fp.enabled(s.get_boolean_content_or_default(tg.enabled));
        fp.overwrite(s.get_boolean_content_or_default(tg.overwrite));

        r[facet] = fp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created facet properties. Result: " << r;
    return r;
}

std::unordered_map<identification::entities::physical_meta_id,
                   entities::archetype_properties>
global_enablement_transform::obtain_archetype_properties(
    const std::unordered_map<identification::entities::physical_meta_id,
    global_archetype_feature_group>& fgs,
    const variability::entities::configuration& ra) {

    BOOST_LOG_SEV(lg, debug) << "Creating archetype properties.";

    std::unordered_map<identification::entities::physical_meta_id,
                       entities::archetype_properties> r;
    const variability::helpers::configuration_selector s(ra);
    for (const auto& pair : fgs) {
        const auto& archetype(pair.first);
        const auto& tg(pair.second);

        entities::archetype_properties ap;
        ap.enabled(s.get_boolean_content_or_default(tg.enabled));
        if (s.has_configuration_point(tg.overwrite))
            ap.overwrite(s.get_boolean_content(tg.overwrite));

        r[archetype] = ap;
    }

    BOOST_LOG_SEV(lg, debug) << "Created archetype properties. Result: " << r;
    return r;
}

void global_enablement_transform::populate_global_enablement_properties(
    const variability::entities::feature_model& fm,
    const identification::entities::physical_meta_name_indices& nrp,
    entities::artefact_repository& ar) {

    const auto bftg(make_backend_feature_group(fm, nrp));
    const auto fftg(make_facet_feature_group(fm, nrp));
    const auto aftg(make_global_archetype_feature_group(fm, nrp));

    const auto rmid(ar.root_module_logical_id());
    const auto i(ar.artefact_sets_by_logical_id().find(rmid));
    if (i == ar.artefact_sets_by_logical_id().end()) {
        BOOST_LOG_SEV(lg, error) << root_module_not_found << rmid;
        BOOST_THROW_EXCEPTION(
            transform_exception(root_module_not_found + rmid.value()));
    }

    const auto& cfg(*i->second.configuration());
    auto& galp(ar.global_enablement_properties());
    galp.backend_properties(obtain_backend_properties(bftg, cfg));
    galp.facet_properties(obtain_facet_properties(fftg, cfg));
    galp.archetype_properties(obtain_archetype_properties(aftg, cfg));

    /*
     * Now populate the denormalised archetype properties by querying
     * the containers we've already populated.
     */
    for (const auto& backend_pair : nrp.archetype_names_by_backend_by_facet()) {
        /*
         * First we locate the backend for the current batch of
         * physical locations.
         */
        const auto& bn(backend_pair.first);
        const auto i(galp.backend_properties().find(bn));
        if (i == galp.backend_properties().end()) {
            BOOST_LOG_SEV(lg, error) << backend_not_found << bn;
            BOOST_THROW_EXCEPTION(transform_exception(
                    backend_not_found + bn.value()));
        }
        const auto& backend(i->second);

        /*
         * Next we loop through all of its facets and locate each facet.
         */
        for (const auto& facet_pair : backend_pair.second) {
            const auto& fn(facet_pair.first);
            const auto j(galp.facet_properties().find(fn));
            if (j == galp.facet_properties().end()) {
                BOOST_LOG_SEV(lg, error) << facet_not_found << fn;
                BOOST_THROW_EXCEPTION(
                    transform_exception(facet_not_found + fn.value()));
            }
            const auto& facet(j->second);

            /*
             * Finally we can loop through all of the physical
             * locations owned by both this backend and facet and
             * populate the denormalised properties.
             */
            for (const auto& an : facet_pair.second) {
                entities::denormalised_archetype_properties dap;
                dap.backend_enabled(backend.enabled());
                dap.facet_enabled(facet.enabled());
                dap.facet_overwrite(facet.overwrite());

                const auto k(galp.archetype_properties().find(an));
                if (k == galp.archetype_properties().end()) {
                    BOOST_LOG_SEV(lg, error) << archetype_not_found << an;
                    BOOST_THROW_EXCEPTION(
                        transform_exception(archetype_not_found + an.value()));
                }
                const auto& archetype(k->second);
                dap.archetype_enabled(archetype.enabled());
                dap.archetype_overwrite(archetype.overwrite());
                galp.denormalised_archetype_properties()
                    .insert(std::make_pair(an, dap));
            }
        }
    }
}

void global_enablement_transform::populate_local_enablement_properties(
    const variability::entities::feature_model& fm,
    const identification::entities::physical_meta_name_indices& nrp,
    entities::artefact_repository& ar) {
    /*
     * Computes all of the possible features for every physical
     * location. Not all of these will be of use to a given element,
     * because they may not be expressed for that element.
     */
    const auto fgs(make_local_archetype_feature_group(fm, nrp));

    for (auto& as_pair : ar.artefact_sets_by_logical_id()) {
        const auto id(as_pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing: " << id;
        auto& as(as_pair.second);

        if (!as.configuration()) {
            BOOST_LOG_SEV(lg, error) << missing_configuration << id;
            BOOST_THROW_EXCEPTION(
                transform_exception(missing_configuration + id.value()));
        }

        const auto& cfg(*as.configuration());
        const variability::helpers::configuration_selector s(cfg);
        for (auto& a_pair : as.artefacts_by_archetype()) {
            auto& a(*a_pair.second);
            const auto archetype(a.meta_name().id());
            const auto i(fgs.find(archetype));
            if (i == fgs.end()) {
                BOOST_LOG_SEV(lg, error) << type_group_not_found << archetype;
                BOOST_THROW_EXCEPTION(transform_exception(
                        type_group_not_found + archetype.value()));
            }
            const auto fg(i->second);
            if (s.has_configuration_point(fg.facet_enabled)) {
                a.enablement_properties().facet_enabled(
                    s.get_boolean_content_or_default(fg.facet_enabled));
            }

            if (s.has_configuration_point(fg.archetype_enabled)) {
                a.enablement_properties().archetype_enabled(
                    s.get_boolean_content_or_default(fg.archetype_enabled));
            }

            if (s.has_configuration_point(fg.facet_overwrite)) {
                a.enablement_properties().facet_overwrite(
                    s.get_boolean_content(fg.facet_overwrite));
            }

            if (s.has_configuration_point(fg.archetype_overwrite)) {
                a.enablement_properties().archetype_overwrite(
                    s.get_boolean_content(fg.archetype_overwrite));
            }
        }
    }
}

void global_enablement_transform::
apply(const context& ctx, entities::artefact_repository& ar) {
    tracing::scoped_transform_tracer stp(lg, "global enablement transform",
        transform_id, ar.identifier(), *ctx.tracer(), ar);

    const auto &fm(*ctx.feature_model());
    const auto& pmm(*ctx.meta_model());
    const auto& in(pmm.indexed_names());
    populate_global_enablement_properties(fm, in, ar);
    populate_local_enablement_properties(fm, in, ar);

    stp.end_transform(ar);
}

}
