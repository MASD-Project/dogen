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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_EXTRACTION_PROPERTIES_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_EXTRACTION_PROPERTIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.physical/types/entities/artefact_repository.hpp"
#include "dogen.physical/types/transforms/context.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Expands all extraction properties from meta-data.
 */
class extraction_properties_transform final {
private:
    struct feature_group {
        variability::entities::feature cpp_headers_output_directory;
        variability::entities::feature enable_backend_directories;
        std::unordered_map<std::string,
                           variability::entities::feature> enabled;
    };

    static feature_group make_feature_group(
        const variability::entities::feature_model& fm,
        const std::list<physical::entities::meta_name>& mns);

    static boost::filesystem::path
    obtain_cpp_headers_output_directory(const feature_group& fg,
        const variability::entities::configuration& cfg);

    static std::unordered_set<std::string>
    obtain_enabled_backends(const feature_group& fg,
        const variability::entities::configuration& cfg);

    static bool obtain_enable_backend_directories(const feature_group& fg,
        const variability::entities::configuration& cfg);

    static entities::extraction_properties make_extraction_properties(
        const context& ctx, const std::list<physical::entities::meta_name>& mns,
        const variability::entities::configuration& cfg);

public:
    /**
     * Applies the extraction properties transform to the supplied
     * model.
     */
    static void apply(const context& ctx, entities::artefact_repository& ar);
};

}

#endif
