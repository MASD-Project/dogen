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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/features/streaming.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/io/entities/streaming_properties_io.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/streaming_properties_transform.hpp"

namespace {

const std::string
transform_id("logical.transforms.streaming_properties_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_id("Duplicate ID: ");

}

namespace dogen::logical::transforms {

using identification::entities::logical_id;

boost::optional<entities::streaming_properties>
streaming_properties_transform::read_streaming_properties(
    const features::streaming::feature_group& fg,
    const entities::element& e) {
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Creating streaming properties for: "
                             << id.value();

    /*
     * If we do not have any configuration related to streaming
     * operations, there is nothing to do.
     */
    const auto& cfg(*e.configuration());
    const variability::helpers::configuration_selector s(cfg);
    if (!s.has_configuration_point(fg.requires_quoting) &&
        !s.has_configuration_point(fg.string_conversion_method) &&
        !s.has_configuration_point(fg.remove_unprintable_characters)) {
        BOOST_LOG_SEV(lg, debug) << "No streaming properties found.";
        return boost::optional<entities::streaming_properties>();
    }

    /*
     * Create the properties and slot them into the results container.
     */
    entities::streaming_properties r;
    const auto scfg(features::streaming::make_static_configuration(fg, cfg));
    r.requires_quoting(scfg.requires_quoting);
    r.string_conversion_method(scfg.string_conversion_method);
    r.remove_unprintable_characters(scfg.remove_unprintable_characters);

    BOOST_LOG_SEV(lg, debug) << "Created streaming properties: " << r;
    return r;
}

void streaming_properties_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "streaming properties",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto fg(features::streaming::make_feature_group(fm));
    std::unordered_map<identification::entities::logical_id,
                       entities::streaming_properties> streaming_properties;

    entities::elements_traversal(m,
        [&](entities::element& e) {
            const auto o(read_streaming_properties(fg, e));
            if (!o)
                return;

            const auto id(e.name().id());
            const auto pair(std::make_pair(id, *o));
            const auto inserted(streaming_properties.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_id << id;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_id + id.value()));
            }
        });
    BOOST_LOG_SEV(lg, debug) << "Streaming properties: " << streaming_properties;
    m.streaming_properties(streaming_properties);

    stp.end_transform(m);
}

}
