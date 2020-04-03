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
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/types/entities/name_repository.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.m2t/io/entities/model_io.hpp"
#include "dogen.m2t/io/entities/facet_properties_io.hpp"
#include "dogen.m2t/types/transforms/transformation_error.hpp"
#include "dogen.m2t/types/transforms/local_enablement_transform.hpp"

namespace {

const std::string transform_id("m2t.transforms.local_enablement_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string global_configuration_not_found(
    "Could not find global enablement configuration for formatter: ");
const std::string duplicate_archetype_name("Duplicate archetype name: ");
const std::string duplicate_element_archetype("Duplicate element archetype: ");
const std::string meta_name_not_found("Meta-name not found: ");

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

namespace dogen::m2t::transforms {

bool local_enablement_transform::
is_element_disabled(const logical::entities::element& e) {
    /*
     * We're only interested in modules as these are the only elements
     * that can be enabled/disabled based on their state.
     */
    using logical::entities::structural::module;
    const auto ptr(dynamic_cast<const module*>(&e));
    if (!ptr)
        return false;

    const auto& m(*ptr);

    /*
     * Ignore the global module. This is just a pseudo module that is
     * used as a top-level container and has no expression in code.
     */
    if (m.is_global_module())
        return true;

    /*
     * Modules are only generatable for the purposes of
     * documentation. Set them to disabled if there is no
     * documentation.
     */
    if (m.documentation().empty()) {
        BOOST_LOG_SEV(lg, trace) << "Module does not have documentation. "
                                 << "Disabling it. Id: "
                                 << m.name().qualified().dot();
        return true;
    }
    return false;
}

void local_enablement_transform::compute_enablement_for_artefact_properties(
    const std::unordered_map<std::string,
    entities::denormalised_archetype_properties>&
    global_enablement_properties,
    const std::unordered_map<std::string,
    logical::entities::enablement_properties>&
    local_enablement_properties,
    const std::string& archetype,
    logical::entities::artefact_properties& ap) {

    const auto& galp(global_enablement_properties);
    const auto& lalp(local_enablement_properties);

    /*
     * As we may be processing a segmented entity, not all formatting
     * needs to be present in the local configuration. For example, an
     * entity may be segmented into an object and a forward
     * declaration; in this case, when we are processing the object,
     * we will still see the forward declaration formatting in the
     * formattable configuration since the transformer merged all
     * segments of the element together. However, these are not
     * present in the local configuration container because we are
     * only processing one segment at a time. So, we need to ignore
     * the formatting for the segments we are not processing.
     * FIXME: check this when element extension is removed.
     */
    const auto j(lalp.find(archetype));
    if (j == lalp.end()) {
        BOOST_LOG_SEV(lg, trace) << "Ignoring formatter: " << archetype;
        return;
    }
    const auto& lc(j->second);

    /*
     * Global configuration must always be present for all archetypes.
     */
    const auto i(galp.find(archetype));
    if (i == galp.end()) {
        BOOST_LOG_SEV(lg, error) << global_configuration_not_found << archetype;
        BOOST_THROW_EXCEPTION(
            transformation_error(global_configuration_not_found + archetype));
    }
    const auto gc(i->second);

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
     * done via a profile, but can be conceivable be done directly for
     * less common configurations - for example adding manual support
     * for IO for a handcrafted type. The global archetype overwrite
     * flag is a bit less useful - we haven't got a use case for it
     * just yet but it is added for (foolish) consistency. Finally,
     * the global facet level overwrite flag is useful for the general
     * case of code generated code. Having said that, it does not make
     * a lot of sense to set overwrite globally to false.
     *
     * Note that the overwrite flag is only relevant if enabled is
     * true. It is not used otherwise. We set it up before enablement
     * just so we don't have to worry about handling the ""continue""
     * statements.
     */
    auto lambda(
        [&](auto& optional_flag) {
            std::ostringstream s;
            if (optional_flag)
                s << *optional_flag;
            else
                s << "<empty>";
            return s.str();
        });
    BOOST_LOG_SEV(lg, trace) << "Overwrite flags. "
                             << "Local artchetype: "
                             << lambda(lc.archetype_overwrite())
                             << " Local facet: "
                             << lambda(lc.facet_overwrite())
                             << " Global archetype: "
                             << lambda(gc.archetype_overwrite())
                             << " Global facet: "
                             << gc.facet_overwrite();

    if (lc.archetype_overwrite())
        ap.overwrite(*lc.archetype_overwrite());
    else if (lc.facet_overwrite())
        ap.overwrite(*lc.facet_overwrite());
    else if (gc.archetype_overwrite())
        ap.overwrite(*gc.archetype_overwrite());
    else
        ap.overwrite(gc.facet_overwrite());

    /*
     * Ensure we log the enablement details with the early returns.
     */
    auto log_scope_exit(make_scope_exit(
        [&]() mutable {
            BOOST_LOG_SEV(lg, trace) << "Enablement for: " << archetype
                                     << " value: " << ap.enabled()
                                     << " overwrite: " << ap.overwrite();
        }));

    /*
     * If the entire backend has been disabled globally, the formatter
     * will be disabled too.
     */
    if (!gc.backend_enabled()) {
        BOOST_LOG_SEV(lg, trace) << "Backend is disabled.";
        ap.enabled(false);
        return;
    }

    /*
     * Check to see if the formatter enablement field has been set
     * locally. If so, it takes precedence over the facet
     * configuration.
     */
    if (lc.archetype_enabled()) {
        ap.enabled(*lc.archetype_enabled());
        return;
    }

    /*
     * Check to see if the facet enablement field has been set
     * locally. If so, it takes precedence over global
     * configuration.
     */
    if (lc.facet_enabled()) {
        ap.enabled(*lc.facet_enabled());
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
     * enabled. This means that you cannot switch off a facet globally
     * but enable only one archetype for that facet. As this seems
     * like a pretty far-fetched use case, we ignore it for now.
     */
    if (gc.archetype_enabled() == false)
        ap.enabled(false);
    else
        ap.enabled(gc.facet_enabled() && gc.archetype_enabled());
}

void local_enablement_transform::compute_enablement_for_element(
    const std::unordered_map<std::string,
    physical::entities::name_group>& physical_names_by_meta_name,
    const std::unordered_map<std::string,
    entities::denormalised_archetype_properties>&
    global_enablement_properties,
    std::unordered_set<entities::element_archetype>&
    enabled_archetype_for_element, logical::entities::element& e) {

    const auto id(e.name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Started computing enablement: " << id;

    /*
     * On some very special cases we may disable an element based on
     * its state. If so, there is nothing to do.
     */
    if (is_element_disabled(e)) {
        BOOST_LOG_SEV(lg, trace) << "Element is disabled due to its state.";
        return;
    }

    const auto mt(e.meta_name().qualified().dot());
    BOOST_LOG_SEV(lg, trace) << "Meta-type: " << mt;

    /*
     * Not all elements have formatting. For example, object templates
     * do not have any at present. This manifests itself as an absence
     * of archetype locations mapped against this element. If it is
     * so, skip the element.
     */
    if (e.enablement_properties().empty()) {
        BOOST_LOG_SEV(lg, trace) << "Element has no formatting, "
                                 << " so nothing enable.";
        return;
    }

    const auto& mn(e.meta_name());
    const auto j(physical_names_by_meta_name.find(mn.qualified().dot()));
    if (j == physical_names_by_meta_name.end()) {
        BOOST_LOG_SEV(lg, error) << meta_name_not_found << mn.qualified().dot();
        BOOST_THROW_EXCEPTION(
            transformation_error(meta_name_not_found + mn.qualified().dot()));
    }
    const auto& cal(j->second.canonical_locations());

    /*
     * Now, for each element, obtain the global and local
     * configuration.
     */
    const auto& galp(global_enablement_properties);
    const auto lalp(e.enablement_properties());

    /*
     * Once we got both the global and the local configuration, we can
     * then compute the enablement values for this formattable, across
     * all the supported formatters.
     */
    auto& eafe(enabled_archetype_for_element);
    for (auto& pair : e.artefact_properties()) {
        const auto arch(pair.first);
        BOOST_LOG_SEV(lg, trace) << "Processing archetype: " << arch;

        auto& art_props(pair.second);
        compute_enablement_for_artefact_properties(galp, lalp, arch, art_props);

        if (!art_props.enabled()) {
            BOOST_LOG_SEV(lg, trace) << "Archetype not enabled.";
            continue;
        }

        BOOST_LOG_SEV(lg, trace) << "Archetype is enabled.";

        /*
         * If we are enabled, we need to update the enablement
         * index. First, we update it with the concrete archetype.
         */
        using entities::element_archetype;
        auto inserted(eafe.insert(element_archetype(id, arch)).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element_archetype << arch
                                     << " " << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_archetype_name
                    + arch + " " + id));
        }

        /*
         * Then, if this archetype maps to a canonical archetype, we
         * create an entry for the canonical archetype as well.
         */
        const auto k(cal.find(arch));
        if (k == cal.end())
            continue;

        inserted = eafe.insert(element_archetype(id, k->second)).second;
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element_archetype << arch
                                     << " " << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_archetype_name
                    + arch + " " + id));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished computing enablement.";
}

void local_enablement_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "enablement new_transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& pmm(*ctx.physical_meta_model());
    const auto& nrp(pmm.kernels().cbegin()->second.names());
    const auto& albmn(nrp.by_meta_name());
    const auto& galp(m.global_enablement_properties()
        .denormalised_archetype_properties());
    std::unordered_set<entities::element_archetype> eafe;
    for(auto& pair : m.elements()) {
        auto& e(*pair.logical_element());
        compute_enablement_for_element(albmn, galp, eafe, e);
    }

    m.enabled_archetype_for_element(eafe);
    stp.end_transform(m);
}

}
