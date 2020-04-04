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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.physical/types/entities/location.hpp"
#include "dogen.physical/types/entities/meta_name.hpp"

namespace dogen::physical::entities {

class archetype final {
public:
    archetype() = default;
    archetype(const archetype&) = default;
    archetype(archetype&&) = default;
    ~archetype() = default;

public:
    archetype(
        const dogen::physical::entities::location& location,
        const std::string& description,
        const dogen::physical::entities::meta_name& meta_name,
        const std::string& default_postfix,
        const std::string& override_postfix,
        const std::string& archetype_kind_id,
        const std::string& meta_element_id,
        const std::string& part);

public:
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

    const std::string& archetype_kind_id() const;
    std::string& archetype_kind_id();
    void archetype_kind_id(const std::string& v);
    void archetype_kind_id(const std::string&& v);

    /**
     * @brief Which types of the logical model this archetype supports.
     */
    /**@{*/
    const std::string& meta_element_id() const;
    std::string& meta_element_id();
    void meta_element_id(const std::string& v);
    void meta_element_id(const std::string&& v);
    /**@}*/

    /**
     * @brief Part in which we are located.
     */
    /**@{*/
    const std::string& part() const;
    std::string& part();
    void part(const std::string& v);
    void part(const std::string&& v);
    /**@}*/

public:
    bool operator==(const archetype& rhs) const;
    bool operator!=(const archetype& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype& other) noexcept;
    archetype& operator=(archetype other);

private:
    dogen::physical::entities::location location_;
    std::string description_;
    dogen::physical::entities::meta_name meta_name_;
    std::string default_postfix_;
    std::string override_postfix_;
    std::string archetype_kind_id_;
    std::string meta_element_id_;
    std::string part_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::archetype& lhs,
    dogen::physical::entities::archetype& rhs) {
    lhs.swap(rhs);
}

}

#endif
