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
#include <ostream>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.injection/io/meta_model/model_io.hpp"
#include "masd.dogen.injection/types/traits.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/references_transform.hpp"

namespace {

const std::string transform_id("injection.transforms.references_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace masd::dogen::injection::transforms {

references_transform::feature_group references_transform::
make_feature_group(const variability::meta_model::feature_model& fm) {
    BOOST_LOG_SEV(lg, debug) << "Creating feature group.";

    feature_group r;
    const variability::helpers::feature_selector s(fm);
    r.reference = s.get_by_name(traits::reference());

    BOOST_LOG_SEV(lg, debug) << "Created feature group.";
    return r;
}

std::list<std::string>
references_transform::make_references(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.reference))
        return s.get_text_collection_content(fg.reference);

    return std::list<std::string>{};
}

void references_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "references transform",
        transform_id, m.name(), *ctx.tracer(), m);

    const auto &fg(make_feature_group(*ctx.feature_model()));
    const auto gcfg(*m.configuration());
    const auto refs(make_references(fg, gcfg));
    m.references(refs);

    stp.end_transform(m);
}

}
