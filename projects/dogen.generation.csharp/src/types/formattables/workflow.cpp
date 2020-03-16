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
#include "dogen.generation.csharp/types/formattables/adapter.hpp"
#include "dogen.generation.csharp/types/formattables/model_expander.hpp"
#include "dogen.generation.csharp/types/formattables/workflow.hpp"
#include "dogen.generation.csharp/io/formattables/model_io.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.csharp.formattables.workflow"));

}

namespace dogen::generation::csharp::formattables {

model workflow::make_model(const formatters::repository& frp,
    const generation::entities::model& m) const {
    model r;
    r.name(m.name());

    adapter a;
    r.formattables(a.adapt(frp, m));

    return r;
}

void workflow::expand_model(
    const variability::entities::feature_model& feature_model,
    const formatters::repository& frp, const locator& l, model& fm) const {
    model_expander ex;
    ex.expand(feature_model, frp, l, fm);
}

model workflow::execute(
    const variability::entities::feature_model& feature_model,
    const formatters::repository& frp, const locator& l,
    const generation::entities::model& m) const {

    auto r(make_model(frp, m));
    expand_model(feature_model, frp, l, r);

    BOOST_LOG_SEV(lg, trace) << "Formattables model: " << r;

    return r;
}

}
