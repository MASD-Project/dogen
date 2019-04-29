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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include "masd.dogen.generation/types/meta_model/model.hpp"
#include "masd.dogen.generation/types/meta_model/element_archetype.hpp"
#include "masd.dogen.generation.cpp/types/formattables/model.hpp"
#include "masd.dogen.generation.cpp/types/formattables/locator.hpp"
#include "masd.dogen.generation.cpp/types/formatters/repository.hpp"
#include "masd.dogen.generation.cpp/types/formattables/formattable.hpp"

namespace masd::dogen::generation::cpp::formattables {

class workflow {
private:
    model make_model(const formatters::repository& frp,
        const generation::meta_model::model& m) const;

    void expand_model(
        const variability::meta_model::feature_model& feature_model,
        const variability::meta_model::configuration& rcfg,
        const std::unordered_set<generation::meta_model::element_archetype>&
        enabled_archetype_for_element,
        const formatters::repository& frp, const locator& l,
        model& fm) const;

public:
    model execute(
        const variability::meta_model::feature_model& feature_model,
        const variability::meta_model::configuration& rcfg,
        const locator& l, const formatters::repository& frp,
        const generation::meta_model::model& m) const;
};

}

#endif
