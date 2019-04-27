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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_CPP_STANDARD_EXPANDER_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_CPP_STANDARD_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.generation.cpp/types/formattables/cpp_standards.hpp"
#include "masd.dogen.generation.cpp/types/formattables/model.hpp"

namespace masd::dogen::generation::cpp::formattables {

class cpp_standard_expander final {
private:
    cpp_standards to_cpp_standard(const std::string& s) const;

private:
    struct type_group {
        variability::type cpp_standard;
    };

    type_group make_type_group(const variability::type_repository& atrp) const;

    cpp_standards
    make_standard(const type_group& tg, const variability::annotation& a) const;

private:
    struct feature_group {
        variability::meta_model::feature cpp_standard;
    };

    feature_group make_feature_group(
        const variability::meta_model::feature_model& fm) const;

    cpp_standards make_standard(const feature_group& fg,
        const variability::meta_model::configuration& cfg) const;

public:
    void expand(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration,
        const variability::annotation& ra,
        const variability::meta_model::configuration& rcfg, model& fm) const;
};

}

#endif
