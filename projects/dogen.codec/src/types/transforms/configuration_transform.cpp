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
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/entities/binding_point.hpp"
#include "dogen.variability/types/helpers/configuration_factory.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/types/transforms/context.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/transforms/configuration_transform.hpp"

namespace {

const std::string transform_id("codec.transforms.configuration_transform");
const std::string mssing_feature_model("Feature model not supplied.");

using namespace dogen::utility::log;
logger lg(logger_factory(transform_id));

}

namespace dogen::codec::transforms {

template<typename NameableAndTaggable>
inline void create_configuration(
    const variability::helpers::configuration_factory& f,
    const variability::entities::binding_point bp, NameableAndTaggable& nat) {

    const auto& tv(nat.tagged_values());
    const auto& otv(nat.tagged_values_overrides());
    nat.configuration(f.make_shared_ptr(tv, otv, bp));
    nat.configuration()->name().simple(nat.name().simple());
}

void configuration_transform::
apply(const transforms::context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "configuration",
        transform_id, m.name().simple(), *ctx.tracer(), m);

    BOOST_LOG_SEV(lg, debug) << "Transforming model: " << m.name().simple()
                             << "Total elements: " << m.elements().size();

    if (ctx.feature_model() == nullptr) {
        BOOST_LOG_SEV(lg, error) << mssing_feature_model;
        BOOST_THROW_EXCEPTION(transformation_error(mssing_feature_model));
    }

    const auto& fm(*ctx.feature_model());
    const auto& cm(ctx.compatibility_mode());
    variability::helpers::configuration_factory f(fm, cm);

    using bp = variability::entities::binding_point;
    create_configuration(f, bp::global, m);
    for (auto& e : m.elements()) {
        create_configuration(f, bp::element, e);
        for (auto& a : e.attributes())
            create_configuration(f, bp::property, a);
    }

    stp.end_transform(m);
    BOOST_LOG_SEV(lg, debug) << "Transformed model.";
}

}
