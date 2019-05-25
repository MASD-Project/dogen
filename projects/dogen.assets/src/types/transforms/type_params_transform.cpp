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
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/types/traits.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/type_params_transform.hpp"

namespace {

const std::string transform_id("assets.type_params_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::assets::transforms {

type_params_transform::feature_group type_params_transform::
make_feature_group(const variability::meta_model::feature_model& fm) {
    feature_group r;
    const variability::helpers::feature_selector s(fm);
    const auto& vnp(traits::type_parameters::variable_number_of_parameters());
    r.variable_number_of_parameters = s.get_by_name(vnp);

    const auto& tpc(traits::type_parameters::type_parameters_count());
    r.type_parameters_count = s.get_by_name(tpc);

    const auto& aih(traits::type_parameters::type_parameters_always_in_heap());
    r.type_parameters_always_in_heap = s.get_by_name(aih);

    return r;
}

meta_model::type_parameters type_params_transform::
make_type_parameters(const features::type_parameters::feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    meta_model::type_parameters r;
    const auto scfg(
        features::type_parameters::make_static_configuration(fg, cfg));
    r.variable_number_of_parameters(scfg.variable_number_of_parameters);
    r.count(static_cast<unsigned int>(scfg.count));
    r.always_in_heap(scfg.always_in_heap);

    return r;
}

void type_params_transform::expand_type_parameters(
    const features::type_parameters::feature_group& fg,
    meta_model::structural::object& o) {
    const auto tp(make_type_parameters(fg, *o.configuration()));
    o.type_parameters(tp);
}

void type_params_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "type params transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto fg(features::type_parameters::make_feature_group(fm));
    for (auto& pair : m.structural_elements().objects()) {
        auto& o(*pair.second);
        expand_type_parameters(fg, o);
    }
    stp.end_transform(m);
}

}
