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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_PART_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_PART_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/name.hpp"
#include "dogen.physical/types/entities/facet.hpp"
#include "dogen.physical/types/entities/location.hpp"
#include "dogen.physical/types/entities/archetype.hpp"
#include "dogen.physical/types/entities/path_configuration.hpp"

namespace dogen::physical::entities {

class part final {
public:
    part(const part&) = default;
    part(part&&) = default;
    ~part() = default;

public:
    part();

public:
    part(
        const std::string& default_directory_name,
        const std::string& override_directory_name,
        const dogen::physical::entities::location& location,
        const std::string& description,
        const dogen::physical::entities::name& name,
        const dogen::physical::entities::path_configuration& path_configuration,
        const std::unordered_map<std::string, dogen::physical::entities::facet>& facets,
        const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes,
        const bool requires_relative_path);

public:
    /**
     * @brief Default directory name.
     */
    /**@{*/
    const std::string& default_directory_name() const;
    std::string& default_directory_name();
    void default_directory_name(const std::string& v);
    void default_directory_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Override directory name, if any.
     */
    /**@{*/
    const std::string& override_directory_name() const;
    std::string& override_directory_name();
    void override_directory_name(const std::string& v);
    void override_directory_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Position of this entity in physical space.
     */
    /**@{*/
    const dogen::physical::entities::location& location() const;
    dogen::physical::entities::location& location();
    void location(const dogen::physical::entities::location& v);
    void location(const dogen::physical::entities::location&& v);
    /**@}*/

    /**
     * @brief Human readable description of the entity.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

    const dogen::physical::entities::name& name() const;
    dogen::physical::entities::name& name();
    void name(const dogen::physical::entities::name& v);
    void name(const dogen::physical::entities::name&& v);

    const dogen::physical::entities::path_configuration& path_configuration() const;
    dogen::physical::entities::path_configuration& path_configuration();
    void path_configuration(const dogen::physical::entities::path_configuration& v);
    void path_configuration(const dogen::physical::entities::path_configuration&& v);

    const std::unordered_map<std::string, dogen::physical::entities::facet>& facets() const;
    std::unordered_map<std::string, dogen::physical::entities::facet>& facets();
    void facets(const std::unordered_map<std::string, dogen::physical::entities::facet>& v);
    void facets(const std::unordered_map<std::string, dogen::physical::entities::facet>&& v);

    const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes() const;
    std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes();
    void archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v);
    void archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v);

    /**
     * @brief If true, this part needs a path relative to its root.
     */
    /**@{*/
    bool requires_relative_path() const;
    void requires_relative_path(const bool v);
    /**@}*/

public:
    bool operator==(const part& rhs) const;
    bool operator!=(const part& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(part& other) noexcept;
    part& operator=(part other);

private:
    std::string default_directory_name_;
    std::string override_directory_name_;
    dogen::physical::entities::location location_;
    std::string description_;
    dogen::physical::entities::name name_;
    dogen::physical::entities::path_configuration path_configuration_;
    std::unordered_map<std::string, dogen::physical::entities::facet> facets_;
    std::unordered_map<std::string, dogen::physical::entities::archetype> archetypes_;
    bool requires_relative_path_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::part& lhs,
    dogen::physical::entities::part& rhs) {
    lhs.swap(rhs);
}

}

#endif
