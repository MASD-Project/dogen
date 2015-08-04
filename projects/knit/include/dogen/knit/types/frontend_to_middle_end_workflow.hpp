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
#ifndef DOGEN_KNIT_TYPES_FRONTEND_TO_MIDDLE_END_WORKFLOW_HPP
#define DOGEN_KNIT_TYPES_FRONTEND_TO_MIDDLE_END_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/archive_types.hpp"
#include "dogen/config/types/knitting_options.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/ownership_hierarchy.hpp"
#include "dogen/frontend/types/input_descriptor.hpp"
#include "dogen/tack/types/model.hpp"

namespace dogen {
namespace knit {

/**
 * @brief Performs the frontend to middle-end workflow.
 */
class frontend_to_middle_end_workflow {
public:
    frontend_to_middle_end_workflow(const config::knitting_options& o,
        const dynamic::repository& rp);

private:
    /**
     * @brief Given an archive type and a model name, returns the
     * appropriate file extension.
     *
     * @param archive_type one of the supported boost archive types.
     */
    std::string extension(const config::archive_types at) const;

    /**
     * @brief Given the original file path, generates a new file path
     * for the archive in question.
     */
    boost::filesystem::path
    create_debug_file_path(const config::archive_types at,
        const boost::filesystem::path& original_path) const;

private:
    /**
     * @brief Create a list of all input descriptors.
     */
    std::list<frontend::input_descriptor>
    obtain_input_descriptors_activity() const;

    /**
     * @brief Obtains all partial Tack models.
     */
    std::list<tack::model> obtain_partial_tack_models_activity(
        const std::list<frontend::input_descriptor>& descriptors) const;

    /**
     * @brief Returns the path to the target model.
     */
    boost::filesystem::path obtain_target_path_activity(
        const std::list<frontend::input_descriptor>& descriptors) const;

    /**
     * @brief Execute the tack assembling workflow.
     */
    tack::model assemble_models_activity(
        const std::list<tack::model>& models) const;

    /**
     * @brief Checks the options chosen by the user to determine if
     * the Tack model should be persisted; if so, persists it.
     */
    void persist_model_activity(const boost::filesystem::path p,
        const tack::model& m) const;

public:
    /**
     * @brief Executes the workflow.
     */
    tack::model execute() const;

private:
    const config::knitting_options& knitting_options_;
    const dynamic::repository repository_;
};

} }

#endif
