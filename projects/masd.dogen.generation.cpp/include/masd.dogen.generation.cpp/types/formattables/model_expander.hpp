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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_MODEL_EXPANDER_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_MODEL_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.generation/types/meta_model/element_archetype.hpp"
#include "masd.dogen.generation.cpp/types/formatters/repository.hpp"
#include "masd.dogen.generation.cpp/types/formattables/locator.hpp"
#include "masd.dogen.generation.cpp/types/formattables/model.hpp"

namespace masd::dogen::generation::cpp::formattables {

class model_expander {
private:
    void expand_streaming(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration, model& fm) const;

    void expand_canonical_archetypes(const formatters::repository& frp,
        model& fm) const;

    void expand_inclusion(
        const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration,
        const std::unordered_set<generation::meta_model::element_archetype>&
        enabled_archetype_for_element,
        const formatters::repository& frp, const locator& l, model& fm) const;

    void expand_aspects(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration, model& fm) const;

    void expand_helpers(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration, const formatters::repository& frp,
        model& fm) const;

    void reduce(model& fm) const;

    void expand_file_paths_and_guards(const formatters::repository& frp,
        const locator& l, model& fm) const;

    void expand_odb(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration,
        const locator& l, model& fm) const;

    void expand_facet_directories(const locator& l, model& fm) const;

    void expand_build_files(const locator& l, model& fm) const;

    void expand_cpp_standard(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration,
        const variability::annotation& ra,
        const variability::meta_model::configuration& rcfg, model& fm) const;

public:
    void expand(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration,
        const variability::annotation& ra,
        const variability::meta_model::configuration& rcfg,
        const std::unordered_set<generation::meta_model::element_archetype>&
        enabled_archetype_for_element,
        const formatters::repository& frp, const locator& l, model& fm) const;
};

}

#endif
