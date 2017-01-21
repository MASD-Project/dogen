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
#ifndef DOGEN_YARN_UPSILON_TYPES_WORKFLOW_HPP
#define DOGEN_YARN_UPSILON_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/upsilon/types/name.hpp"
#include "dogen/upsilon/types/model.hpp"
#include "dogen/upsilon/types/output.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {
namespace upsilon {

class workflow final {
private:
    /**
     * @brief Obtains a list of output languages from the upsilon
     * configuration.
     */
    std::list<languages> obtain_output_languages(
        const std::vector<dogen::upsilon::output>& outputs) const;

    /**
     * @brief Creates a map of schema names to yarn model names.
     */
    std::unordered_map<std::string, dogen::yarn::name>
    map_schema_name_to_model_name(const dogen::upsilon::model& um) const;

    /**
     * @brief Gathers all of the names of collections on the upsilon
     * model.
     */
    std::unordered_map<std::string, dogen::upsilon::name>
    obtain_collection_names(const dogen::upsilon::model& um) const;

    /**
     * @brief Creates an empty yarn model with the basic properties
     * set.
     */
    yarn::intermediate_model
    create_model(const dogen::upsilon::model& um) const;

    /**
     * @brief Populates the yarn model with all the upsilon types.
     */
    void populate_model(const dogen::upsilon::model& um,
        const std::unordered_map<std::string, dogen::yarn::name>&
        schema_name_to_model_name,
        const std::unordered_map<std::string, dogen::upsilon::name>&
        collection_names, yarn::intermediate_model& im) const;

public:
    yarn::intermediate_model execute(const dogen::upsilon::model& um) const;
};

} } }

#endif
