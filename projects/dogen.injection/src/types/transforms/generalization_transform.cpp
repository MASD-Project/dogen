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
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.injection/io/meta_model/model_io.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.injection/types/features/generalization.hpp"
#include "dogen.injection/types/transforms/transformation_error.hpp"
#include "dogen.injection/types/transforms/generalization_transform.hpp"

namespace {

const std::string transform_id("injector.transforms.generalization_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string parent_name_conflict(
    "Parent name is defined in both meta-data and structure of model: ");

}

namespace dogen::injection::transforms {

void generalization_transform::
apply(const transforms::context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "generalization transform",
        transform_id, m.name(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    using features::generalization;
    const auto fg(generalization::make_feature_group(fm));

    for (auto& e : m.elements()) {
        /*
         * Obtain the parent name from the meta-data. If there is no
         * parent name there is nothing to do.
         */
        const auto& cfg(*e.configuration());
        const auto scfg(generalization::make_static_configuration(fg, cfg));
        if (scfg.parent.empty())
            continue;

        /*
         * If we've already have a parent name, this means there are now
         * two conflicting sources of parenting information so bomb out.
         */
        if (!e.parents().empty()) {
            const auto& n(e.name());
            BOOST_LOG_SEV(lg, error) << parent_name_conflict << n;
            BOOST_THROW_EXCEPTION(
                transformation_error(parent_name_conflict + n));
        }

        /*
         * Populate our parent names container.
         */
        e.parents().push_back(scfg.parent);
    }

    stp.end_transform(m);
}

}
