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
#ifndef DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_FACTORY_HPP
#define DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/options/types/input_options.hpp"
#include "dogen/yarn/types/descriptor.hpp"
#include "dogen/yarn/types/frontend_registrar.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 *  @brief Performs the pre-merge sub-workflow.
 */
class intermediate_model_factory {
private:
    /**
     * @brief Performs a module expansion on the model.
     */
    void expand_modules(intermediate_model& im) const;

    /**
     * @brief Performs an expansion of all annotations objects on the
     * model.
     */
    void expand_annotations(const annotations::annotation_groups_factory& agf,
        intermediate_model& im) const;

    /**
     * @brief Performs the expansion of the origin type.
     */
    void expand_origin(const annotations::type_repository& atrp,
        intermediate_model& im) const;

    /**
     * @brief Performs a type parameters expansion on the model.
     */
    void expand_type_parameters(const annotations::type_repository& atrp,
        intermediate_model& im) const;

    /**
     * @brief Expand all parts of the model which require parsing.
     */
    void expand_parsing(const annotations::type_repository& atrp,
        intermediate_model& im) const;

    void post_process(const annotations::annotation_groups_factory& agf,
        const annotations::type_repository& atrp, intermediate_model& im) const;

    /**
     * @brief Obtains an intermediate model.
     */
    intermediate_model intermediate_model_for_descriptor(
        const annotations::annotation_groups_factory& agf,
        const annotations::type_repository& atrp,
        frontend_registrar& rg, const descriptor& descriptors) const;

public:
    /**
     * @brief Executes the workflow.
     */
    std::vector<intermediate_model>
    make(const std::vector<boost::filesystem::path>& dirs,
        const annotations::annotation_groups_factory& agf,
        const annotations::type_repository& atrp,
        const options::input_options& io,
        frontend_registrar& rg) const;
};

} }

#endif
