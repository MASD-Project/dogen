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
#ifndef DOGEN_ENGINE_TYPES_TRANSFORMS_PROFILE_TEMPLATE_ADAPTION_TRANSFORM_HPP
#define DOGEN_ENGINE_TYPES_TRANSFORMS_PROFILE_TEMPLATE_ADAPTION_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.variability/types/meta_model/profile_template.hpp"
#include "dogen.assets/types/meta_model/model_set.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template.hpp"
#include "dogen.engine/types/transforms/context_fwd.hpp"

namespace dogen::engine::transforms {

class profile_template_adaption_transform final {
private:
    static variability::meta_model::profile_template
    adapt(const variability::meta_model::feature_model& fm,
        const assets::meta_model::variability::profile_template& vpt);

public:
    static std::list<variability::meta_model::profile_template>
    apply(const context& ctx, const assets::meta_model::model_set& ms);
};

}

#endif
