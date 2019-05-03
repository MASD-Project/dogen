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
#ifndef MASD_DOGEN_ENGINE_TYPES_TRANSFORMS_INJECTION_MODEL_TO_CODING_MODEL_TRANSFORM_HPP
#define MASD_DOGEN_ENGINE_TYPES_TRANSFORMS_INJECTION_MODEL_TO_CODING_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <vector>
#include <unordered_map>
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.injection/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/location.hpp"
#include "masd.dogen.coding/types/meta_model/attribute.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.engine/types/transforms/context_fwd.hpp"
#include "masd.dogen.engine/types/helpers/adapter.hpp"
#include "masd.dogen.engine/types/transforms/naming_configuration.hpp"

namespace masd::dogen::engine::transforms {

class injection_model_to_coding_model_transform final {
private:
    struct feature_group {
        variability::meta_model::feature external_modules;
        variability::meta_model::feature model_modules;
    };

    static feature_group
    make_feature_group(const variability::meta_model::feature_model& fm);

    static naming_configuration
    make_naming_configuration(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

private:
    static coding::meta_model::location
    create_location(const naming_configuration& nc);

    static coding::meta_model::static_stereotypes compute_element_type(
        const std::list<coding::meta_model::static_stereotypes>& st,
        const std::string& fallback_element_type);

    static void process_element(const helpers::adapter& ad,
        const coding::meta_model::location& l,
        const injection::meta_model::element& ie,
        coding::meta_model::model& m);

public:
    static coding::meta_model::model
    apply(const context& ctx, const injection::meta_model::model& m);
};

}

#endif
