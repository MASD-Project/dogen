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
#ifndef MASD_DOGEN_TEMPLATING_TYPES_STITCH_PROPERTIES_FACTORY_HPP
#define MASD_DOGEN_TEMPLATING_TYPES_STITCH_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.templating/types/stitch/properties.hpp"

namespace masd::dogen::templating::stitch {

/**
 * @brief Creates the stitching properties.
 */
class properties_factory {
public:
    properties_factory(const variability::type_repository& arp,
        const variability::meta_model::feature_model& fm);

private:
    struct type_group {
        variability::type stream_variable_name;
        variability::type relative_output_directory;
        variability::type inclusion_dependency;
        variability::type containing_namespaces;
        variability::type wale_template;
        variability::type wale_kvp;
    };

    /**
     * @brief Creates the formatter properties.
     */
    type_group
    make_type_group(const variability::type_repository& arp) const;

private:
    /**
     * @brief Extracts the stream variable name.
     */
    std::string
    extract_stream_variable_name(const variability::annotation& a) const;

    /**
     * @brief Extracts the relative output directory.
     */
    boost::filesystem::path
    extract_relative_output_directory(const variability::annotation& a) const;

    /**
     * @brief Extracts inclusion dependencies.
     */
    std::list<std::string>
    extract_inclusion_dependencies(const variability::annotation& o) const;

    /**
     * @brief Extract containing namespaces.
     */
    std::list<std::string>
    extract_containing_namespaces(const variability::annotation& a) const;

    /**
     * @brief Extract wale template
     */
    std::string extract_wale_template(const variability::annotation& a) const;

    /**
     * @brief Extract wale kvps
     */
    std::unordered_map<std::string, std::string>
    extract_wale_kvps(const variability::annotation& a) const;

private:
    struct feature_group {
        variability::meta_model::feature stream_variable_name;
        variability::meta_model::feature relative_output_directory;
        variability::meta_model::feature inclusion_dependency;
        variability::meta_model::feature containing_namespaces;
        variability::meta_model::feature wale_template;
        variability::meta_model::feature wale_kvp;
    };

    /**
     * @brief Creates the formatter properties.
     */
    feature_group
    make_feature_group(const variability::meta_model::feature_model& fm) const;

private:
    /**
     * @brief Extracts the stream variable name.
     */
    std::string
    extract_stream_variable_name(
        const variability::meta_model::configuration& cfg) const;

    /**
     * @brief Extracts the relative output directory.
     */
    boost::filesystem::path
    extract_relative_output_directory(
        const variability::meta_model::configuration& cfg) const;

    /**
     * @brief Extracts inclusion dependencies.
     */
    std::list<std::string>
    extract_inclusion_dependencies(
        const variability::meta_model::configuration& cfg) const;

    /**
     * @brief Extract containing namespaces.
     */
    std::list<std::string>
    extract_containing_namespaces(
        const variability::meta_model::configuration& cfg) const;

    /**
     * @brief Extract wale template
     */
    std::string extract_wale_template(
        const variability::meta_model::configuration& cfg) const;

    /**
     * @brief Extract wale kvps
     */
    std::unordered_map<std::string, std::string>
    extract_wale_kvps(const variability::meta_model::configuration& cfg) const;

public:
    /**
     * @brief Create the stitching settings.
     */
    properties make(const variability::meta_model::configuration& cfg) const;

public:
    /**
     * @brief Create the stitching settings.
     */
    properties make(const variability::annotation& a) const;

private:
    const type_group type_group_;
    const feature_group feature_group_;
};

}

#endif
