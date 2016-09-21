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
 * GNU General Public License for more details. *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_YARN_TYPES_PRE_MERGE_WORKFLOW_HPP
#define DOGEN_YARN_TYPES_PRE_MERGE_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/types/repository.hpp"
#include "dogen/options/types/input_options.hpp"
#include "dogen/yarn/types/descriptor.hpp"
#include "dogen/yarn/types/frontend_registrar.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 *  @brief Performs the pre-merge sub-workflow.
 */
class pre_merge_workflow {
private:
    /**
     * @brief Obtain the model descriptors.
     */
    std::list<descriptor> obtain_descriptors(
        const std::list<boost::filesystem::path>& dirs,
        const options::input_options& io) const;

    /**
     * @brief Obtains all intermediate models.
     */
    std::list<intermediate_model> obtain_intermediate_models(
        const dynamic::repository& drp, frontend_registrar& rg,
        const std::list<descriptor>& d) const;

    /**
     * @brief Performs a module expansion on the model.
     */
    void do_modules_expansion(intermediate_model& im) const;

    /**
     * @brief Performs a local attribute expansion on the model.
     */
    void do_parsing_expansion(intermediate_model& im) const;

    /**
     * @brief Performs a annotations expansion on the model.
     */
    void do_annotations_expansion(const dynamic::repository& drp,
        intermediate_model& im) const;

public:
    /**
     * @brief Executes the workflow.
     */
    std::list<intermediate_model> execute(const dynamic::repository& drp,
        const std::list<boost::filesystem::path>& dirs,
        const options::input_options& io,
        frontend_registrar& rg) const;
};

} }

#endif
