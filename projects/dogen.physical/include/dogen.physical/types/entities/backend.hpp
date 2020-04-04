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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_BACKEND_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/part.hpp"
#include "dogen.physical/types/entities/facet.hpp"
#include "dogen.physical/types/entities/location.hpp"
#include "dogen.physical/types/entities/archetype.hpp"
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.physical/types/entities/archetype_kind.hpp"

namespace dogen::physical::entities {

/**
 * @brief Code generation backend, targeting a given technical space.
 */
class backend final {
public:
    backend() = default;
    backend(const backend&) = default;
    backend(backend&&) = default;
    ~backend() = default;

public:
    backend(
        const std::string& default_directory_name,
        const std::string& override_directory_name,
        const dogen::physical::entities::location& location,
        const std::string& description,
        const dogen::physical::entities::meta_name& meta_name,
        const std::unordered_map<std::string, dogen::physical::entities::part>& parts,
        const std::unordered_map<std::string, dogen::physical::entities::facet>& facets,
        const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes,
        const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& archetype_kinds);

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

    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::physical::entities::meta_name& meta_name() const;
    dogen::physical::entities::meta_name& meta_name();
    void meta_name(const dogen::physical::entities::meta_name& v);
    void meta_name(const dogen::physical::entities::meta_name&& v);
    /**@}*/

    const std::unordered_map<std::string, dogen::physical::entities::part>& parts() const;
    std::unordered_map<std::string, dogen::physical::entities::part>& parts();
    void parts(const std::unordered_map<std::string, dogen::physical::entities::part>& v);
    void parts(const std::unordered_map<std::string, dogen::physical::entities::part>&& v);

    const std::unordered_map<std::string, dogen::physical::entities::facet>& facets() const;
    std::unordered_map<std::string, dogen::physical::entities::facet>& facets();
    void facets(const std::unordered_map<std::string, dogen::physical::entities::facet>& v);
    void facets(const std::unordered_map<std::string, dogen::physical::entities::facet>&& v);

    const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes() const;
    std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes();
    void archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v);
    void archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v);

    const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& archetype_kinds() const;
    std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& archetype_kinds();
    void archetype_kinds(const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& v);
    void archetype_kinds(const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>&& v);

public:
    bool operator==(const backend& rhs) const;
    bool operator!=(const backend& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(backend& other) noexcept;
    backend& operator=(backend other);

private:
    std::string default_directory_name_;
    std::string override_directory_name_;
    dogen::physical::entities::location location_;
    std::string description_;
    dogen::physical::entities::meta_name meta_name_;
    std::unordered_map<std::string, dogen::physical::entities::part> parts_;
    std::unordered_map<std::string, dogen::physical::entities::facet> facets_;
    std::unordered_map<std::string, dogen::physical::entities::archetype> archetypes_;
    std::unordered_map<std::string, dogen::physical::entities::archetype_kind> archetype_kinds_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::backend& lhs,
    dogen::physical::entities::backend& rhs) {
    lhs.swap(rhs);
}

}

#endif
