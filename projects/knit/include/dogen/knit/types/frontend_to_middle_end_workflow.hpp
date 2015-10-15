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
#ifndef DOGEN_KNIT_TYPES_FRONTEND_TO_MIDDLE_END_WORKFLOW_HPP
#define DOGEN_KNIT_TYPES_FRONTEND_TO_MIDDLE_END_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/knitting_options.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/ownership_hierarchy.hpp"
#include "dogen/yarn/types/input_descriptor.hpp"
#include "dogen/yarn/types/model.hpp"

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
     * @brief Create a list of all input descriptors.
     */
    std::list<yarn::input_descriptor>
    obtain_input_descriptors_activity() const;

    /**
     * @brief Obtains all partial Yarn models.
     */
    std::list<yarn::model> import_yarn_models_activity(
        const std::list<yarn::input_descriptor>& descriptors) const;

    /**
     * @brief Execute the yarn assembling workflow.
     */
    yarn::model assemble_yarn_models_activity(
        const std::list<yarn::model>& models) const;

    /**
     * @brief Returns the path to the target model.
     */
    boost::filesystem::path obtain_target_path_activity(
        const std::list<yarn::input_descriptor>& descriptors) const;

public:
    /**
     * @brief Executes the workflow.
     */
    yarn::model execute() const;

private:
    const config::knitting_options& knitting_options_;
    const dynamic::repository repository_;
};

} }

#endif
