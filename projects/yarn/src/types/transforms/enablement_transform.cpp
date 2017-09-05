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
#include <functional>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/typeindex_io.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/types/meta_model/elements_traversal.hpp"
#include "dogen/yarn/io/meta_model/facet_properties_io.hpp"
#include "dogen/yarn/io/transforms/local_enablement_configuration_io.hpp"
#include "dogen/yarn/io/transforms/global_enablement_configuration_io.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/enablement_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.enablement_transform"));

const std::string global_configuration_not_found(
    "Could not find global enablement configuration for formatter: ");
const std::string duplicate_archetype_name("Duplicate archetype name: ");
const std::string archetype_not_found("Archetype not found: ");
const std::string incompatible_facet(
    "Facet is not compatible with C++ standard chosen: ");
const std::string element_not_found("Element not found: ");
const std::string default_value_unset("Default value not set for field: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

inline std::ostream& operator<<(std::ostream& s,
    const enablement_transform::global_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform::"
      << "enablement_transform::global_type_group\"" << ", "
      << "\"kernel_enabled\": " << v.kernel_enabled << ", "
      << "\"facet_enabled\": " << v.facet_enabled << ", "
      << "\"archetype_enabled\": " << v.archetype_enabled
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s,
    const enablement_transform::local_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform"
      << "enablement_transform::local_type_group\"" << ", "
      << "\"facet_enabled\": " << v.facet_enabled << ", "
      << "\"archetype_enabled\": " << v.archetype_enabled << ", "
      << "\"supported\": " << v.facet_supported
      << " }";

    return s;
}

enablement_transform::global_type_group_type enablement_transform::
make_global_type_group(const annotations::type_repository& atrp,
    const std::list<annotations::archetype_location>& als) {

    BOOST_LOG_SEV(lg, debug) << "Creating global type group.";

    global_type_group_type r;
    const annotations::type_repository_selector s(atrp);
    for (const auto& al : als) {
        global_type_group gtg;
        const auto ebl(traits::enabled());
        gtg.kernel_enabled = s.select_type_by_name(al.kernel(), ebl);
        gtg.facet_enabled = s.select_type_by_name(al.facet(), ebl);
        gtg.archetype_enabled = s.select_type_by_name(al.archetype(), ebl);

        const auto ow(traits::overwrite());
        gtg.facet_overwrite = s.select_type_by_name(al.facet(), ow);
        gtg.archetype_overwrite = s.select_type_by_name(al.archetype(), ow);

        gtg.facet_name = al.facet();

        r[al.archetype()] = gtg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created global type group. Result: " << r;
    return r;
}

enablement_transform::global_enablement_configurations_type
enablement_transform::obtain_global_configurations(
    const std::unordered_map<std::string, global_type_group>& gtg,
    const annotations::annotation& ra) {

    BOOST_LOG_SEV(lg, debug) << "Creating global enablement configuration.";

    global_enablement_configurations_type r;
    const annotations::entry_selector s(ra);
    for (const auto& pair : gtg) {
        const auto& arch(pair.first);
        const auto& t(pair.second);

        global_enablement_configuration gec;
        gec.kernel_enabled(s.get_boolean_content_or_default(t.kernel_enabled));
        gec.facet_enabled(s.get_boolean_content_or_default(t.facet_enabled));
        gec.facet_name(t.facet_name);
        gec.archetype_enabled(
            s.get_boolean_content_or_default(t.archetype_enabled));
        gec.facet_overwrite(
            s.get_boolean_content_or_default(t.facet_overwrite));

        if (s.has_entry(t.archetype_overwrite)) {
            gec.archetype_overwrite(
                s.get_boolean_content(t.archetype_overwrite));
        }

        r[arch] = gec;
    }

    BOOST_LOG_SEV(lg, debug) << "Created global enablement configuration. "
                             << "Result: " << r;
    return r;
}

void enablement_transform::update_facet_enablement(
    const std::list<annotations::archetype_location>& als,
    const global_enablement_configurations_type& gcs,
    meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Updating facet enablement.";

    /*
     * For each formatter in our global configurations: find the facet
     * to which the formatter belongs to, and update the enablement
     * value of that facet in the main facet container.
     *
     * Note that this is all a bit silly - we're doing this N times
     * for one facet - where N is the number of formatters for that
     * facet - rather than just read the facet field and update it
     * once.
     *
     * FIXME: read facet fields here instead of reusing configuration.
     */
    const auto archetype_to_facet([&]() {
            std::unordered_map<std::string, std::string> r;
            for (const auto& al : als)
                r[al.archetype()] = al.facet();
            return r;
        }());

    for (const auto& pair : gcs) {
        const auto arch(pair.first);
        const auto i(archetype_to_facet.find(arch));
        if (i == archetype_to_facet.end()) {
            BOOST_LOG_SEV(lg, error) << archetype_not_found << arch;
            BOOST_THROW_EXCEPTION(
                transformation_error(archetype_not_found + arch));
        }

        const auto& fct(i->second);
        const auto& gc(pair.second);
        im.facet_properties()[fct].enabled(gc.facet_enabled());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished updating facet enablement."
                             << "Result: " << im.facet_properties();
}

enablement_transform::local_type_group_type enablement_transform::
make_local_type_group(const annotations::type_repository& atrp,
    const std::list<annotations::archetype_location>& als) {

    BOOST_LOG_SEV(lg, debug) << "Creating local type grup.";

    local_type_group_type r;
    const annotations::type_repository_selector s(atrp);
    for (const auto& al : als) {
        const auto& fct(al.facet());
        const auto ebl(traits::enabled());

        local_type_group ltg;
        ltg.facet_enabled = s.select_type_by_name(fct, ebl);

        const auto& arch(al.archetype());
        ltg.archetype_enabled = s.select_type_by_name(arch, ebl);

        const auto ow(traits::overwrite());
        ltg.facet_overwrite = s.select_type_by_name(fct, ow);
        ltg.archetype_overwrite = s.select_type_by_name(arch, ow);
        ltg.facet_supported = s.select_type_by_name(fct, traits::supported());
        r[arch] = ltg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created local type group. Result: " << r;
    return r;
}

std::unordered_map<std::string, enablement_transform::local_type_group_type>
enablement_transform::bucket_local_type_group_by_meta_name(
    const local_type_group_type& unbucketed_ltgs,
    const std::unordered_map<std::string,
    std::list<annotations::archetype_location>>&
    archetype_locations_by_meta_name) {

    BOOST_LOG_SEV(lg, debug) << "Started bucketing local field definitions "
                             << "by meta name.";
    std::unordered_map<std::string, local_type_group_type> r;

    for (const auto& pair: archetype_locations_by_meta_name) {
        const auto& mt(pair.first);
        const auto& als(pair.second);

        local_type_group_type& ltg(r[mt]);
        for (const auto& al : als) {
            const auto arch(al.archetype());
            const auto i(unbucketed_ltgs.find(arch));
            if (i == unbucketed_ltgs.end()) {
                BOOST_LOG_SEV(lg, error) << archetype_not_found << arch;
                BOOST_THROW_EXCEPTION(
                    transformation_error(archetype_not_found + arch));
            }

            const auto& unbucketed_ltg(i->second);
            const auto pair(std::make_pair(arch, unbucketed_ltg));
            const auto inserted(ltg.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_archetype_name << arch;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_archetype_name + arch));
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished bucketing local field definitions "
                             << "by type index. Result: " << r;
    return r;
}

enablement_transform::local_enablement_configurations_type
enablement_transform::
obtain_local_configurations(const local_type_group_type& ltg,
    const annotations::annotation& o) {

    BOOST_LOG_SEV(lg, debug) << "Obtaining local configurations.";
    local_enablement_configurations_type r;
    const annotations::entry_selector s(o);
    for (const auto& pair : ltg) {
        const auto& arch(pair.first);
        const auto& t(pair.second);

        local_enablement_configuration lec;
        if (s.has_entry(t.facet_enabled))
            lec.facet_enabled(s.get_boolean_content(t.facet_enabled));

        if (s.has_entry(t.archetype_enabled))
            lec.archetype_enabled(s.get_boolean_content(t.archetype_enabled));

        if (s.has_entry(t.facet_overwrite))
            lec.facet_overwrite(s.get_boolean_content(t.facet_overwrite));

        if (s.has_entry(t.archetype_overwrite))
            lec.archetype_overwrite(
                s.get_boolean_content(t.archetype_overwrite));

        r[arch] = lec;
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained local configurations. Result: " << r;
    return r;
}

bool enablement_transform::
is_element_disabled(const yarn::meta_model::element& e) {
    /*
     * We're only interested in modules as these are the only elements
     * that can be enabled/disabled based on their state.
     */
    const auto ptr(dynamic_cast<const yarn::meta_model::module*>(&e));
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
        BOOST_LOG_SEV(lg, debug) << "Module does not have documentation. "
                                 << "Disabling it. Id: " << m.name().id();
        return true;
    }
    return false;
}

void enablement_transform::compute_enablement_for_artefact_properties(
    const global_enablement_configurations_type& gcs,
    const local_enablement_configurations_type& lcs,
    const std::string& archetype, meta_model::artefact_properties& ap) {
    /*
     * As we may be processing a segmented entity, not all formatters
     * need to be present in the local configuration. For example, an
     * entity may be segmented into an object and a forward
     * declaration; in this case, when we are processing the object,
     * we will still see the forward declaration formatters in the
     * formattable configuration since the transformer merged all
     * segments of the element together. However, these are not
     * present in the local configuration container because we are
     * only processing one segment at a time. So, we need to ignore
     * the formatters for the segments we are not processing.
     */
    const auto j(lcs.find(archetype));
    if (j == lcs.end()) {
        BOOST_LOG_SEV(lg, debug) << "Ignoring formatter: " << archetype;
        return;
    }
    const auto& lc(j->second);

    /*
     * Global configuration must always be present for all archetypes.
     */
    const auto i(gcs.find(archetype));
    if (i == gcs.end()) {
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

    if (lc.archetype_overwrite())
        ap.overwrite(*lc.archetype_overwrite());
    else if (lc.facet_overwrite())
        ap.overwrite(*lc.facet_overwrite());
    else if (gc.archetype_overwrite())
        ap.overwrite(*gc.archetype_overwrite());
    else
        ap.overwrite(gc.facet_overwrite());

    /*
     * If either the entire kernel or facet have been disabled
     * globally, the formatter will be disabled too.
     */
    if (!gc.kernel_enabled() || !gc.facet_enabled()) {
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
     * If nothing else has been set, use the global enablement
     * flag for the formatter.
     */
    ap.enabled(gc.archetype_enabled());
    BOOST_LOG_SEV(lg, debug) << "Enablement for: " << archetype
                             << " value: " << ap.enabled();
}

void enablement_transform::compute_enablement_for_element(
    const global_enablement_configurations_type& gcs,
    const std::unordered_map<std::string, local_type_group_type>& ltgmt,
    meta_model::element& e) {

    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Started computing enablement: " << id;

    /*
     * On some very special cases we may disable an element based on
     * its state. If so, there is nothing to do.
     */
    if (is_element_disabled(e))
        return;

    const auto mt(e.meta_name().id());
    BOOST_LOG_SEV(lg, debug) << "Meta-type: " << mt;

    /*
     * Not all elements have formatters; for example, object templates
     * don't have any at present. If so, skip the element.
     */
    const auto i(ltgmt.find(mt));
    if (i == ltgmt.end()) {
        BOOST_LOG_SEV(lg, debug) << "Element has no formatters, "
                                 << " so nothing enable.";
        return;
    }

    /*
     * Now, for each element segment, find the corresponding local
     * types and use those to obtain the local configuration.
     */
    const auto& t(i->second);
    auto lcs(obtain_local_configurations(t, e.annotation()));

    /*
     * Once we got both the global and the local configuration, we can
     * then compute the enablement values for this formattable, across
     * all the supported formatters.
     */
    for (auto& pair : e.element_properties().artefact_properties()) {
        const auto arch(pair.first);
        auto& art_props(pair.second);
        compute_enablement_for_artefact_properties(gcs, lcs, arch, art_props);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished computing enablement.";
}

void enablement_transform::
transform(const context& ctx, meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Started enablement transform.";

    const auto& atrp(ctx.type_repository());
    const auto& ra(im.root_module()->annotation());
    const auto& als(ctx.archetype_location_repository().archetype_locations());

    /*
     * Obtain the types at the global level. These are types that only
     * apply to the root object, as some of these should not exist
     * anywhere else.
     */
    const auto gtg(make_global_type_group(atrp, als));

    /*
     * Read the values for the global type from the root annotations,
     * and update the facet configurations with it.
     */
    const auto gcs(obtain_global_configurations(gtg, ra));
    update_facet_enablement(als, gcs, im);

    /*
     * Create the fields for the local types. These are generated
     * against all registered formatters.
     */
    const auto ltg(make_local_type_group(atrp, als));

    /*
     * Bucket the local types by element - i.e., we only care about
     * those formatters which are valid for a particular element.
     */
    const auto& alrp(ctx.archetype_location_repository());
    const auto& albmn(alrp.archetype_locations_by_meta_name());
    const auto ltgmn(bucket_local_type_group_by_meta_name(ltg, albmn));

    using namespace std::placeholders;
    const auto f(enablement_transform::compute_enablement_for_element);
    const auto v(std::bind(f, gcs, ltgmn, _1));
    const bool include_injected_elements(true);
    meta_model::elements_traversal(im, v, include_injected_elements);

    BOOST_LOG_SEV(lg, debug) << "Finished enablement transform.";
}

} } }
