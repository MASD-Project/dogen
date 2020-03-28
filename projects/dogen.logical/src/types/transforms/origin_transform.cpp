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
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/types/features/origin.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/origin_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.origin_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string target_cannot_be_proxy(
    "Model has origin set to target but is also a proxy: ");

}

namespace dogen::logical::transforms {

namespace {

using namespace entities::structural;
using namespace entities::decoration;
using namespace entities::variability;
using namespace entities::templating;
using namespace entities::serialization;
using namespace entities::visual_studio;

class updater {
public:
    explicit updater(const entities::origin_types ot) : origin_types_(ot) {}

public:
    template<typename DeterminableOrigin>
    void update(DeterminableOrigin& d) { d.origin_type(origin_types_); }

public:
    void operator()(entities::element& v) { update(v); }

private:
    const entities::origin_types origin_types_;
};

}

entities::origin_types origin_transform::
compute_origin_types(const entities::model& m, const bool is_proxy_model) {
    using entities::origin_types;
    if (is_proxy_model && m.origin_type() == origin_types::target) {
        const auto& id(m.name().qualified().dot());
        BOOST_LOG_SEV(lg, error) << target_cannot_be_proxy << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(target_cannot_be_proxy + id));
    }

    if (m.origin_type() == origin_types::target)
        return origin_types::target;
    else if (is_proxy_model)
        return origin_types::proxy_reference;

    return origin_types::non_proxy_reference;
}

void origin_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "origin transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);


    /*
     * First we obtain the is proxy model flag from the model's static
     * configuration.
     */
    const auto& fm(*ctx.feature_model());
    const auto fg(features::origin::make_feature_group(fm));
    const auto& cfg(*m.root_module()->configuration());
    const auto scfg(features::origin::make_static_configuration(fg, cfg));

    BOOST_LOG_SEV(lg, debug) << "Read is proxy model: " << scfg.is_proxy_model
                             << " for model: " << m.name().qualified().dot();

    /*
     * We then use the proxy model flag to compute the appropriate
     * origin type for this model.
     */
    const auto ot(compute_origin_types(m, scfg.is_proxy_model));
    m.origin_type(ot);

    /*
     * Finally, we update all model elements with the computed origin
     * type. Note that if you do not add the correct origin type to a
     * model element, it will not be code generated as we ignore all
     * non-target elements.
     */
    updater g(ot);
    entities::elements_traversal(m, g);

    stp.end_transform(m);
}

}
