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
#ifndef DOGEN_TEMPLATING_TYPES_STITCH_INSTANTIATOR_HPP
#define DOGEN_TEMPLATING_TYPES_STITCH_INSTANTIATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/helpers/configuration_factory.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.templating/types/stitch/text_template.hpp"

namespace dogen::templating::stitch {

/**
 * @brief Provides file name information on errors.
 */
typedef boost::error_info<struct tag_file_name, std::string> error_in_file;

class instantiator final {
public:
    instantiator(const boost::filesystem::path& wale_templates_directory,
        const variability::entities::feature_model& fm,
        const variability::helpers::configuration_factory& cf);

private:
    /**
     * @brief Computes the output path, given the template input path.
     */
    boost::filesystem::path
    compute_output_path(const boost::filesystem::path& input_path,
        const properties& props) const;

    /**
     * @brief Reads the supplied stitch text template into memory as a
     * raw string.
     */
    std::string read_text_template(const boost::filesystem::path& p) const;

    /**
     * @brief Finds all of the variable blocks in the template, and
     * uses them to update the expected keys.
     */
    void update_expected_keys(text_template& tt) const;

    /**
     * @brief Instantiates the wale template, if configured.
     */
    void handle_wale_template(text_template& tt) const;

    /**
     * @brief Merge external KVPs with existing KVPs.
     */
    void merge_kvps(const std::unordered_map<std::string, std::string>& kvps,
        text_template& tt) const;

    /**
     * @brief Validate the supplied KVPs.
     */
    void validate_kvps(text_template& tt) const;

    /**
     * @brief Creates the properties.
     */
    properties create_properties(
        const variability::entities::configuration& cfg) const;

    /**
     * @brief Creates the text template.
     */
    text_template create_text_template(
        const boost::filesystem::path& input_path,
        const std::string& text_template_as_string,
        const std::unordered_map<std::string, std::string>& kvps) const;

    /**
     * @brief Formats the supplied text template.
     */
    physical::entities::artefact
    format_text_template(const text_template& tt) const;

public:
    /**
     * @brief Instantiate the template from a string, using the
     * supplied KVPs.
     */
    std::string instantiate(const std::string& input,
        const std::unordered_map<std::string, std::string>& kvps) const;

    /**
     * @brief Instantiate the template from a file, using the supplied
     * KVPs.
     */
    physical::entities::artefact
    instantiate(const boost::filesystem::path& input_path,
        const std::unordered_map<std::string, std::string>& kvps) const;

private:
    const boost::filesystem::path wale_templates_directory_;
    const variability::helpers::configuration_factory& configuration_factory_;
    const variability::entities::feature_model& feature_model_;
};

}

#endif
