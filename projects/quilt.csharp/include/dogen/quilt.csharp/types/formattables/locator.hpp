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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FORMATTABLES_LOCATOR_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FORMATTABLES_LOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/quilt.csharp/types/formatters/repository.hpp"
#include "dogen/quilt.csharp/types/formattables/locator_configuration.hpp"


namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

class locator final {
private:
    struct type_group {
        std::unordered_map<std::string, annotations::type> facet_directories;
        std::unordered_map<std::string, annotations::type>
        formatters_directories;
        annotations::type kernel_directory_name;
    };

    type_group make_type_group(const annotations::type_repository& atrp,
        const formatters::repository& frp) const;

    locator_configuration make_configuration(const type_group& tg,
        const annotations::annotation& o) const;

    locator_configuration
    make_configuration(const annotations::type_repository& atrp,
        const formatters::repository& frp, const annotations::annotation& a);

public:
    locator(
        const boost::filesystem::path& output_directory_path,
        const annotations::type_repository& atrp,
        const formatters::repository& frp, const annotations::annotation& ra,
        const yarn::name& model_name,
        const std::unordered_set<std::string>& module_ids,
        const bool enable_kernel_directories);

private:
    /**
     * @brief Returns the absolute path to the project folder.
     */
    boost::filesystem::path make_project_path(
        const boost::filesystem::path& output_directory_path,
        const yarn::name& model_name, const locator_configuration& lc,
        const bool enable_kernel_directories) const;

    /**
     * @brief Generates the facet path segment of a file path.
     *
     * The facet path segment is the same for both include and source
     * folders; it starts at the facet and includes the file name.
     */
    boost::filesystem::path make_facet_path(const std::string& archetype,
        const std::string& extension, const yarn::name& n) const;

public:
    boost::filesystem::path
    make_full_path(const yarn::name& n, const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_project(
        const yarn::name& n, const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_solution(
        const yarn::name& n, const std::string& archetype) const;

private:
    const yarn::name& model_name_;
    const locator_configuration configuration_;
    const std::unordered_set<std::string> module_ids_;
    const boost::filesystem::path project_path_;
};

} } } }

#endif
