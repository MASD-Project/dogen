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
#ifndef DOGEN_ORCHESTRATION_TYPES_HELPERS_DEPENDENCIES_BUILDER_HPP
#define DOGEN_ORCHESTRATION_TYPES_HELPERS_DEPENDENCIES_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/entities/inclusion_directives.hpp"
#include "dogen.text/types/entities/model.hpp"
#include "dogen.text/types/transforms/context_fwd.hpp"

namespace dogen::orchestration::helpers {

/**
 * @brief Helps in building the inclusion dependencies for a given
 * formatteridentification::entities::logical_meta_physical_id.
 */
class dependencies_builder {
public:
    dependencies_builder(const std::unordered_map<
        identification::entities::logical_meta_physical_id,
        physical::entities::inclusion_directives>& ids,
        const std::unordered_set<
        identification::entities::logical_meta_physical_id>&
        enabled_archetype_for_element);

private:
    /**
     * @brief Returns the inclusion directive group for a given name
     * and formatter name.
     *
     * @pre name must exist in path derivatives collection.
     */
    boost::optional<physical::entities::inclusion_directives>
    get_directive_group(const identification::entities::logical_name& n,
        const std::string& archetype) const;

public:
    /**
     * @brief Returns true if the formatter is enabled.
     */
    bool is_enabled(const identification::entities::logical_name& n,
        const std::string& archetype) const;

public:
    /**
     * @brief Adds the supplied inclusion directive.
     */
    /**@{*/
    void add(const std::string& directive);
    void add(const std::list<std::string>& directives);
    /**@{*/

    /**
     * @brief Adds include as a system include, i.e. with angle
     * brackets.
     */
    void add_as_system(const std::string& directive);

    /**
     * @brief Adds include as a user include, i.e. with double quotes.
     */
    void add_as_user(const std::string& directive);

    /**
     * @brief Adds the inclusion directive for the supplied archetype
     * and name.
     */
    /**@{*/
    void add(const identification::entities::logical_name& n,
        const std::string& archetype);
    void add(const boost::optional<identification::entities::logical_name>& n,
        const std::string& archetype);
    /**@}*/

    /**
     * @brief Adds the inclusion directives for the supplied
     * archetype, for each of the supplied names.
     */
    void add(const std::list<identification::entities::logical_name>& names,
        const std::string& archetype);

    /**
     * @brief Adds the inclusion directive for the supplied archetype
     * and name.
     */
    /**@{*/
    void add(const identification::entities::logical_name& n,
        const identification::entities::physical_meta_id& archetype);
    void add(const boost::optional<identification::entities::logical_name>& n,
        const identification::entities::physical_meta_id& archetype);
    /**@}*/

    /**
     * @brief Adds the inclusion directives for the supplied
     * archetype, for each of the supplied names.
     */
    void add(const std::list<identification::entities::logical_name>& names,
        const identification::entities::physical_meta_id& archetype);

public:
    /**
     * @brief Builds the inclusion dependencies. All additions must
     * have been performed already.
     */
    std::list<std::string> build();

private:
    const std::unordered_map<identification::entities::logical_meta_physical_id,
                             physical::entities::inclusion_directives>&
    inclusion_directives_;
    std::list<std::string> dependencies_;
    const std::unordered_set<
        identification::entities::logical_meta_physical_id>&
    enabled_archetype_for_element_;
};

}

#endif
