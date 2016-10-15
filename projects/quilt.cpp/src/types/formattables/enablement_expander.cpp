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
#include <boost/io/ios_state.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/typeindex_io.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/quilt.cpp/io/formattables/facet_properties_io.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/io/formattables/local_enablement_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/global_enablement_configuration_io.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/enablement_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.enablement_expander"));

const std::string global_configuration_not_found(
    "Could not find global enablement configuration for formatter: ");
const std::string local_configuration_not_found(
    "Could not find local enablement configuration for formatter: ");
const std::string duplicate_formatter_name("Duplicate formatter name: ");
const std::string formatter_not_found("Formatter not found: ");
const std::string element_not_found("Element not found: ");
const std::string default_value_unset("Default value not set for field: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

inline std::ostream& operator<<(std::ostream& s,
    const enablement_expander::global_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "enablement_expander::global_type_group\"" << ", "
      << "\"model_enabled\": " << v.model_enabled << ", "
      << "\"facet_enabled\": " << v.facet_enabled << ", "
      << "\"formatter_enabled\": " << v.formatter_enabled
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s,
    const enablement_expander::local_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "enablement_expander::local_type_group\"" << ", "
      << "\"facet_enabled\": " << v.facet_enabled << ", "
      << "\"formatter_enabled\": " << v.formatter_enabled << ", "
      << "\"supported\": " << v.facet_supported
      << " }";

    return s;
}

enablement_expander::global_type_group_type
enablement_expander::make_global_type_group(
    const annotations::type_repository& atrp,
    const formatters::container& fc) const {

    BOOST_LOG_SEV(lg, debug) << "Creating global field definitions.";

    global_type_group_type r;
    const annotations::type_repository_selector s(atrp);
    for (const auto& f : fc.file_formatters()) {
        const auto oh(f->ownership_hierarchy());

        global_type_group gtg;
        const auto& mn(oh.model_name());
        const auto ebl(traits::enabled());
        gtg.model_enabled = s.select_type_by_name(mn, ebl);

        const auto& fctn(oh.facet_name());
        gtg.facet_enabled = s.select_type_by_name(fctn, ebl);

        const auto& fmtn(oh.formatter_name());
        gtg.formatter_enabled = s.select_type_by_name(fmtn, ebl);

        const auto ow(traits::overwrite());
        gtg.facet_overwrite = s.select_type_by_name(fctn, ow);
        gtg.formatter_overwrite = s.select_type_by_name(fmtn, ow);

        r[fmtn] = gtg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created global field definitions. Result: "
                             << r;
    return r;
}

enablement_expander::global_enablement_configurations_type
enablement_expander::obtain_global_configurations(
    const std::unordered_map<std::string, global_type_group>& gtg,
    const annotations::annotation& root) const {

    BOOST_LOG_SEV(lg, debug) << "Creating global enablement configuration.";

    global_enablement_configurations_type r;
    const annotations::entry_selector s(root);
    for (const auto& pair : gtg) {
        const auto& fmtn(pair.first);
        const auto& t(pair.second);

        /*
         * Model configuration can only be set via meta-data, so we'll
         * take the value set or its default.
         */
        global_enablement_configuration gec;
        gec.model_enabled(s.get_boolean_content_or_default(t.model_enabled));
        gec.facet_enabled(s.get_boolean_content_or_default(t.facet_enabled));
        gec.formatter_enabled(
            s.get_boolean_content_or_default(t.formatter_enabled));
        gec.facet_overwrite(
            s.get_boolean_content_or_default(t.facet_overwrite));

        if (s.has_entry(t.formatter_overwrite)) {
            gec.formatter_overwrite(
                s.get_boolean_content(t.formatter_overwrite));
        }

        r[fmtn] = gec;
    }

    BOOST_LOG_SEV(lg, debug) << "Created global enablement configuration. "
                             << "Result: " << r;
    return r;
}

void enablement_expander::update_facet_enablement(
    const formatters::container& fc,
    const global_enablement_configurations_type& gcs, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Updating facet enablement.";

    /*
     * For each formatter on our global configurations: find the facet
     * to which the formatter belongs to, and update the enabled value
     * of that facet in the main facet container.
     *
     * Note that this is all a bit silly - we're doing this N times
     * for one facet (where N is the number of formatters for that
     * facet) rather than just read the facet field and update it
     * once.
     *
     * FIXME: read facet fields here instead of reusing configuration.
     */
    const auto& fffn(fc.file_formatters_by_formatter_name());
    auto& fct_props(fm.facet_properties());
    for (const auto& pair : gcs) {
        const auto fmtn(pair.first);
        const auto i(fffn.find(fmtn));
        if (i == fffn.end()) {
            BOOST_LOG_SEV(lg, error) << formatter_not_found << fmtn;
            BOOST_THROW_EXCEPTION(
                expansion_error(formatter_not_found + fmtn));
        }

        const auto& fmt(*i->second);
        const auto& oh(fmt.ownership_hierarchy());
        const auto fctn(oh.facet_name());
        const auto& gc(pair.second);
        fct_props[fctn].enabled(gc.facet_enabled());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished updating facet enablement."
                             << "Result: " << fm.facet_properties();
}

enablement_expander::local_type_group_type enablement_expander::
make_local_type_group(const annotations::type_repository& atrp,
    const formatters::container& fc) const {

    BOOST_LOG_SEV(lg, debug) << "Creating local field definitions.";

    local_type_group_type r;
    const annotations::type_repository_selector s(atrp);
    for (const auto& f : fc.file_formatters()) {
        local_type_group ltg;
        const auto oh(f->ownership_hierarchy());

        const auto& fctn(oh.facet_name());
        const auto ebl(traits::enabled());
        ltg.facet_enabled = s.select_type_by_name(fctn, ebl);

        const auto& fmtn(oh.formatter_name());
        ltg.formatter_enabled = s.select_type_by_name(fmtn, ebl);

        const auto ow(traits::overwrite());
        ltg.facet_overwrite = s.select_type_by_name(fctn, ow);
        ltg.formatter_overwrite = s.select_type_by_name(fmtn, ow);
        ltg.facet_supported = s.select_type_by_name(fctn, traits::supported());
        r[fmtn] = ltg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created local field definitions. Result: "
                             << r;
    return r;
}

std::unordered_map<std::type_index,
                   enablement_expander::local_type_group_type>
enablement_expander::bucket_local_type_group_by_type_index(
    const local_type_group_type& unbucketed_ltgs,
    const formatters::container& fc) const {

    BOOST_LOG_SEV(lg, debug) << "Started bucketing local field definitions "
                             << "by type index.";
    std::unordered_map<std::type_index,
                       enablement_expander::local_type_group_type> r;

    const auto& ffti(fc.file_formatters_by_type_index());
    for (const auto& pair: ffti) {
        const auto& ti(pair.first);
        const auto& fmts(pair.second);

        local_type_group_type& ltg(r[ti]);
        for (const auto& fmt: fmts) {
            const auto fmtn(fmt->ownership_hierarchy().formatter_name());
            const auto i(unbucketed_ltgs.find(fmtn));
            if (i == unbucketed_ltgs.end()) {
                BOOST_LOG_SEV(lg, error) << formatter_not_found << fmtn;
                BOOST_THROW_EXCEPTION(
                    expansion_error(formatter_not_found + fmtn));
            }

            const auto pair(std::make_pair(fmtn, i->second));
            const auto ret(ltg.insert(pair));
            if (!ret.second) {
                BOOST_LOG_SEV(lg, error) << duplicate_formatter_name << fmtn;
                BOOST_THROW_EXCEPTION(
                    expansion_error(duplicate_formatter_name + fmtn));
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished bucketing local field definitions "
                             << "by type index. Result: " << r;
    return r;
}

enablement_expander::local_enablement_configurations_type enablement_expander::
obtain_local_configurations(const local_type_group_type& ltg,
    const annotations::annotation& o) const {

    BOOST_LOG_SEV(lg, debug) << "Obtaining local configurations.";
    local_enablement_configurations_type r;
    const annotations::entry_selector s(o);
    for (const auto& pair : ltg) {
        const auto& fmtn(pair.first);
        const auto& t(pair.second);

        local_enablement_configuration lec;
        if (s.has_entry(t.facet_enabled))
            lec.facet_enabled(s.get_boolean_content(t.facet_enabled));

        if (s.has_entry(t.formatter_enabled))
            lec.formatter_enabled(s.get_boolean_content(t.formatter_enabled));

        if (s.has_entry(t.facet_overwrite))
            lec.facet_overwrite(s.get_boolean_content(t.facet_overwrite));

        if (s.has_entry(t.formatter_overwrite))
            lec.formatter_overwrite(
                s.get_boolean_content(t.formatter_overwrite));

        r[fmtn] = lec;
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained local configurations. Result: " << r;
    return r;
}

bool enablement_expander::has_user_defined_service(
    const std::list<boost::shared_ptr<yarn::element>>& element_segments) const {

    for (const auto& segment : element_segments) {
        auto object_ptr(dynamic_cast<const yarn::object*>(segment.get()));
        if (object_ptr == nullptr)
            continue;

        const auto uds(yarn::object_types::user_defined_service);
        return object_ptr->object_type() == uds;
    }
    return false;
}

void enablement_expander::compute_enablement(
    const global_enablement_configurations_type& gcs,
    const local_enablement_configurations_type& lcs, formattable& fbl) const {

    BOOST_LOG_SEV(lg, debug) << "Started computing enablement.";
    for (auto& pair : fbl.element_properties().formatter_properties()) {
        const auto fmtn(pair.first);

        /*
         * As we may be processing a segmented entity, not all
         * formatters need to be present in the local
         * configuration. For example, an entity may be segmented into
         * an object and a forward declaration; in this case, when we
         * are processing the object, we will still see the forward
         * declaration formatters in the formattable configuration
         * since the transformer merged all segments of the element
         * together. However, these are not present in the local
         * configuration container because we are only processing one
         * segment at a time. So, we need to ignore the formatters for
         * the segments we are not processing.
         */
        const auto j(lcs.find(fmtn));
        if (j == lcs.end()) {
            BOOST_LOG_SEV(lg, debug) << "Ignoring formatter: " << fmtn;
            continue;
        }
        const auto& lc(j->second);

        const auto i(gcs.find(fmtn));
        if (i == gcs.end()) {
            BOOST_LOG_SEV(lg, error) << global_configuration_not_found << fmtn;
            BOOST_THROW_EXCEPTION(
                expansion_error(global_configuration_not_found + fmtn));
        }

        /*
         * If either the entire model model or facet have been
         * disabled globally, the formatter will be disabled too.
         */
        auto& fmt_props(pair.second);
        const auto gc(i->second);
        if (!gc.model_enabled() || !gc.facet_enabled()) {
            fmt_props.enabled(false);
            continue;
        }

        /*:
         * FIXME: We only want to generate the types facet for
         * services at present. This is achieved with the below hack
         * for now.
         */
        if (has_user_defined_service(fbl.all_segments())) {
            const auto types_prefix("quilt.cpp.types.");
            const auto is_types(boost::starts_with(fmtn, types_prefix));
            fmt_props.enabled(is_types);
            continue;
        }

        /*
         * Check to see if the formatter enablement field has been set
         * locally. If so, it takes precedence over the facet
         * configuration.
         */
        if (lc.formatter_enabled()) {
            fmt_props.enabled(*lc.formatter_enabled());
            continue;
        }

        /*
         * If the overwrite flag is set locally at the formatter or
         * facet level, then that takes priority. If not, first check
         * to see if its set globally at the formatter level; if so,
         * it takes priority. Finally, if nothing else is set, use the
         * global facet default.
         *
         * The rationale here is as follows: users can set facets to
         * overwrite locally on a model element (either directly of
         * via profiles); for example, for an handcrafted class, we
         * want to set overwrite to false at the element level. This
         * is normally done via a profile, but can be conceivable be
         * done directly for less common configurations - for example
         * adding manual support for IO for a handcrafted type. The
         * global formatter overwrite flag is a bit less useful - we
         * haven't got a use case for it just yet but it is added for
         * (foolish) consistency. Finally, the global facet level
         * overwrite flag is useful for the general case of code
         * generated code. Having said that, it does not make a lot of
         * sense to set overwrite globally to false.
         *
         * Note also that the overwrite flag is only relevant if
         * enabled is true. It is not used otherwise.
         */
        if (lc.formatter_overwrite())
            fmt_props.overwrite(*lc.formatter_overwrite());
        else if (lc.facet_overwrite())
            fmt_props.overwrite(*lc.facet_overwrite());
        else if (gc.formatter_overwrite())
            fmt_props.overwrite(*gc.formatter_overwrite());
        else
            fmt_props.overwrite(gc.facet_overwrite());

        /*
         * Check to see if the facet enablement field has been set
         * locally. If so, it takes precedence over global
         * configuration.
         */
        if (lc.facet_enabled()) {
            fmt_props.enabled(*lc.facet_enabled());
            continue;
        }

        /*
         * If nothing else has been set, use the global enablement
         * flag for the formatter.
         */
        fmt_props.enabled(gc.formatter_enabled());
        BOOST_LOG_SEV(lg, debug) << "Enablement for: " << fmtn
                                 << " value: " << fmt_props.enabled();
    }

    BOOST_LOG_SEV(lg, debug) << "Finished computed enablement.";
}

void enablement_expander::expand(const annotations::type_repository& atrp,
    const annotations::annotation& root, const formatters::container& fc,
    model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started expanding enablement.";
    /*
     * Obtain the field definitions at the global level. These are the
     * field definitions that only apply to the root object, as some
     * of these fields do not exist anywhere else.
     */
    const auto gtg(make_global_type_group(atrp, fc));

    /*
     * Read the values for the global field definitions, and update
     * the facet configurations with it.
     */
    const auto gcs(obtain_global_configurations(gtg, root));
    update_facet_enablement(fc, gcs, fm);

    /*
     * Create the fields for the local field definitions. These are
     * made across all registered formatters.
     */
    const auto ltg(make_local_type_group(atrp, fc));

    /*
     * Bucket the local field definitions by element type - i.e., we
     * only care about those formatters which are valid for a
     * particular element.
     */
    const auto ltgti(bucket_local_type_group_by_type_index(ltg, fc));

    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        for (const auto& segment : formattable.all_segments()) {
            const auto& e(*segment);

            /*
             * Now, for each element segment, find the corresponding
             * local field definitions and use those to obtain the
             * values of the local configuration.
             */
            const auto ti(std::type_index(typeid(e)));
            BOOST_LOG_SEV(lg, debug) << "Type index: " << ti.name();

            /*
             * Not all elements have formatters; for example, concepts
             * don't have any at present. If so, skip the element.
             */
            const auto i(ltgti.find(ti));
            if (i == ltgti.end()) {
                BOOST_LOG_SEV(lg, debug) << "Element has no formatters, "
                                         << " so nothing enable.";
                continue;
            }

            const auto& t(i->second);
            auto lcs(obtain_local_configurations(t, e.annotation()));

            /*
             * Once we got both the global and the local configuration, we
             * can then compute the enablement values for this
             * formattable, across all the supported formatters.
             */
            compute_enablement(gcs, lcs, formattable);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding enablement.";
}

} } } }
