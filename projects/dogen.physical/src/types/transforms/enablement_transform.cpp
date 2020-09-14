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
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.identification/types/entities/physical_meta_name_indices.hpp"
#include "dogen.physical/io/entities/artefact_repository_io.hpp"
#include "dogen.physical/io/entities/facet_properties_io.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/enablement_transform.hpp"

namespace {

const std::string transform_id("physical.transforms.enablement_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

static std::string enabled_feature("enabled");
static std::string overwrite_feature("overwrite");

const std::string null_artefact("Artefact cannot be null: ");
const std::string global_configuration_not_found(
    "Could not find global enablement configuration for formatter: ");
const std::string duplicate_archetype_name("Duplicate archetype name: ");
const std::string duplicate_element_archetype("Duplicate element archetype: ");
const std::string logical_meta_id_not_found("Logical meta ID not found: ");
const std::string missing_configuration(
    "Configuration not available for element: ");
const std::string type_group_not_found(
    "Could not find a type group for archetype: ");

template <typename T>
struct scope_exit {
    scope_exit(T &&t) : t_{std::move(t)} {}
    ~scope_exit() { t_(); }
    T t_;
};

template <typename T>
scope_exit<T> make_scope_exit(T &&t) {
    return scope_exit<T> { std::move(t)}; }
}


namespace dogen::physical::transforms {

using variability::entities::feature_model;
using identification::entities::physical_meta_id;
using identification::entities::physical_meta_name_indices;
using identification::entities::logical_meta_physical_id;

std::unordered_map<physical_meta_id, enablement_transform::feature_group>
enablement_transform::make_feature_group(const feature_model& fm,
    const physical_meta_name_indices& idx) {
    const auto& ef(enabled_feature);
    const auto& of(overwrite_feature);
    const variability::helpers::feature_selector s(fm);
    identification::helpers::physical_meta_id_builder b;
    std::unordered_map<physical_meta_id, feature_group> r;

    /*
     * For each archetype, obtain its facet. Then for the pair facet
     * and archetype, create a feature group for all of the relevant
     * properties. Note that we compute all of the possible features
     * for every physical location. Not all of these will be of use to
     * a given element, because they may not be expressed for that
     * element.
     */
    for (const auto& arch_pmn : idx.all()) {
        feature_group fg;
        const auto arch_pmid(arch_pmn.id());
        const auto fct_pmid(b.build_facet(arch_pmn));

        fg.facet_enabled = s.get_by_name(fct_pmid.value(), ef);
        fg.archetype_enabled = s.get_by_name(arch_pmid.value(), ef);

        fg.facet_overwrite = s.get_by_name(fct_pmid.value(), of);
        fg.archetype_overwrite = s.get_by_name(arch_pmid.value(), of);

        r.insert(std::make_pair(arch_pmid, fg));
    }
    return r;
}

void enablement_transform::populate_enablement_properties(
    const std::unordered_map<identification::entities::physical_meta_id,
    feature_group>& fgs, entities::artefact_repository& ar) {
    for (auto& as_pair : ar.artefact_sets_by_logical_id()) {
        const auto lid(as_pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing: " << lid;

        auto& as(as_pair.second);
        if (!as.configuration()) {
            BOOST_LOG_SEV(lg, error) << missing_configuration << lid;
            BOOST_THROW_EXCEPTION(
                transform_exception(missing_configuration + lid.value()));
        }

        /*
         * Obtain the feature group associated with a given point in
         * physical space and then read its configuration related to
         * enablement. Note that all archetypes are expected to have a
         * feature group.
         */
        const auto& cfg(*as.configuration());
        const variability::helpers::configuration_selector s(cfg);
        for (auto& a_pair : as.artefacts_by_archetype()) {
            auto& a(*a_pair.second);
            const auto pmid(a.meta_name().id());
            const auto i(fgs.find(pmid));
            if (i == fgs.end()) {
                BOOST_LOG_SEV(lg, error) << type_group_not_found << pmid;
                BOOST_THROW_EXCEPTION(transform_exception(
                        type_group_not_found + pmid.value()));
            }
            const auto& fg(i->second);
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

void enablement_transform::compute_enablement_for_artefact(
    const entities::denormalised_archetype_properties&
    global_enablement_properties,
    const physical_meta_id& archetype, entities::artefact& a) {

    const auto& gc(global_enablement_properties);
    const auto& lc(a.enablement_properties());

    /*
     * If the overwrite flag is set locally at the archetype or facet
     * level, then that takes priority. If not, first check to see if
     * its set globally at the archetype level; if so, it takes
     * priority. Finally, if nothing else is set, use the global facet
     * default.
     *
     * The rationale here is as follows: users can set facets to
     * overwrite locally on a model element (either directly of via
     * profiles); for example, for an handcrafted class, we want to
     * set overwrite to false at the element level. This is normally
     * done via a profile, but can be conceivably done at the element
     * level for less common configurations - for example, by adding
     * manual support for IO for a handcrafted type. The global
     * archetype overwrite flag is a bit less useful - we haven't got
     * a use case for it just yet but it is added for (foolish)
     * consistency. Finally, the global facet level overwrite flag is
     * useful for the general case of code generated code (e.g. we
     * want to always overwrite). Having said that, it does not make a
     * lot of sense to set overwrite globally to false.
     *
     * Also, note that the overwrite flag is only relevant if enabled
     * is true. It is not used otherwise. We set it up before
     * enablement just so we don't have to worry about handling the
     * "continue" statements.
     */
    auto lambda([&](auto& optional_flag) {
            std::ostringstream s;
            if (optional_flag)
                s << *optional_flag;
            else
                s << "<empty>";
            return s.str();
        });
    BOOST_LOG_SEV(lg, trace) << "Overwrite flags. Local archetype: "
                             << lambda(lc.archetype_overwrite())
                             << " Local facet: "
                             << lambda(lc.facet_overwrite())
                             << " Global archetype: "
                             << lambda(gc.archetype_overwrite())
                             << " Global facet: "
                             << gc.facet_overwrite();

    if (lc.archetype_overwrite())
        a.overwrite(*lc.archetype_overwrite());
    else if (lc.facet_overwrite())
        a.overwrite(*lc.facet_overwrite());
    else if (gc.archetype_overwrite())
        a.overwrite(*gc.archetype_overwrite());
    else
        a.overwrite(gc.facet_overwrite());

    /*
     * Ensure we log the enablement details with the early returns.
     */
    auto log_scope_exit(make_scope_exit([&]() mutable {
            BOOST_LOG_SEV(lg, trace) << "Enablement for: " << archetype
                                     << " value: " << a.enabled()
                                     << " overwrite: " << a.overwrite();
        }));

    /*
     * If the entire backend has been disabled globally, the formatter
     * will be disabled too.
     */
    if (!gc.backend_enabled()) {
        BOOST_LOG_SEV(lg, trace) << "Backend is disabled.";
        a.enabled(false);
        return;
    }

    /*
     * Check to see if the formatter enablement field has been set
     * locally. If so, it takes precedence over the facet
     * configuration.
     */
    if (lc.archetype_enabled()) {
        a.enabled(*lc.archetype_enabled());
        return;
    }

    /*
     * Check to see if the facet enablement field has been set
     * locally. If so, it takes precedence over global configuration.
     *
     * It is important to note the role of profiles here. It makes
     * very little sense to have a "local" *facet* enablement or
     * overwrite properties - why would you want to enable or disable
     * a facet on a given archetype? After all you know the
     * archetype's name already, you are on it. But when you think of
     * it from a profile viewpoint, then it makes sense: you don't
     * want to have to deal with individual archetypes when defining
     * profiles, you just want to make blanket statements about
     * enablement at the facet level - else you'd end up having to
     * describe every single archetype the profile could possibly
     * apply to. So its kind of "local" but really more like "profile
     * level local".
     */
    if (lc.facet_enabled()) {
        a.enabled(*lc.facet_enabled());
        return;
    }

    /*
     * If nothing else has been set, use the global enablement flag
     * for the facet and archetypes. Note that this logic is one big
     * hack. We used to rely on the archetype enablement, but since it
     * defaults to true, it means we ignore the global facet settings;
     * this in turn means its not possible to globally switch off a
     * facet. So the new logic instead works as follows: if the
     * archetype has been switched off globally, we honour that
     * first. This is for cases such as visual studio solutions etc
     * that tend to be manually disabled. However, since archetypes
     * default to enabled, we can't just directly rely on that when
     * set to true. So we check to make sure the facet itself is
     * enabled. This means that you cannot globally switch off a facet
     * but enable only one archetype for that facet. As this seems
     * like a pretty far-fetched use case, we ignore it for now. We of
     * course support this scenario for local enablement, which is
     * very common.
     */
    a.enabled(gc.archetype_enabled() && gc.facet_enabled());
}

void enablement_transform::compute_enablement_for_artefact_set(
    const std::unordered_map<identification::entities::logical_meta_id,
    identification::entities::archetype_name_set>& pmn_by_lmid,
    const std::unordered_map<physical_meta_id,
    entities::denormalised_archetype_properties>& global_enablement_properties,
    std::unordered_set<logical_meta_physical_id>& enabled_archetype_for_element,
    entities::artefact_set& as) {

    const auto lid(as.provenance().logical_name().id());
    BOOST_LOG_SEV(lg, debug) << "Started computing enablement: " << lid;

    /*
     * Some logical elements do not project into the physical
     * dimension. If so, there is nothing to do.
     */
    if (!as.is_generatable()) {
        BOOST_LOG_SEV(lg, trace) << "Element is not generatable.";
        return;
    }

    /*
     * Locate all of the physical meta-names associated with a given
     * logical meta ID; in other words, find the archetypes for a
     * given logical meta-element. Note that the archetype name set is
     * always expected to exist, even if it is empty.
     */
    const auto lmid(as.provenance().logical_meta_name().id());
    BOOST_LOG_SEV(lg, trace) << "Logical meta ID: " << lmid;
    const auto i(pmn_by_lmid.find(lmid));
    if (i == pmn_by_lmid.end()) {
        BOOST_LOG_SEV(lg, error) << logical_meta_id_not_found << lmid;
        BOOST_THROW_EXCEPTION(
            transform_exception(logical_meta_id_not_found + lmid.value()));
    }
    const auto& cal(i->second.canonical_locations());

    /*
     * Now go through all of the artefacts in the artefact set and for
     * each, compute their enablement properties.
     */
    for(auto& pair : as.artefacts_by_archetype()) {
        const auto pmid(pair.first);
        BOOST_LOG_SEV(lg, trace) << "Processing artefact for archetype: "
                                 << pmid;

        /*
         * Ensure artefact looks vaguely sane.
         */
        if (!pair.second) {
            BOOST_LOG_SEV(lg, error) << null_artefact << pmid;
            BOOST_THROW_EXCEPTION(
                transform_exception(null_artefact + pmid.value()));
        }
        auto& a(*pair.second);

        /*
         * Global enablement must always be present for all
         * archetypes.
         */
        const auto i(global_enablement_properties.find(pmid));
        if (i == global_enablement_properties.end()) {
            BOOST_LOG_SEV(lg, error) << global_configuration_not_found << pmid;
            BOOST_THROW_EXCEPTION(transform_exception(
                    global_configuration_not_found + pmid.value()));
        }
        const auto& gep(i->second);

        /*
         * Compute the enablement values for this artefact. If it is
         * not enabled there is no much to be done so bomb out.
         */
        compute_enablement_for_artefact(gep, pmid, a);
        if (!a.enabled()) {
            BOOST_LOG_SEV(lg, trace) << "Artefact not enabled.";
            continue;
        }

        /*
         * If we are enabled, we need to update the enablement
         * index. First, we update it with the concrete archetype.
         */
        BOOST_LOG_SEV(lg, trace) << "Artefact is enabled.";
        auto& eafe(enabled_archetype_for_element);
        auto inserted(eafe.insert(logical_meta_physical_id(lid, pmid)).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element_archetype << pmid
                                     << " " << lid;
            BOOST_THROW_EXCEPTION(transform_exception(duplicate_archetype_name
                    + pmid.value() + " " + lid.value()));
        }

        /*
         * Then, if this archetype maps to a canonical archetype, we
         * create an entry for the canonical archetype as well.
         */
        const auto j(cal.find(pmid));
        if (j == cal.end())
            continue;

        inserted = eafe.insert(logical_meta_physical_id(lid, j->second)).second;
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element_archetype << pmid
                                     << " " << lid;
            BOOST_THROW_EXCEPTION(transform_exception(duplicate_archetype_name
                    + pmid.value() + " " + lid.value()));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished computing enablement.";
}

void enablement_transform::
apply(const context& ctx, entities::artefact_repository& arp) {
    tracing::scoped_transform_tracer stp(lg, "enablement",
        transform_id, arp.identifier(), *ctx.tracer(), arp);

    /*
     * First, we update all of the local enablement properties from
     * configuration. The global properties have been updated as part
     * of the meta-model properties transform.
     */
    const auto& fm(*ctx.feature_model());
    const auto& pmm(*ctx.meta_model());
    const auto& in(pmm.indexed_names());
    const auto fgs(make_feature_group(fm, in));
    populate_enablement_properties(fgs, arp);

    /*
     * Now, for each artefact, compute their enablement properties.
     */
    const auto& mmp(arp.meta_model_properties());
    const auto& dap(mmp.denormalised_archetype_properties());
    const auto& lmn(in.archetype_names_by_logical_meta_name());
    std::unordered_set<logical_meta_physical_id> eafe;
    for(auto& pair : arp.artefact_sets_by_logical_id()) {
        auto& as(pair.second);
        compute_enablement_for_artefact_set(lmn, dap, eafe, as);
    }

    /*
     * The very badly named archetype for element container keeps
     * track of which archetypes are enable for a given logical
     * element. However, we seem to only remember those which are
     * canonical. This code will be cleaned up with the new
     * dependencies approach.
     */
    arp.enabled_archetype_for_element(eafe);

    stp.end_transform(arp);
}

}
