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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.generation.csharp/types/formattables/adapter.hpp"
#include "masd.dogen.generation.csharp/types/formattables/model_expander.hpp"
#include "masd.dogen.generation.csharp/types/formattables/workflow.hpp"
#include "masd.dogen.generation.csharp/io/formattables/model_io.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("generation.csharp.formattables.workflow"));

}

namespace masd::dogen::generation::csharp::formattables {

model workflow:: make_model(const formatters::repository& frp,
    const generation::meta_model::model& m) const {
    model r;
    r.name(m.name());

    adapter a;
    r.formattables(a.adapt(frp, m));

    return r;
}

void workflow::expand_model(
    const variability::type_repository& atrp,
    const variability::meta_model::feature_model& feature_model,
    const bool use_configuration,
    const formatters::repository& frp, const locator& l, model& fm) const {
    model_expander ex;
    ex.expand(atrp, feature_model, use_configuration, frp, l, fm);
}

model workflow::execute(
    const variability::type_repository& atrp,
    const variability::meta_model::feature_model& feature_model,
    const bool use_configuration,
    const formatters::repository& frp, const locator& l,
    const generation::meta_model::model& m) const {

    auto r(make_model(frp, m));
    expand_model(atrp, feature_model, use_configuration, frp, l, r);

    BOOST_LOG_SEV(lg, trace) << "Formattables model: " << r;

    return r;
}

}
