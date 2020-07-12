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
#include "dogen.text.cpp/types/formattables/streaming_expander.hpp"
#include "dogen.text.cpp/types/formattables/canonical_archetype_expander.hpp"
#include "dogen.text.cpp/types/formattables/inclusion_expander.hpp"
#include "dogen.text.cpp/types/formattables/aspect_expander.hpp"
#include "dogen.text.cpp/types/formattables/helper_expander.hpp"
#include "dogen.text.cpp/types/formattables/reducer.hpp"
#include "dogen.text.cpp/types/formattables/file_path_and_guard_expander.hpp"
#include "dogen.text.cpp/types/formattables/odb_expander.hpp"
#include "dogen.text.cpp/types/formattables/facet_directory_expander.hpp"
#include "dogen.text.cpp/types/formattables/build_files_expander.hpp"
#include "dogen.text.cpp/types/formattables/cpp_standard_expander.hpp"
#include "dogen.text.cpp/types/formattables/model_expander.hpp"

namespace dogen::text::cpp::formattables {

void model_expander::
expand_streaming(const variability::entities::feature_model& feature_model,
    model& fm) const {
    streaming_expander ex;
    ex.expand(feature_model, fm);
}

void model_expander::expand_canonical_archetypes(
    const transforms::repository& frp, model& fm) const {
    canonical_archetype_expander ex;
    ex.expand(frp, fm);
}

void model_expander::expand_inclusion(
    const variability::entities::feature_model& feature_model,
    const std::unordered_set<physical::entities::element_archetype>&
    enabled_archetype_for_element, const transforms::repository& frp,
    const locator& l, model& fm) const {
    inclusion_expander ex;
    ex.expand(feature_model, enabled_archetype_for_element, frp, l, fm);
}

void model_expander::expand_aspects(
    const variability::entities::feature_model& feature_model,
    model& fm) const {
    aspect_expander ex;
    ex.expand(feature_model, fm);
}

void model_expander::expand_helpers(
    const variability::entities::feature_model& feature_model,
    const transforms::repository& frp, model& fm) const {
    helper_expander ex;
    ex.expand(feature_model, frp, fm);
}

void model_expander::reduce(model& fm) const {
    reducer rd;
    rd.reduce(fm);
}

void model_expander::expand_file_paths_and_guards(
    const transforms::repository& frp, const locator& l, model& fm) const {
    file_path_and_guard_expander ex;
    ex.expand(frp, l, fm);
}

void model_expander::expand_odb(const locator& l, model& fm) const {
    odb_expander ex;
    ex.expand(l, fm);
}

void model_expander::
expand_facet_directories(const locator& l,model& fm) const {
    facet_directory_expander ex;
    ex.expand(l, fm);
}

void model_expander::expand_build_files(const locator& l, model& fm) const {
    build_files_expander ex;
    ex.expand(l, fm);
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
    const std::unordered_set<physical::entities::element_archetype>&
    enabled_archetype_for_element,
    const transforms::repository& frp, const locator& l, model& fm) const {

    /*
     * Streaming expansion must be done before helper expansion as the
     * helpers need the streaminging properties.
     */
    expand_streaming(feature_model, fm);

    /*
     * C++ standard expansion must be done before enablement because
     * we will use it to check that the enabled facets are compatible
     * with the C++ standard (e.g. hash is not available for C++ 98).
     */
    expand_cpp_standard(feature_model, rcfg, fm);

    /*
     * Canonical formatter expansion must be done before inclusion
     * because we use the canonical formatter notation to find
     * inclusion directives.
     */
    expand_canonical_archetypes(frp, fm);

    expand_inclusion(feature_model, enabled_archetype_for_element, frp, l, fm);
    expand_aspects(feature_model, fm);
    expand_helpers(feature_model, frp, fm);

    /*
     * All of the above expansions must be performed prior to
     * reduction because we require types from external models.
     */
    reduce(fm);

    expand_file_paths_and_guards(frp, l, fm);
    expand_odb(l, fm);
    expand_facet_directories(l, fm);
    expand_build_files(l, fm);
}

}
