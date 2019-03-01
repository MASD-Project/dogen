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
#include "masd.dogen.annotations/types/type.hpp"
#include "masd.dogen.annotations/types/annotation.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"
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
        annotations::type force_write;
        annotations::type delete_extra_files;
        annotations::type ignore_files_matching_regex;
        annotations::type cpp_headers_output_directory;
        annotations::type enable_backend_directories;
        std::list<annotations::type> enabled;
    };

    static type_group make_type_group(const annotations::type_repository& atrp,
        const std::list<annotations::archetype_location>& als);

    static bool obtain_force_write(const type_group& tg,
        const annotations::annotation& ra);

    static bool obtain_delete_extra_files(const type_group& tg,
        const annotations::annotation& ra);

    static std::vector<std::string> obtain_ignore_files_matching_regex(
        const type_group& tg, const annotations::annotation& ra);

    static boost::filesystem::path obtain_cpp_headers_output_directory(
        const type_group& tg, const annotations::annotation& ra);

    static std::unordered_set<std::string> obtain_enabled_backends(
        const type_group& tg, const annotations::annotation& ra);

    static bool obtain_enable_backend_directories(const type_group& tg,
        const annotations::annotation& ra);

    static meta_model::extraction_properties make_extraction_properties(
        const context& ctx,
        const std::list<annotations::archetype_location>& als,
        const annotations::annotation& ra);

public:
    /**
     * Execute the extraction properties transform.
     */
    static void transform(const context& ctx, meta_model::model& m);
};

}

#endif
