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
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.coding/types/traits.hpp"
#include "dogen.coding/io/meta_model/model_io.hpp"
#include "dogen.coding/types/transforms/context.hpp"
#include "dogen.coding/types/transforms/mapping_source_transform.hpp"

namespace {

const std::string
transform_id("coding.transforms.mapping_source_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;

}

namespace dogen::coding::transforms {

mapping_source_transform::feature_group
mapping_source_transform::make_feature_group(
    const variability::meta_model::feature_model& fm) {
    const variability::helpers::feature_selector s(fm);

    feature_group r;
    // r.source = s.get_by_name(traits::mapping::source());
    r.destination  = s.get_by_name(traits::mapping::destination());

    return r;
}

std::string mapping_source_transform::make_source(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    const auto r(s.get_text_content(fg.source));
    BOOST_LOG_SEV(lg, trace) << "Read source: " << r;
    return r;
}

std::string mapping_source_transform::make_destination(
    const feature_group &fg,
    const variability::meta_model::configuration &cfg) {
    const variability::helpers::configuration_selector s(cfg);
    const auto r(s.get_text_content(fg.destination));
    BOOST_LOG_SEV(lg, trace) << "Read destination: " << r;
    return r;
}

void mapping_source_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "mapping source transform", transform_id,
        m.name().qualified().dot(), *ctx.tracer(), m);


    stp.end_transform(m);
}

}
