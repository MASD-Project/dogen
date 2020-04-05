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
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/types/helpers/qualified_meta_name_builder.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.m2t/io/entities/model_io.hpp"
#include "dogen.m2t/io/entities/element_archetype_io.hpp"
#include "dogen.m2t/io/entities/backend_properties_io.hpp"
#include "dogen.m2t/io/entities/facet_properties_io.hpp"
#include "dogen.m2t/io/entities/archetype_properties_io.hpp"
#include "dogen.logical/io/entities/enablement_properties_io.hpp"
#include "dogen.m2t/types/transforms/transformation_error.hpp"
#include "dogen.m2t/types/transforms/global_enablement_transform.hpp"

namespace {

const std::string transform_id(
    "generation.transforms.global_enablement_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string type_group_not_found(
    "Could not find a type group for archetype: ");
const std::string backend_not_found("Could not find backend: ");
const std::string facet_not_found("Could not find facet: ");
const std::string archetype_not_found("Could not find archetype: ");

}

namespace dogen::m2t::transforms {

std::unordered_map<
    std::string,
    global_enablement_transform::backend_feature_group>
global_enablement_transform::
make_backend_feature_group(const variability::entities::feature_model& fm,
    const physical::entities::meta_name_repository& mnrp) {
    std::unordered_map<std::string, backend_feature_group> r;

    const variability::helpers::feature_selector s(fm);
    for (const auto& pair : mnrp.facet_names_by_backend_name()) {
        const auto& backend(pair.first);
        backend_feature_group btg;
        const auto ebl(logical::traits::enabled());
        btg.enabled = s.get_by_name(backend, ebl);

        r.insert(std::make_pair(backend, btg));
    }
    return r;
}

std::unordered_map<
    std::string,
    global_enablement_transform::facet_feature_group>
global_enablement_transform::
make_facet_feature_group(const variability::entities::feature_model& fm,
    const physical::entities::meta_name_repository& nrp) {
    std::unordered_map<std::string, facet_feature_group> r;

    const variability::helpers::feature_selector s(fm);
    for (const auto& pair : nrp.facet_names_by_backend_name()) {
        for (const auto& fct : pair.second) {
            facet_feature_group ftg;
            const auto ebl(logical::traits::enabled());
            ftg.enabled = s.get_by_name(fct, ebl);

            const auto ow(logical::traits::overwrite());
            ftg.overwrite = s.get_by_name(fct, ow);

            r.insert(std::make_pair(fct, ftg));
        }
    }
    return r;
}

std::unordered_map<
    std::string,
    global_enablement_transform::global_archetype_feature_group>
global_enablement_transform::make_global_archetype_feature_group(
    const variability::entities::feature_model& fm,
    const physical::entities::meta_name_repository& nrp) {
    std::unordered_map<std::string, global_archetype_feature_group> r;

    const variability::helpers::feature_selector s(fm);
    for (const auto& n : nrp.all()) {
        global_archetype_feature_group gatg;
        const auto ebl(logical::traits::enabled());
        gatg.enabled = s.get_by_name(n.qualified(), ebl);

        const auto ow(logical::traits::overwrite());
        gatg.overwrite = s.get_by_name(n.qualified(), ow);

        r.insert(std::make_pair(n.qualified(), gatg));
    }
    return r;
}

std::unordered_map<
    std::string,
    global_enablement_transform::local_archetype_feature_group>
global_enablement_transform::make_local_archetype_feature_group(
    const variability::entities::feature_model& fm,
    const physical::entities::meta_name_repository& nrp) {
    std::unordered_map<std::string, local_archetype_feature_group> r;

    const variability::helpers::feature_selector s(fm);
    using qnb = physical::helpers::qualified_meta_name_builder;
    for (const auto& n : nrp.all()) {
        local_archetype_feature_group latg;
        const auto qn(n.qualified());
        const auto ebl(logical::traits::enabled());
        const auto f(qnb::build_facet(n));
        latg.facet_enabled = s.get_by_name(f, ebl);
        latg.archetype_enabled = s.get_by_name(qn, ebl);

        const auto ow(logical::traits::overwrite());
        latg.facet_overwrite = s.get_by_name(f, ow);
        latg.archetype_overwrite = s.get_by_name(qn, ow);

        r.insert(std::make_pair(qn, latg));
    }
    return r;
}

std::unordered_map<std::string, entities::backend_properties>
global_enablement_transform::obtain_backend_properties(
    const std::unordered_map<std::string, backend_feature_group>& fgs,
    const variability::entities::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Creating backend properties.";

    std::unordered_map<std::string, entities::backend_properties> r;
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

std::unordered_map<std::string, entities::facet_properties>
global_enablement_transform::obtain_facet_properties(
    const std::unordered_map<std::string, facet_feature_group>& fgs,
    const variability::entities::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Creating facet properties.";

    std::unordered_map<std::string, entities::facet_properties> r;
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

std::unordered_map<std::string, entities::archetype_properties>
global_enablement_transform::obtain_archetype_properties(
    const std::unordered_map<std::string, global_archetype_feature_group>& fgs,
    const variability::entities::configuration& ra) {

    BOOST_LOG_SEV(lg, debug) << "Creating archetype properties.";

    std::unordered_map<std::string, entities::archetype_properties> r;
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
    const physical::entities::meta_name_repository& nrp,
    entities::model& m) {

    const auto bftg(make_backend_feature_group(fm, nrp));
    const auto fftg(make_facet_feature_group(fm, nrp));
    const auto aftg(make_global_archetype_feature_group(fm, nrp));

    const auto& cfg(*m.root_module()->configuration());
    auto& galp(m.global_enablement_properties());
    galp.backend_properties(obtain_backend_properties(bftg, cfg));
    galp.facet_properties(obtain_facet_properties(fftg, cfg));
    galp.archetype_properties(obtain_archetype_properties(aftg, cfg));

    /*
     * Now populate the denormalised archetype properties by querying
     * the containers we've already populated.
     */
    for (const auto& backend_pair : nrp.by_backend_by_facet()) {
        /*
         * First we locate the backend for the current batch of
         * physical locations.
         */
        const auto& bn(backend_pair.first);
        const auto i(galp.backend_properties().find(bn));
        if (i == galp.backend_properties().end()) {
            BOOST_LOG_SEV(lg, error) << backend_not_found << bn;
            BOOST_THROW_EXCEPTION(transformation_error(backend_not_found + bn));
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
                    transformation_error(facet_not_found + fn));
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
                        transformation_error(archetype_not_found + an));
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

std::unordered_map<std::string, logical::entities::enablement_properties>
global_enablement_transform::obtain_local_enablement_properties(
    const std::unordered_map<std::string, local_archetype_feature_group>& fgs,
    const std::list<physical::entities::meta_name>& mns,
    const variability::entities::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Creating global enablement properties.";

    std::unordered_map<std::string, logical::entities::enablement_properties> r;
    const variability::helpers::configuration_selector s(cfg);
    for (const auto& mn : mns) {
        const auto archetype(mn.qualified());
        const auto i(fgs.find(archetype));
        if (i == fgs.end()) {
            BOOST_LOG_SEV(lg, error) << type_group_not_found << archetype;
            BOOST_THROW_EXCEPTION(
                transformation_error(type_group_not_found + archetype));
        }
        const auto fg(i->second);

        logical::entities::enablement_properties lalp;
        if (s.has_configuration_point(fg.facet_enabled)) {
            lalp.facet_enabled(
                s.get_boolean_content_or_default(fg.facet_enabled));
        }

        if (s.has_configuration_point(fg.archetype_enabled)) {
            lalp.archetype_enabled(
                s.get_boolean_content_or_default(fg.archetype_enabled));
        }

        if (s.has_configuration_point(fg.facet_overwrite))
            lalp.facet_overwrite(s.get_boolean_content(fg.facet_overwrite));

        if (s.has_configuration_point(fg.archetype_overwrite)) {
            lalp.archetype_overwrite(
                s.get_boolean_content(fg.archetype_overwrite));
        }

        r[archetype] = lalp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created global enablement properties.";
    return r;
}

void global_enablement_transform::populate_local_enablement_properties(
    const variability::entities::feature_model& fm,
    const physical::entities::meta_name_repository& nrp,
    entities::model& m) {
    /*
     * Computes all of the possible features for every physical
     * location. Not all of these will be of use to a given element,
     * because they may not be expressed for that element.
     */
    const auto fgs(make_local_archetype_feature_group(fm, nrp));

    /*
     * Bucket all elements by their meta-name.
     */
    std::unordered_map<std::string,
                       std::list<boost::shared_ptr<logical::entities::element>>>
        bucketed_elements;
    for (auto ea : m.elements()) {
        auto ptr(ea.element());
        const auto& mn(ptr->meta_name());
        bucketed_elements[mn.qualified().dot()].push_back(ptr);
    }

    for (auto& pair : bucketed_elements) {
        /*
         * Locate all of the physical locations that make sense for
         * the current meta-name. If none do, there nothing for us to
         * do here. This can happen if the meta-model element is not
         * expressed as an artefact at all. This is the case, for
         * example, for object templates (at the time of this
         * writing).
         */
        const auto mn_id(pair.first);
        const auto& lmn(nrp.by_logical_meta_name());
        const auto i(lmn.find(mn_id));
        if (i == lmn.end())
            continue;

        const auto& ns(i->second.meta_names());

        /*
         * Now process each of the elements of this meta-feature, only
         * taking into account the physical locations relevant to the
         * meta-feature.
         */
        for (auto ptr : pair.second) {
            auto& e(*ptr);
            const auto& cfg(*e.configuration());
            e.enablement_properties(
                obtain_local_enablement_properties(fgs, ns, cfg));
        }
    }
}

void global_enablement_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "global enablement transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto &fm(*ctx.feature_model());
    const auto& pmm(*ctx.physical_meta_model());
    const auto& nrp(pmm.kernels().cbegin()->second.names());
    populate_global_enablement_properties(fm, nrp, m);
    populate_local_enablement_properties(fm, nrp, m);

    stp.end_transform(m);
}

}
