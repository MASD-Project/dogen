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
#include <boost/make_shared.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/io/meta_model/feature_io.hpp"
#include "dogen.variability/io/meta_model/feature_model_io.hpp"
#include "dogen.variability/types/transforms/transformation_error.hpp"
#include "dogen.variability/types/transforms/feature_model_transform.hpp"

namespace {

const std::string
transform_id("variability.transforms.feature_model_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_qualified_name(
    "Qualified name defined more than once: ");

}

namespace dogen::variability::transforms {

boost::shared_ptr<meta_model::feature_model> feature_model_transform::
apply(const context& ctx, const std::list<meta_model::feature>& features) {
    tracing::scoped_transform_tracer stp(lg, "feature model transform",
        transform_id, transform_id, *ctx.tracer(), features);

    auto r(boost::make_shared<meta_model::feature_model>());
    r->all(features);

    for (const auto& f : features) {
        const auto qn(f.name().qualified());
        const auto pair(std::make_pair(qn, f));
        const auto inserted(r->by_name().insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << qn;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_qualified_name + qn));
        }

        if (f.is_partially_matchable())
            r->partially_matchable()[qn] = f;
    }

    stp.end_transform(r);
    return r;
}

}
