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
#ifndef DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_LOCATOR_HPP
#define DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_LOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.logical/types/meta_model/name.hpp"
#include "dogen.generation.csharp/types/formatters/repository.hpp"
#include "dogen.generation.csharp/types/formattables/locator_configuration.hpp"


namespace dogen::generation::csharp::formattables {

class locator final {
private:
    struct facet_feature_group {
        variability::meta_model::feature directory;
        variability::meta_model::feature postfix;
    };

    struct formatter_feature_group {
        boost::optional<variability::meta_model::feature> facet_directory;
        boost::optional<variability::meta_model::feature> facet_postfix;
        variability::meta_model::feature archefeature_postfix;
    };

    struct feature_group {
        std::unordered_map<std::string, facet_feature_group>
        facets_feature_group;
        std::unordered_map<std::string, formatter_feature_group>
        formatters_feature_group;
        variability::meta_model::feature backend_directory_name;
    };

    feature_group make_feature_group(
        const variability::meta_model::feature_model& fm,
        const formatters::repository& frp) const;

    locator_configuration make_configuration(const feature_group& tg,
        const variability::meta_model::configuration& cfg) const;

    locator_configuration
    make_configuration(const variability::meta_model::feature_model& fm,
        const formatters::repository& frp,
        const variability::meta_model::configuration& cfg);

private:
    /**
     * @brief Given an archetype, returns its configuration.
     *
     * @pre Archetype must have a configuration.
     */
    const locator_archetype_configuration& configuration_for_archetype(
        const std::string& archetype) const;

public:
    locator(
        const boost::filesystem::path& output_directory_path,
        const variability::meta_model::feature_model& fm,
        const formatters::repository& frp,
        const variability::meta_model::configuration& rcfg,
        const logical::meta_model::name& model_name,
        const std::unordered_set<std::string>& module_ids,
        const bool enable_backend_directories);

private:
    /**
     * @brief Returns the absolute path to the project folder.
     */
    boost::filesystem::path make_project_path(
        const boost::filesystem::path& output_directory_path,
        const logical::meta_model::name& model_name,
        const locator_configuration& lc,
        const bool enable_backend_directories) const;

    /**
     * @brief Generates the facet path segment of a file path.
     *
     * The facet path segment is the same for both include and source
     * folders; it starts at the facet and includes the file name.
     */
    boost::filesystem::path make_facet_path(const std::string& archetype,
        const std::string& extension, const logical::meta_model::name& n) const;

public:
    /**
     * @brief Top-level project directory.
     */
    const boost::filesystem::path project_path() const;

public:
    boost::filesystem::path make_relative_path(
        const boost::filesystem::path& full_path) const;

public:
    boost::filesystem::path make_full_path(const logical::meta_model::name& n,
        const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_project(
        const logical::meta_model::name& n, const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_solution(
        const logical::meta_model::name& n, const std::string& archetype) const;

private:
    const logical::meta_model::name& model_name_;
    const locator_configuration configuration_;
    const std::unordered_set<std::string> module_ids_;
    const boost::filesystem::path project_path_;
};

}

#endif
