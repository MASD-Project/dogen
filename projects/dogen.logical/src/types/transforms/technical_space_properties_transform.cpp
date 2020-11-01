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
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/io/entities/structural/technical_space_properties_io.hpp"
#include "dogen.logical/types/entities/structural/technical_space_properties.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/technical_space_properties_transform.hpp"

namespace {

const std::string
transform_id("logical.transforms.technical_space_properties_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_id("Duplicate ID: ");

}

namespace dogen::logical::transforms {

boost::optional<entities::structural::technical_space_properties>
technical_space_properties_transform::obtain_properties(
    const features::technical_space_properties::feature_group& fg,
    entities::element& e) {

    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

    /*
     * If we do not have any configuration related to streaming
     * operations, there is nothing to do.
     */
    const auto& cfg(*e.configuration());
    const variability::helpers::configuration_selector s(cfg);
    if (!s.has_configuration_point(fg.requires_manual_default_constructor) &&
        !s.has_configuration_point(fg.requires_manual_move_constructor) &&
        !s.has_configuration_point(fg.requires_stream_manipulators)) {
        BOOST_LOG_SEV(lg, debug) << "No properties found.";
        return boost::optional<
            entities::structural::technical_space_properties>();
    }

    /*
     * Create the properties and slot them into the results container.
     */
    entities::structural::technical_space_properties r;
    const auto scfg(features::technical_space_properties::
        make_static_configuration(fg, cfg));
    r.requires_manual_default_constructor(
        scfg.requires_manual_default_constructor);
    r.requires_manual_move_constructor(
        scfg.requires_manual_move_constructor);
    r.requires_stream_manipulators(scfg.requires_stream_manipulators);

    return r;
}

std::unordered_map<identification::entities::logical_id,
                   entities::structural::technical_space_properties>
technical_space_properties_transform::obtain_properties(
    const variability::entities::feature_model& fm,
    entities::model& m) {

    const auto fg(features::technical_space_properties::make_feature_group(fm));
    std::unordered_map<identification::entities::logical_id,
                       entities::structural::technical_space_properties> r;

    entities::elements_traversal(m,
        [&](entities::element& e) {
            const auto o(obtain_properties(fg, e));
            if (!o)
                return;

            const auto id(e.name().id());
            const auto pair(std::make_pair(id, *o));
            const auto inserted(r.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_id << id;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_id + id.value()));
            }
        });
    BOOST_LOG_SEV(lg, debug) << "Streaming properties: " << r;
    return r;
}

void technical_space_properties_transform::
walk_name_tree(const identification::entities::logical_name_tree& nt,
    const bool is_top_level, const std::unordered_map<
    identification::entities::logical_id,
    entities::structural::technical_space_properties>& src_tsps,
    entities::structural::technical_space_properties& dest_tsp) {

    for (const auto& c : nt.children())
        walk_name_tree(c, false/*is_top_level*/, src_tsps, dest_tsp);

    if (is_top_level && nt.is_current_simple_type())
        dest_tsp.requires_manual_default_constructor(true);

    const auto i(src_tsps.find(nt.current().id()));
    if (i == src_tsps.end())
        return;

    const auto src_tsp(i->second);
    if (src_tsp.requires_stream_manipulators())
        dest_tsp.requires_stream_manipulators(true);

    if (!is_top_level)
        return;

    if (src_tsp.requires_manual_default_constructor())
        dest_tsp.requires_manual_default_constructor(true);

    if (src_tsp.requires_manual_move_constructor())
        dest_tsp.requires_manual_move_constructor(true);
}

entities::structural::technical_space_properties
technical_space_properties_transform::compute_properties(
    const std::unordered_map<identification::entities::logical_id,
    entities::structural::technical_space_properties>& src_tsps,
    const std::list<logical::entities::attribute>& attrs) {

    entities::structural::technical_space_properties r;
    for (const auto& attr : attrs) {
        const auto& nt(attr.parsed_type());
        walk_name_tree(nt, true/*is_top_level*/, src_tsps, r);
    }
    return r;
}

void technical_space_properties_transform::populate_properties(
    const std::unordered_map<identification::entities::logical_id,
    entities::structural::technical_space_properties>& src_tsps,
    entities::model& m) {

    using identification::entities::model_type;
    auto& se(m.structural_elements());
    for (auto& pair : se.objects()) {
        /*
         * We only need to generate the properties for elements of the
         * target model.
         */
        auto& e(*pair.second);
        if (e.provenance().model_type() != model_type::target)
            continue;

        const auto& attrs(e.local_attributes());
        e.technical_space_properties(compute_properties(src_tsps, attrs));
    }

    for (auto& pair : se.primitives()) {
        /*
         * We only need to generate the properties for elements of the
         * target model.
         */
        auto& p(*pair.second);
        if (p.provenance().model_type() != model_type::target)
            continue;

        using logical::entities::attribute;
        const std::list<attribute> attrs{ p.value_attribute() };
        p.technical_space_properties(compute_properties(src_tsps, attrs));
    }
}

void technical_space_properties_transform::
apply(const context &ctx, entities::model &m) {
    tracing::scoped_transform_tracer stp(lg, "technical space properties",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto src_tsps(obtain_properties(fm, m));
    populate_properties(src_tsps, m);

    stp.end_transform(m);
}

}
