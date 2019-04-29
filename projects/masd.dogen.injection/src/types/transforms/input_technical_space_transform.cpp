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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/traits.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/transformation_error.hpp"
#include "masd.dogen.injection/types/transforms/input_technical_space_transform.hpp"

namespace {

const std::string transform_id(
    "injection.transforms.input_technical_space_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::injection::transforms {

input_technical_space_transform::feature_group input_technical_space_transform::
make_feature_group(const variability::meta_model::feature_model& fm) {
    feature_group r;
    const variability::helpers::feature_selector s(fm);
    r.input_technical_space = s.get_by_name(traits::input_technical_space());
    return r;
}

std::string input_technical_space_transform::
make_input_technical_space(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    return s.get_text_content_or_default(fg.input_technical_space);
}

void input_technical_space_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "technical space transform",
        transform_id, m.name(), *ctx.tracer(), m);

    const auto& fg(make_feature_group(*ctx.feature_model()));
    const auto& gcfg(*m.configuration());
    m.input_technical_space(make_input_technical_space(fg, gcfg));

    stp.end_transform(m);
}

}
