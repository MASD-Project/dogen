/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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

#include <list>
#include <string>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/formatters/types/file.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/dynamic/schema/types/ownership_hierarchy.hpp"
#include "dogen/stitch/types/settings_bundle.hpp"
#include "dogen/stitch/types/text_template.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Performs the stitch workflow.
 */
class workflow {
private:
    /**
     * @brief Returns all stitch templates that can be found from p.
     *
     * If p is a file, it is returned if its extension is @code
     * .stitch. If p is a directory, it and it sub-directories are
     * searched for files with the @code .stitch extension.
     */
    std::list<boost::filesystem::path> get_text_template_paths_activity(
        const boost::filesystem::path& file_or_directory) const;

    /**
     * @brief Reads all of the supplied stitch text templates into memory.
     */
    std::list<std::string> read_text_templates_activity(
        const std::list<boost::filesystem::path>& text_template_paths) const;

    /**
     * @brief Obtains the ownership hierarchy.
     */
    std::forward_list<dynamic::schema::ownership_hierarchy>
    obtain_ownership_hierarchy_activity() const;

    /**
     * @brief Sets up the dynamic schema repository.
     */
    dynamic::schema::repository setup_schema_repository_activity(
        const std::forward_list<dynamic::schema::ownership_hierarchy>& oh)
        const;

    /**
     * @brief Parses all of the strings that contain text templates.
     */
    std::list<text_template> parse_text_templates_activity(
        const std::list<std::string>& text_templates_as_string) const;

    /**
     * @brief Creates the settings bundles.
     */
    std::list<text_template> obtain_settings_bundle_activity(
        const std::list<text_template>& text_template) const;

    /**
     * @brief Formats all of the supplied text templates.
     */
    std::list<formatters::file> format_text_templates_activity(
        const std::list<text_template>& text_templates) const;

    /**
     * @brief Outputs all of the files into the filesystem.
     */
    void output_files_activity(const std::list<formatters::file>& files) const;

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
