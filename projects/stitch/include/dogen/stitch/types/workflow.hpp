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

#include <string>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/ownership_hierarchy.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/stitch/types/properties.hpp"
#include "dogen/stitch/types/text_template.hpp"
#include "dogen/stitch/types/formatter.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Provides file name information on errors.
 */
typedef boost::error_info<struct tag_file_name, std::string> error_in_file;

/**
 * @brief Performs the stitch workflow.
 */
class workflow {
public:
    workflow();

private:
    /**
     * @brief Expands the annotations object.
     */
    void perform_expansion(const boost::filesystem::path& p,
        annotations::annotation& a) const;

private:
    /**
     * @brief Returns the absolute path for the supplied path.
     */
    boost::filesystem::path make_absolute_path_activity(
        const boost::filesystem::path& p) const;

    /**
     * @brief Returns all stitch templates that can be found from p.
     *
     * If p is a file, it is returned if its extension is @code
     * .stitch. If p is a directory, it and it sub-directories are
     * searched for files with the @code .stitch extension.
     */
    std::forward_list<boost::filesystem::path> get_text_template_paths_activity(
        const boost::filesystem::path& file_or_directory) const;

    /**
     * @brief Ensures the file paths point to valid templates.
     */
    void validate_text_template_paths(
        const std::forward_list<boost::filesystem::path>&
        text_template_paths) const;

    /**
     * @brief Reads all of the supplied stitch text templates into memory.
     */
    std::forward_list<std::pair<boost::filesystem::path, std::string> >
    read_text_templates_activity(
        const std::forward_list<boost::filesystem::path>&
        text_template_paths) const;

    /**
     * @brief Obtains the ownership hierarchy.
     */
    std::forward_list<annotations::ownership_hierarchy>
    obtain_ownership_hierarchy_activity() const;

    /**
     * @brief Creates the formatters' repository.
     */
    dogen::formatters::repository create_formatters_repository_activity() const;

    /**
     * @brief Sets up the annotations repository.
     */
    annotations::type_repository create_annotations_repository_activity(
        const std::forward_list<annotations::ownership_hierarchy>& oh)
        const;

    /**
     * @brief Parses all of the strings that contain text templates.
     */
    std::forward_list<text_template> parse_text_templates_activity(
        const annotations::type_repository& rp,
        const std::forward_list<
        std::pair<boost::filesystem::path, std::string>
        >& text_templates_as_string) const;

    /**
     * @brief Creates the properties.
     */
    void populate_properties_activity(
        const annotations::type_repository& annotations_repository,
        const dogen::formatters::repository& formatters_repository,
        std::forward_list<text_template>& text_templates) const;

    /**
     * @brief Formats all of the supplied text templates.
     */
    std::forward_list<formatters::file> format_text_templates_activity(
        const std::forward_list<text_template>& text_templates) const;

    /**
     * @brief Writes all of the files into the filesystem.
     */
    void write_files_activity(
        const std::forward_list<formatters::file>& files) const;

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

private:
    const formatter formatter_;
};

} }

#endif
