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
#include "dogen.text.csharp/types/formattables/project_items_expander.hpp"
#include "dogen.text.csharp/types/formattables/aspect_expander.hpp"
#include "dogen.text.csharp/types/formattables/assistant_expander.hpp"
#include "dogen.text.csharp/types/formattables/reducer.hpp"
#include "dogen.text.csharp/types/formattables/helper_expander.hpp"
#include "dogen.text.csharp/types/formattables/model_expander.hpp"

namespace dogen::text::csharp::formattables {

void model_expander::expand_aspect_properties(
    const variability::entities::feature_model& feature_model,
    model& fm) const {
    aspect_expander ex;
    ex.expand(feature_model, fm);
}

void model_expander::expand_assistant_properties(
    const variability::entities::feature_model& feature_model,
    model& fm) const {

    assistant_expander ex;
    ex.expand(feature_model, fm);
}

void model_expander::reduce(model& fm) const {
    reducer rd;
    rd.reduce(fm);
}

void model_expander::expand_project_items(model& fm) const {
    project_items_expander pie;
    pie.expand(fm);
}

void model_expander::
expand_helpers(const variability::entities::feature_model& feature_model,
    const transforms::repository& frp, model& fm) const {
    helper_expander he;
    he.expand(feature_model, frp, fm);
}

void model_expander::expand(
    const variability::entities::feature_model& feature_model,
    const transforms::repository& frp, model& fm) const {

    /*
     * We must expand the aspect and assistant properties before
     * reduction because we need to know about properties from
     * non-target elements.
     */
    expand_aspect_properties(feature_model, fm);
    expand_assistant_properties(feature_model, fm);

    /*
     * We must expand helpers before reduction because we want to
     * generate helpers for all referenced types, not just those in
     * the target model.
     */
    expand_helpers(feature_model, frp, fm);

    reduce(fm);
    expand_project_items(fm);
}

}
