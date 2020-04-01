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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/io/formattables/aspect_properties_io.hpp"
#include "dogen.m2t.cpp/types/formattables/aspect_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("m2t.cpp.formattables.aspect_expander"));

}

namespace dogen::m2t::cpp::formattables {

aspect_expander::feature_group aspect_expander::
make_feature_group(const variability::entities::feature_model& fm) const {
    feature_group r;

    const variability::helpers::feature_selector s(fm);
    typedef traits::cpp::aspect aspect;

    const auto& rmdc(aspect::requires_manual_default_constructor());
    r.requires_manual_default_constructor = s.get_by_name(rmdc);

    const auto& rmmc(aspect::requires_manual_move_constructor());
    r.requires_manual_move_constructor = s.get_by_name(rmmc);

    const auto& rsm(aspect::requires_stream_manipulators());
    r.requires_stream_manipulators = s.get_by_name(rsm);

    return r;
}

boost::optional<aspect_properties> aspect_expander::
make_aspect_properties(const feature_group& fg,
    const variability::entities::configuration& cfg) const {
    aspect_properties r;

    const variability::helpers::configuration_selector s(cfg);
    bool found_any(false);

    if (s.has_configuration_point(fg.requires_manual_default_constructor))
        found_any = true;

    r.requires_manual_default_constructor(
        s.get_boolean_content_or_default(
            fg.requires_manual_default_constructor));

    if (s.has_configuration_point(fg.requires_manual_move_constructor))
        found_any = true;

    r.requires_manual_move_constructor(
        s.get_boolean_content_or_default(
            fg.requires_manual_move_constructor));

    if (s.has_configuration_point(fg.requires_stream_manipulators))
        found_any = true;

    r.requires_stream_manipulators(
        s.get_boolean_content_or_default(
            fg.requires_stream_manipulators));

    if (found_any)
        return r;

    return boost::optional<aspect_properties>();
}

aspect_expander::aspect_properties_type aspect_expander::
obtain_aspect_properties(
    const variability::entities::feature_model& feature_model,
    const std::unordered_map<std::string, formattable>& formattables) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating aspect configuration.";

    const auto fg(make_feature_group(feature_model));
    aspect_properties_type r;
    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        const auto& segment(*formattable.element());

        const auto ap(make_aspect_properties(fg, *segment.configuration()));
        if (ap)
            r[id] = *ap;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating aspect properties. "
                             << "Result: " << r;
    return r;
}

void aspect_expander::walk_name_tree(const logical::entities::name_tree& nt,
    const bool is_top_level, const aspect_properties_type& element_aps,
    aspect_properties& ap) const {

    for (const auto& c : nt.children())
        walk_name_tree(c, false/*is_top_level*/, element_aps, ap);

    if (is_top_level && nt.is_current_simple_type())
        ap.requires_manual_default_constructor(true);

    const auto i(element_aps.find(nt.current().qualified().dot()));
    if (i == element_aps.end())
        return;

    const auto element_ap(i->second);
    if (element_ap.requires_stream_manipulators())
        ap.requires_stream_manipulators(true);

    if (!is_top_level)
        return;

    if (element_ap.requires_manual_default_constructor())
        ap.requires_manual_default_constructor(true);

    if (element_ap.requires_manual_move_constructor())
        ap.requires_manual_move_constructor(true);
}

aspect_properties aspect_expander::compute_aspect_properties(
    const aspect_properties_type& element_aps,
    const std::list<logical::entities::attribute>& attrs) const {

    aspect_properties r;
    for (const auto& attr : attrs) {
        const auto& nt(attr.parsed_type());
        walk_name_tree(nt, true/*is_top_level*/, element_aps, r);
    }
    return r;
}

void aspect_expander::populate_aspect_properties(const std::string& element_id,
    const aspect_properties_type& element_aps,
    formattable& formattable) const {

    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << element_id;
    auto& eprops(formattable.element_properties());

    /*
     * We only want to process the master segment; extensions can
     * be ignored.
     */
    const auto& ms(formattable.element());

    /*
     * We only need to generate the aspect configuration for
     * elements of the target model. However, we can't perform
     * this after reduction because the aspect configurations must
     * be build prior to reduction or else we will not get aspects
     * for referenced models.
     */
    if (ms->origin_type() != logical::entities::origin_types::target)
        return;

    /*
     * We are only interested in yarn objects; all other element
     * types do not need helpers.
     */
    const auto ptr(dynamic_cast<const logical::entities::structural::object*>(ms.get()));
    if (ptr == nullptr)
        return;

    const auto& o(*ptr) ;

    /*
     * Update the aspect properties.
     */
    const auto& attrs(o.local_attributes());
    const auto element_ap(compute_aspect_properties(element_aps, attrs));
    eprops.aspect_properties(element_ap);
}

void aspect_expander::
populate_aspect_properties(const aspect_properties_type& element_aps,
    std::unordered_map<std::string, formattable>& formattables) const {

    for (auto& pair : formattables) {
        const auto id(pair.first);
        auto& formattable(pair.second);
        populate_aspect_properties(id, element_aps, formattable);
    }
}

void aspect_expander::
expand(const variability::entities::feature_model& feature_model,
    model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expansion.";
    const auto element_aps(
        obtain_aspect_properties(feature_model, fm.formattables()));
    populate_aspect_properties(element_aps, fm.formattables());
    BOOST_LOG_SEV(lg, debug) << "Finished expansion.";
}

}
