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
#ifndef MASD_DOGEN_INJECTION_TYPES_TRANSFORMS_REFERENCES_TRANSFORM_HPP
#define MASD_DOGEN_INJECTION_TYPES_TRANSFORMS_REFERENCES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.injection/types/meta_model/model.hpp"
#include "masd.dogen.injection/types/transforms/context_fwd.hpp"

namespace masd::dogen::injection::transforms {

/**
 * @brief Reads the model references from the annotation.
 */
class references_transform final {
private:
    struct feature_group {
        variability::meta_model::feature reference;
    };

    static feature_group
    make_feature_group(const variability::meta_model::feature_model& fm);

    static std::list<std::string> make_references(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
