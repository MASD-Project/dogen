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
#include "dogen.text.cpp/types/formattables/aspect_expander.hpp"
#include "dogen.text.cpp/types/formattables/helper_expander.hpp"
#include "dogen.text.cpp/types/formattables/reducer.hpp"
#include "dogen.text.cpp/types/formattables/cpp_standard_expander.hpp"
#include "dogen.text.cpp/types/formattables/model_expander.hpp"

namespace dogen::text::cpp::formattables {

void model_expander::expand_aspects(
    const variability::entities::feature_model& feature_model,
    model& fm) const {
    aspect_expander ex;
    ex.expand(feature_model, fm);
}

void model_expander::expand_helpers(
    const variability::entities::feature_model& feature_model,
    const std::unordered_map<identification::entities::logical_id,
    logical::entities::streaming_properties>& streaming_properties,
    const transforms::repository& frp, model& fm) const {
    helper_expander ex;
    ex.expand(feature_model, streaming_properties, frp, fm);
}

void model_expander::reduce(model& fm) const {
    reducer rd;
    rd.reduce(fm);
}

void
model_expander::expand_cpp_standard(
    const variability::entities::feature_model& feature_model,
    const variability::entities::configuration& rcfg, model& fm) const {
    cpp_standard_expander ex;
    ex.expand(feature_model, rcfg, fm);
}

void model_expander::expand(
    const variability::entities::feature_model& feature_model,
    const variability::entities::configuration& rcfg,
    const std::unordered_map<identification::entities::logical_id,
    logical::entities::streaming_properties>& streaming_properties,
    const transforms::repository& frp, model& fm) const {

    /*
     * C++ standard expansion must be done before enablement because
     * we will use it to check that the enabled facets are compatible
     * with the C++ standard (e.g. hash is not available for C++ 98).
     */
    expand_cpp_standard(feature_model, rcfg, fm);

    expand_aspects(feature_model, fm);
    expand_helpers(feature_model, streaming_properties, frp, fm);

    /*
     * All of the above expansions must be performed prior to
     * reduction because we require types from external models.
     */
    reduce(fm);
}

}
