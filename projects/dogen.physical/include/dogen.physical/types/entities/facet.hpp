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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_FACET_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_FACET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/archetype.hpp"
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.identification/types/entities/label.hpp"

namespace dogen::physical::entities {

class facet final {
public:
    facet() = default;
    facet(const facet&) = default;
    facet(facet&&) = default;
    ~facet() = default;

public:
    facet(
        const std::string& default_directory_name,
        const std::string& override_directory_name,
        const std::string& description,
        const dogen::physical::entities::meta_name& meta_name,
        const std::list<dogen::identification::entities::label>& labels,
        const std::string& default_postfix,
        const std::string& override_postfix,
        const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes,
        const std::unordered_map<std::string, dogen::physical::entities::archetype>& default_archetype_for_logical_meta_model_id);

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

    /**
     * @brief All labels associated with this element.
     */
    /**@{*/
    const std::list<dogen::identification::entities::label>& labels() const;
    std::list<dogen::identification::entities::label>& labels();
    void labels(const std::list<dogen::identification::entities::label>& v);
    void labels(const std::list<dogen::identification::entities::label>&& v);
    /**@}*/

    /**
     * @brief Default postfix for the element.
     */
    /**@{*/
    const std::string& default_postfix() const;
    std::string& default_postfix();
    void default_postfix(const std::string& v);
    void default_postfix(const std::string&& v);
    /**@}*/

    /**
     * @brief Overridden postfix, if any.
     */
    /**@{*/
    const std::string& override_postfix() const;
    std::string& override_postfix();
    void override_postfix(const std::string& v);
    void override_postfix(const std::string&& v);
    /**@}*/

    const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes() const;
    std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes();
    void archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v);
    void archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v);

    /**
     * @brief Maps the logical model element ID to the default archetype for this facet.
     *
     * Used to obtain the default archetype for referencing.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::physical::entities::archetype>& default_archetype_for_logical_meta_model_id() const;
    std::unordered_map<std::string, dogen::physical::entities::archetype>& default_archetype_for_logical_meta_model_id();
    void default_archetype_for_logical_meta_model_id(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v);
    void default_archetype_for_logical_meta_model_id(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v);
    /**@}*/

public:
    bool operator==(const facet& rhs) const;
    bool operator!=(const facet& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(facet& other) noexcept;
    facet& operator=(facet other);

private:
    std::string default_directory_name_;
    std::string override_directory_name_;
    std::string description_;
    dogen::physical::entities::meta_name meta_name_;
    std::list<dogen::identification::entities::label> labels_;
    std::string default_postfix_;
    std::string override_postfix_;
    std::unordered_map<std::string, dogen::physical::entities::archetype> archetypes_;
    std::unordered_map<std::string, dogen::physical::entities::archetype> default_archetype_for_logical_meta_model_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::facet& lhs,
    dogen::physical::entities::facet& rhs) {
    lhs.swap(rhs);
}

}

#endif
