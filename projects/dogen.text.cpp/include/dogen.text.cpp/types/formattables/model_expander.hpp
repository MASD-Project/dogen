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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_MODEL_EXPANDER_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_MODEL_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.identification/hash/entities/logical_meta_id_hash.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.text.cpp/types/transforms/repository.hpp"
#include "dogen.text.cpp/types/formattables/locator.hpp"
#include "dogen.text.cpp/types/formattables/model.hpp"

namespace dogen::text::cpp::formattables {

class model_expander {
private:
    void expand_streaming(
        const variability::entities::feature_model& feature_model,
        model& fm) const;

    void expand_canonical_archetypes(const transforms::repository& frp,
        model& fm) const;

    void expand_inclusion(
        const variability::entities::feature_model& feature_model,
        const std::unordered_set<
        identification::entities::logical_meta_physical_id>&
        enabled_archetype_for_element,
        const transforms::repository& frp, const locator& l, model& fm) const;

    void expand_aspects(
        const variability::entities::feature_model& feature_model,
        model& fm) const;

    void expand_helpers(
        const variability::entities::feature_model& feature_model,
        const transforms::repository& frp, model& fm) const;

    void reduce(model& fm) const;

    void expand_file_paths_and_guards(const transforms::repository& frp,
        const locator& l, model& fm) const;

    void expand_odb(const locator& l, model& fm) const;

    void expand_facet_directories(const locator& l, model& fm) const;

    void expand_build_files(const locator& l, model& fm) const;

    void expand_cpp_standard(
        const variability::entities::feature_model& feature_model,
        const variability::entities::configuration& rcfg, model& fm) const;

public:
    void expand(const variability::entities::feature_model& feature_model,
        const variability::entities::configuration& rcfg,
        const std::unordered_set<
        identification::entities::logical_meta_physical_id>&
        enabled_archetype_for_element,
        const transforms::repository& frp, const locator& l, model& fm) const;
};

}

#endif
