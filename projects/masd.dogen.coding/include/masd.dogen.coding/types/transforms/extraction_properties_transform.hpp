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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_EXTRACTION_PROPERTIES_TRANSFORM_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_EXTRACTION_PROPERTIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include <boost/optional.hpp>
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/extraction_properties.hpp"

namespace masd::dogen::coding::transforms {

/**
 * @brief Expands all extraction properties from meta-data.
 */
class extraction_properties_transform final {
private:
    struct type_group {
        variability::type cpp_headers_output_directory;
        variability::type enable_backend_directories;
        std::list<variability::type> enabled;
    };

    static type_group make_type_group(const variability::type_repository& atrp,
        const std::list<archetypes::location>& als);

    static boost::filesystem::path obtain_cpp_headers_output_directory(
        const type_group& tg, const variability::annotation& ra);

    static std::unordered_set<std::string> obtain_enabled_backends(
        const type_group& tg, const variability::annotation& ra);

    static bool obtain_enable_backend_directories(const type_group& tg,
        const variability::annotation& ra);

    static meta_model::extraction_properties make_extraction_properties(
        const context& ctx,
        const std::list<archetypes::location>& als,
        const variability::annotation& ra);

private:
    struct feature_group {
        variability::meta_model::feature cpp_headers_output_directory;
        variability::meta_model::feature enable_backend_directories;
        std::list<variability::meta_model::feature> enabled;
    };

    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm,
        const std::list<archetypes::location>& als);

    static boost::filesystem::path
    obtain_cpp_headers_output_directory(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::unordered_set<std::string>
    obtain_enabled_backends(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static bool obtain_enable_backend_directories(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static meta_model::extraction_properties make_extraction_properties(
        const context& ctx,
        const std::list<archetypes::location>& als,
        const variability::meta_model::configuration& cfg);

public:
    /**
     * Applies the extraction properties transform to the supplied
     * model.
     */
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
