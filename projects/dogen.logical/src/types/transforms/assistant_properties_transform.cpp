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
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/io/entities/assistant_properties_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/features/assistant.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/assistant_properties_transform.hpp"

namespace {

const std::string
transform_id("logical.transforms.assistant_properties_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

using identification::entities::logical_id;

namespace {

class generator {
public:
    explicit generator(const features::assistant::feature_group& fg);

public:
    void operator()(const logical::entities::element&);

public:
    const std::unordered_map<logical_id, entities::assistant_properties>&
    result() const;

private:
    const features::assistant::feature_group& feature_group_;
    std::unordered_map<logical_id, entities::assistant_properties> result_;
};

generator::generator(const features::assistant::feature_group& fg)
    : feature_group_(fg) {}

void generator::operator()(const logical::entities::element& e) {
    bool has_properties(false);
    entities::assistant_properties ap;
    const auto& cfg(*e.configuration());
    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(feature_group_.requires_assistance)) {
        has_properties = true;
        ap.requires_assistance(
            s.get_boolean_content(feature_group_.requires_assistance));
    }

    if (s.has_configuration_point(feature_group_.method_postfix)) {
        has_properties = true;
        ap.method_postfix(s.get_text_content(feature_group_.method_postfix));
    }

    if (has_properties)
        result_[e.name().id()] = ap;
}

const std::unordered_map<logical_id, entities::assistant_properties>&
generator::result() const {
    return result_;
}

}

void
assistant_properties_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "aspect properties",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto fg(features::assistant::make_feature_group(fm));
    generator g(fg);

    entities::elements_traversal(m, g);
    m.assistant_properties(g.result());
    BOOST_LOG_SEV(lg, debug) << "Assistant properties: "
                             << m.assistant_properties();

    stp.end_transform(m);
}

}
