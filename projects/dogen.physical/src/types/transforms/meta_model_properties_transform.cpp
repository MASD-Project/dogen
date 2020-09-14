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
#include "dogen.physical/types/transforms/meta_model_properties_transform.hpp"

namespace {

const std::string
transform_id("physical.transforms.meta_model_properties_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

static std::string enabled_feature("enabled");
static std::string overwrite_feature("overwrite");

const std::string root_module_not_found("Could not find root module: ");
const std::string backend_not_found("Could not find backend: ");
const std::string facet_not_found("Could not find facet: ");
const std::string archetype_not_found("Could not find archetype: ");

}

namespace dogen::physical::transforms {

using variability::entities::feature_model;
using variability::helpers::feature_selector;
using variability::helpers::configuration_selector;
using identification::entities::physical_meta_id;
using identification::entities::physical_meta_name_indices;

std::unordered_map<physical_meta_id,
                   meta_model_properties_transform::backend_feature_group>
meta_model_properties_transform::make_backend_feature_group(
    const feature_model& fm, const physical_meta_name_indices& idx) {

    const feature_selector s(fm);
    std::unordered_map<physical_meta_id, backend_feature_group> r;
    for (const auto& pair : idx.facet_names_by_backend_name()) {
        const auto& backend(pair.first);
        backend_feature_group fg;
        fg.enabled = s.get_by_name(backend.value(), enabled_feature);
        r.insert(std::make_pair(backend, fg));
    }
    return r;
}

std::unordered_map<physical_meta_id,
                   meta_model_properties_transform::facet_feature_group>
meta_model_properties_transform::make_facet_feature_group(
    const feature_model& fm, const physical_meta_name_indices& idx) {

    const feature_selector s(fm);
    std::unordered_map<physical_meta_id, facet_feature_group> r;
    for (const auto& pair : idx.facet_names_by_backend_name()) {
        for (const auto& fct : pair.second) {
            facet_feature_group fg;
            fg.enabled = s.get_by_name(fct.value(), enabled_feature);
            fg.overwrite = s.get_by_name(fct.value(), overwrite_feature);
            r.insert(std::make_pair(fct, fg));
        }
    }
    return r;
}

std::unordered_map<physical_meta_id,
                   meta_model_properties_transform::archetype_feature_group>
meta_model_properties_transform::make_archetype_feature_group(
    const feature_model& fm, const physical_meta_name_indices& idx) {

    const feature_selector s(fm);
    std::unordered_map<physical_meta_id, archetype_feature_group> r;
    for (const auto& pmn : idx.all()) {
        const auto pmid(pmn.id().value());
        archetype_feature_group fg;
        fg.enabled = s.get_by_name(pmid, enabled_feature);
        fg.overwrite = s.get_by_name(pmid, overwrite_feature);
        r.insert(std::make_pair(pmid, fg));
    }
    return r;
}

std::unordered_map<physical_meta_id, entities::backend_properties>
meta_model_properties_transform::obtain_backend_properties(
    const std::unordered_map<physical_meta_id, backend_feature_group>& fgs,
    const variability::entities::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Creating backend properties.";

    const configuration_selector s(cfg);
    std::unordered_map<physical_meta_id, entities::backend_properties> r;
    for (const auto& pair : fgs) {
        const auto& backend(pair.first);
        const auto& fg(pair.second);

        entities::backend_properties bp;
        bp.enabled(s.get_boolean_content_or_default(fg.enabled));
        r[backend] = bp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created backend properties. Result: " << r;
    return r;
}

std::unordered_map<physical_meta_id, entities::facet_properties>
meta_model_properties_transform::obtain_facet_properties(
    const std::unordered_map<physical_meta_id, facet_feature_group>& fgs,
    const variability::entities::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Creating facet properties.";

    const configuration_selector s(cfg);
    std::unordered_map<physical_meta_id, entities::facet_properties> r;
    for (const auto& pair : fgs) {
        const auto& facet(pair.first);
        const auto& fg(pair.second);

        entities::facet_properties fp;
        fp.enabled(s.get_boolean_content_or_default(fg.enabled));
        fp.overwrite(s.get_boolean_content_or_default(fg.overwrite));
        r[facet] = fp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created facet properties. Result: " << r;
    return r;
}

std::unordered_map<physical_meta_id, entities::archetype_properties>
meta_model_properties_transform::obtain_archetype_properties(
    const std::unordered_map<physical_meta_id, archetype_feature_group>& fgs,
    const variability::entities::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Creating archetype properties.";

    const configuration_selector s(cfg);
    std::unordered_map<physical_meta_id, entities::archetype_properties> r;
    for (const auto& pair : fgs) {
        const auto& archetype(pair.first);
        const auto& fg(pair.second);

        entities::archetype_properties ap;
        ap.enabled(s.get_boolean_content_or_default(fg.enabled));
        if (s.has_configuration_point(fg.overwrite))
            ap.overwrite(s.get_boolean_content(fg.overwrite));
        r[archetype] = ap;
    }

    BOOST_LOG_SEV(lg, debug) << "Created archetype properties. Result: " << r;
    return r;
}

std::unordered_map<physical_meta_id,
                   entities::denormalised_archetype_properties>
meta_model_properties_transform::obtain_denormalised_archetype_properties(
    const identification::entities::physical_meta_name_indices& idx,
    const entities::meta_model_properties& mmp) {

    std::unordered_map<physical_meta_id,
                       entities::denormalised_archetype_properties> r;
    for (const auto& backend_pair : idx.archetype_names_by_backend_by_facet()) {
        /*
         * First we locate the backend for the current batch of
         * physical locations.
         */
        const auto& bn(backend_pair.first);
        const auto i(mmp.backend_properties().find(bn));
        if (i == mmp.backend_properties().end()) {
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
            const auto j(mmp.facet_properties().find(fn));
            if (j == mmp.facet_properties().end()) {
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

                const auto k(mmp.archetype_properties().find(an));
                if (k == mmp.archetype_properties().end()) {
                    BOOST_LOG_SEV(lg, error) << archetype_not_found << an;
                    BOOST_THROW_EXCEPTION(
                        transform_exception(archetype_not_found + an.value()));
                }
                const auto& archetype(k->second);
                dap.archetype_enabled(archetype.enabled());
                dap.archetype_overwrite(archetype.overwrite());
                r.insert(std::make_pair(an, dap));
            }
        }
    }
    return r;
}

void meta_model_properties_transform::
apply(const context& ctx, entities::artefact_repository& arp) {
    tracing::scoped_transform_tracer stp(lg, "global enablement transform",
        transform_id, arp.identifier(), *ctx.tracer(), arp);

    /*
     * Obtain the root module configuration.
     */
    const auto rmid(arp.root_module_logical_id());
    const auto i(arp.artefact_sets_by_logical_id().find(rmid));
    if (i == arp.artefact_sets_by_logical_id().end()) {
        BOOST_LOG_SEV(lg, error) << root_module_not_found << rmid;
        BOOST_THROW_EXCEPTION(
            transform_exception(root_module_not_found + rmid.value()));
    }
    const auto& cfg(*i->second.configuration());

    const auto& fm(*ctx.feature_model());
    const auto& pmm(*ctx.meta_model());
    const auto& idx(pmm.indexed_names());
    auto& mmp(arp.meta_model_properties());

    /*
     * Populate the backend properties.
     */
    const auto bfg(make_backend_feature_group(fm, idx));
    mmp.backend_properties(obtain_backend_properties(bfg, cfg));

    /*
     * Populate the facet properties.
     */
    const auto ffg(make_facet_feature_group(fm, idx));
    mmp.facet_properties(obtain_facet_properties(ffg, cfg));

    /*
     * Populate the archetype properties.
     */
    const auto afg(make_archetype_feature_group(fm, idx));
    mmp.archetype_properties(obtain_archetype_properties(afg, cfg));

    /*
     * Now populate the denormalised archetype properties by querying
     * the containers we've already populated.
     */
    mmp.denormalised_archetype_enablement_properties(
        obtain_denormalised_archetype_properties(idx, mmp));

    stp.end_transform(arp);
}

}
