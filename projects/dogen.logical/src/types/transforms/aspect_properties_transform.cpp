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
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.logical/io/entities/aspect_properties_io.hpp"
#include "dogen.logical/types/entities/aspect_properties.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/features/aspect.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/aspect_properties_transform.hpp"

namespace {

const std::string
transform_id("logical.transforms.aspect_properties_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

using identification::entities::logical_id;

namespace {

class aspect_properties_generator {
public:
    explicit aspect_properties_generator(
        const features::aspect::feature_group& fg);

private:
    void handle_aspect_properties(
        const variability::entities::configuration& cfg,
        const logical_id& id);

public:
    void operator()(const logical::entities::element&) {}
    void operator()(const logical::entities::structural::enumeration& e);
    void operator()(const logical::entities::structural::exception& e);
    void operator()(const logical::entities::structural::object& o);
    void operator()(const logical::entities::structural::builtin& p);

public:
    const std::unordered_map<logical_id, entities::aspect_properties>&
    result() const;

private:
    const features::aspect::feature_group& feature_group_;
    std::unordered_map<logical_id, entities::aspect_properties> result_;
};

aspect_properties_generator::aspect_properties_generator(
    const features::aspect::feature_group& fg) : feature_group_(fg) {}

void aspect_properties_generator::handle_aspect_properties(
    const variability::entities::configuration& cfg, const logical_id& id) {
    const variability::helpers::configuration_selector s(cfg);

    /*
     * FIXME: It would be nice to make this container sparse rather
     * than dense. However, because we now default "require static
     * reference equals" to true, sparseness becomes a bit
     * confusing. This needs some rethinking.
     */
    entities::aspect_properties ap;
    const auto& rsrq(feature_group_.requires_static_reference_equals);
    ap.requires_static_reference_equals(s.get_boolean_content_or_default(rsrq));

    result_[id] = ap;
}

void aspect_properties_generator::
operator()(const logical::entities::structural::enumeration& e) {
    handle_aspect_properties(*e.configuration(), e.name().id());
}

void aspect_properties_generator::
operator()(const logical::entities::structural::exception& e) {
    handle_aspect_properties(*e.configuration(), e.name().id());
}

void aspect_properties_generator::
operator()(const logical::entities::structural::object& o) {
    handle_aspect_properties(*o.configuration(), o.name().id());
}

void aspect_properties_generator::
operator()(const logical::entities::structural::builtin& p) {
    handle_aspect_properties(*p.configuration(), p.name().id());
}

const std::unordered_map<logical_id, entities::aspect_properties>&
aspect_properties_generator::result() const {
    return result_;
}

}

void aspect_properties_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "aspect properties",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto fg(features::aspect::make_feature_group(fm));
    aspect_properties_generator g(fg);

    entities::elements_traversal(m, g);
    m.aspect_properties(g.result());
    BOOST_LOG_SEV(lg, debug) << "Aspect properties: "
                             << m.aspect_properties();

    stp.end_transform(m);
}

}
