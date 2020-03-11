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
#ifndef DOGEN_ASSETS_TYPES_HELPERS_PROFILE_ADAPTER_HPP
#define DOGEN_ASSETS_TYPES_HELPERS_PROFILE_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.variability/types/meta_model/profile.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.variability/types/meta_model/profile_template.hpp"
#include "dogen.variability/types/transforms/profile_repository_inputs.hpp"
#include "dogen.assets/types/meta_model/model_set.hpp"
#include "dogen.assets/types/meta_model/variability/profile.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template.hpp"

namespace dogen::assets::helpers {

/**
 * @brief Adapts all types in a model set related to variability
 * profiles into their variability counterparts.
 */
class profile_adapter final {
private:
    /**
     * @brief Adapts an assets profile template into its variability
     * counterpart.
     */
    static variability::meta_model::profile_template
    adapt(const meta_model::variability::profile_template& pt);

    /**
     * @brief Adapts an assets profile into its variability
     * counterpart.
     */
    static variability::meta_model::profile
    adapt(const variability::meta_model::feature_model& fm,
        const meta_model::variability::profile& p);

public:
    /**
     * @brief Adapt all profile templates.
     */
    static std::list<variability::meta_model::profile_template>
    adapt_profile_templates(const meta_model::model_set& ms);

    /**
     * @brief Adapt all profiles.
     */
    static std::list<variability::meta_model::profile>
    adapt_profiles(const variability::meta_model::feature_model& fm,
        const meta_model::model_set& ms);

    /**
     * @brief Adapts a model set into the inputs required to build a
     * profile repository.
     */
    static variability::transforms::profile_repository_inputs
    adapt(const variability::meta_model::feature_model& fm,
        const meta_model::model_set& ms);
};

}

#endif
