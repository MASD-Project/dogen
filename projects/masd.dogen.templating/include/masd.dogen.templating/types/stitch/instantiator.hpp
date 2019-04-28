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
#ifndef MASD_DOGEN_TEMPLATING_TYPES_STITCH_INSTANTIATOR_HPP
#define MASD_DOGEN_TEMPLATING_TYPES_STITCH_INSTANTIATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.variability/types/annotation_factory.hpp"
#include "masd.dogen.variability/types/helpers/configuration_factory.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.extraction/types/meta_model/artefact.hpp"
#include "masd.dogen.templating/types/stitch/properties_factory.hpp"
#include "masd.dogen.templating/types/stitch/text_template.hpp"

namespace masd::dogen::templating::stitch {

/**
 * @brief Provides file name information on errors.
 */
typedef boost::error_info<struct tag_file_name, std::string> error_in_file;

class instantiator final {
public:
    instantiator(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& fm,
        const bool use_configuration,
        const variability::annotation_factory& af,
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
     * @brief Creates the text template.
     */
    text_template create_text_template(
        const boost::filesystem::path& input_path,
        const std::string& text_template_as_string,
        const std::unordered_map<std::string, std::string>& kvps) const;

    /**
     * @brief Formats the supplied text template.
     */
    extraction::meta_model::artefact
    format_text_template(const text_template& tt) const;

public:
    extraction::meta_model::artefact
    instantiate(const boost::filesystem::path& input_path,
        const std::unordered_map<std::string, std::string>& kvps) const;

private:
    bool use_configuration_;
    const variability::annotation_factory& annotation_factory_;
    const variability::helpers::configuration_factory& configuration_factory_;
    const properties_factory properties_factory_;
};

}

#endif
