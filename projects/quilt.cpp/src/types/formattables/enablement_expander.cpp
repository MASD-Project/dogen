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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
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
const std::string formatter_not_found("Formatter not found: ");
const std::string element_not_found("Element not found: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

enablement_expander::global_field_definitions_type
enablement_expander::make_global_field_definitions(
    const dynamic::repository& drp,
    const formatters::container& fc) const {

    global_field_definitions_type r;
    const dynamic::repository_selector s(drp);
    for (const auto& f : fc.file_formatters()) {
        const auto oh(f->ownership_hierarchy());

        global_field_definitions fd;
        const auto& mn(oh.model_name());
        fd.model_enabled = s.select_field_by_name(mn, traits::enabled());

        const auto& fctn(oh.facet_name());
        fd.facet_enabled = s.select_field_by_name(fctn, traits::enabled());

        const auto& fn(oh.formatter_name());
        fd.formatter_enabled = s.select_field_by_name(fn, traits::enabled());

        r[fn] = fd;
    }
    return r;
}

enablement_expander::global_enablement_configurations_type
enablement_expander::obtain_global_configurations(
    const std::unordered_map<std::string, global_field_definitions>& gfd,
    const dynamic::object& root_object) const {

    global_enablement_configurations_type r;
    const dynamic::field_selector fs(root_object);
    for (const auto& pair : gfd) {
        const auto& fmtn(pair.first);
        const auto& fd(pair.second);

        global_enablement_configuration gc;
        gc.model_enabled(fs.get_boolean_content_or_default(fd.model_enabled));
        gc.facet_enabled(fs.get_boolean_content_or_default(fd.facet_enabled));
        gc.formatter_enabled(
            fs.get_boolean_content_or_default(fd.formatter_enabled));

        r[fmtn] = gc;
    }

    BOOST_LOG_SEV(lg, debug) << "Global enablement properties: " << r;
    return r;
}

enablement_expander::local_field_definitions_type
enablement_expander::make_local_field_definitions(const dynamic::repository& drp,
    const formatters::container& fc) const {

    local_field_definitions_type r;
    const dynamic::repository_selector s(drp);
    for (const auto& f : fc.file_formatters()) {
        local_field_definitions fd;
        const auto oh(f->ownership_hierarchy());
        const auto& fmtn(oh.formatter_name());
        fd.enabled = s.select_field_by_name(fmtn, traits::enabled());

        const auto& fctn(oh.facet_name());
        fd.supported = s.select_field_by_name(fctn, traits::supported());
        r[fmtn] = fd;
    }
    return r;
}

std::unordered_map<std::type_index,
                   enablement_expander::local_field_definitions_type>
enablement_expander::obtain_local_field_definitions_by_type_index(
    const local_field_definitions_type& lfds,
    const formatters::container& fc) const {

    std::unordered_map<std::type_index,
                       enablement_expander::local_field_definitions_type> r;

    const auto& ffti(fc.file_formatters_by_type_index());
    for (const auto& pair: ffti) {
        const auto& ti(pair.first);
        const auto& fmts(pair.second);

        local_field_definitions_type& lfd(r[ti]);
        for (const auto& fmt: fmts) {
            const auto fmtn(fmt->ownership_hierarchy().formatter_name());
            const auto i(lfds.find(fmtn));
            if (i == lfds.end()) {
                BOOST_LOG_SEV(lg, error) << formatter_not_found << fmtn;
                BOOST_THROW_EXCEPTION(
                    expansion_error(formatter_not_found + fmtn));
            }

            lfd[fmtn] = i->second;
        }
    }
    return r;
}

enablement_expander::local_enablement_configurations_type enablement_expander::
obtain_local_configurations(const local_field_definitions_type& lfd,
    const dynamic::object& o) const {
    local_enablement_configurations_type r;
    const dynamic::field_selector fs(o);
    for (const auto& pair : lfd) {
        const auto& fmtn(pair.first);
        const auto& fd(pair.second);

        local_enablement_configuration lec;
        lec.supported(fs.get_boolean_content_or_default(fd.supported));
        if (fs.has_field(fd.enabled))
            lec.enabled(fs.get_boolean_content(fd.enabled));

        r[fmtn] = lec;
    }
    return r;
}

void enablement_expander::compute_enablement(
    const global_enablement_configurations_type& gcs,
    const local_enablement_configurations_type& lcs, formattable& f) const {

    for (auto& pair : f.configuration().formatter_configuration()) {
        const auto fmtn(pair.first);
        auto& fmtc(pair.second);

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
        const auto gc(i->second);
        if (!gc.model_enabled() || !gc.facet_enabled()) {
            fmtc.enabled(false);
            continue;
        }

        /*:
         * FIXME: We only want to generate the types facet for
         * services at present. This is achieved with the below hack
         * for now.
         */
        const auto& e(*f.element());
        auto object_ptr(dynamic_cast<const yarn::object*>(&e));
        if (object_ptr != nullptr) {
            const auto uds(yarn::object_types::user_defined_service);
            const auto is_service(object_ptr->object_type() == uds);

            if (is_service) {
                const auto types_prefix("quilt.cpp.types.");
                const auto is_types(boost::starts_with(fmtn, types_prefix));
                fmtc.enabled(is_types);
                continue;
            }
        }

        const auto j(lcs.find(fmtn));
        if (j == lcs.end()) {
            BOOST_LOG_SEV(lg, error) << local_configuration_not_found << fmtn;
            BOOST_THROW_EXCEPTION(
                expansion_error(local_configuration_not_found + fmtn));
        }
        const auto& lc(j->second);

        /*
         * Check to see if the formatter enablement field has been set
         * locally. If so, it takes precedence over global
         * configuration.
         */
        if (lc.enabled()) {
            fmtc.enabled(*lc.enabled());
            continue;
        }

        /*
         * If nothing else has been set, use the global enablement
         * flag for the formatter.
         */
        fmtc.enabled(gc.formatter_enabled());
    }
}

void enablement_expander::expand(const dynamic::repository& drp,
    const dynamic::object& root_object, const formatters::container& fc,
    std::unordered_map<std::string, formattable>& formattables) const {

    /*
     * Obtain the field definitions at the global level. These are the
     * field definitions that only apply to the root object, as some
     * of these fields do not exist anywhere else.
     */
    const auto gfds(make_global_field_definitions(drp, fc));

    /*
     * Read the values for the global field definitions.
     */
    const auto gcs(obtain_global_configurations(gfds, root_object));

    /*
     * Create the fields for the local field definitions. These are
     * made across all registered formatters.
     */
    const auto lfds(make_local_field_definitions(drp, fc));

    /*
     * Bucket the local field definitions by element type - i.e., we
     * only care about those formatters which are valid for a
     * particular element.
     */
    const auto lfdsti(obtain_local_field_definitions_by_type_index(lfds, fc));

    for (auto& pair : formattables) {
        const auto id(pair.first);
        auto& formattable(pair.second);
        const auto& e(*formattable.element());

        /*
         * Now, for each formattable, find the corresponding local field
         * definitions and use those to obtain the values of the local
         * configuration.
         */
        const auto ti(std::type_index(typeid(e)));
        const auto i(lfdsti.find(ti));
        if (i == lfdsti.end()) {
            BOOST_LOG_SEV(lg, error) << element_not_found << id;
            BOOST_THROW_EXCEPTION(expansion_error(element_not_found + id));
        }

        auto lcs(obtain_local_configurations(i->second, e.extensions()));

        /*
         * Once we got both the global and the local configuration, we
         * can then compute the enablement values for this
         * formattable, across all the supported formatters.
         */
        compute_enablement(gcs, lcs, formattable);
    }
}

} } } }
