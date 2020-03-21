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
#include "dogen.m2t.cpp/types/formattables/adapter.hpp"
#include "dogen.m2t.cpp/types/formattables/model_expander.hpp"
#include "dogen.m2t.cpp/types/formattables/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formattables.workflow"));

}

namespace dogen::m2t::cpp::formattables {

model workflow::make_model(const formatters::repository& frp,
    const m2t::entities::model& m) const {
    adapter a;
    return a.adapt(frp, m);
}

void workflow::expand_model(
    const variability::entities::feature_model& feature_model,
    const variability::entities::configuration& rcfg,
    const std::unordered_set<m2t::entities::element_archetype>&
    enabled_archetype_for_element,
    const formatters::repository& frp, const locator& l,
    model& fm) const {
    model_expander ex;
    ex.expand(feature_model, rcfg, enabled_archetype_for_element, frp, l, fm);
}

model workflow::execute(
    const variability::entities::feature_model& feature_model,
    const variability::entities::configuration& rcfg,
    const locator& l, const formatters::repository& frp,
    const m2t::entities::model& m) const {

    auto r(make_model(frp, m));
    expand_model(feature_model, rcfg,
        m.enabled_archetype_for_element(), frp, l, r);
    return r;
}

}
