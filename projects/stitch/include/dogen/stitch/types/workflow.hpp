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
#ifndef DOGEN_STITCH_TYPES_WORKFLOW_HPP
#define DOGEN_STITCH_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/annotations/types/archetype_location_repository.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/stitch/types/properties.hpp"
#include "dogen/stitch/types/properties_factory.hpp"
#include "dogen/stitch/types/text_template.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Performs the stitch workflow.
 */
class workflow {
private:
    std::vector<boost::filesystem::path> create_data_directories() const;

    /**
     * @brief Returns the absolute path for the supplied path.
     */
    boost::filesystem::path make_absolute_path(
        const boost::filesystem::path& p) const;

    /**
     * @brief Returns all stitch templates that can be found from p.
     *
     * If p is a file, it is returned if its extension is @code
     * .stitch. If p is a directory, it and it sub-directories are
     * searched for files with the @code .stitch extension.
     */
    std::forward_list<boost::filesystem::path> get_text_template_paths(
        const boost::filesystem::path& file_or_directory) const;

    /**
     * @brief Ensures the file paths point to valid templates.
     */
    void validate_text_template_paths(
        const std::forward_list<boost::filesystem::path>&
        text_template_paths) const;

private:
    /**
     * @brief Obtains the archetype location repository.
     */
    annotations::archetype_location_repository
    obtain_archetype_location_repository() const;

    /**
     * @brief Creates the formatters' repository.
     */
    dogen::formatters::repository create_formatters_repository(
        const std::vector<boost::filesystem::path>& data_dirs) const;

    /**
     * @brief Sets up the annotations repository.
     */
    annotations::type_repository create_annotations_type_repository(
        const std::vector<boost::filesystem::path>& data_dirs,
        const annotations::archetype_location_repository& alrp)
        const;

    /**
     * @brief Creates the artefacts
     */
    std::forward_list<formatters::artefact> create_artefacts(
        const annotations::annotation_groups_factory& af,
        const properties_factory& pf,
        const std::forward_list<boost::filesystem::path>&
        text_template_paths) const;

    /**
     * @brief Writes all of the artefacts to the filesystem.
     */
    void write_artefacts(
        const std::forward_list<formatters::artefact>& artefacts) const;

public:
    /**
     * @brief Execute the workflow.
     *
     * This is done in one of two modes:
     *
     * @li if @code p is a directory, finds all stitch templates in
     * that directory or any of its sub-directories and, for each
     * template, code-generates the stitch templates.
     *
     * @li if @code p is a file, code-generates the stitch template.
     */
    void execute(const boost::filesystem::path& p) const;
};

} }

#endif
