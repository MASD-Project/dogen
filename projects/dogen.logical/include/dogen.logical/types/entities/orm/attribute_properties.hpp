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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_ORM_ATTRIBUTE_PROPERTIES_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_ORM_ATTRIBUTE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/orm/database_system.hpp"
#include "dogen.logical/hash/entities/orm/database_system_hash.hpp"

namespace dogen::logical::entities::orm {

class attribute_properties final {
public:
    attribute_properties(const attribute_properties&) = default;
    ~attribute_properties() = default;

public:
    attribute_properties();

public:
    attribute_properties(attribute_properties&& rhs);

public:
    attribute_properties(
        const std::unordered_map<dogen::logical::entities::orm::database_system, std::string>& type_overrides,
        const std::list<std::string>& odb_pragmas,
        const std::string& column_name,
        const bool is_primary_key,
        const boost::optional<bool>& is_nullable,
        const bool is_composite);

public:
    /**
     * @brief Override the default type for this attribute for a given database system.
     */
    /**@{*/
    const std::unordered_map<dogen::logical::entities::orm::database_system, std::string>& type_overrides() const;
    std::unordered_map<dogen::logical::entities::orm::database_system, std::string>& type_overrides();
    void type_overrides(const std::unordered_map<dogen::logical::entities::orm::database_system, std::string>& v);
    void type_overrides(const std::unordered_map<dogen::logical::entities::orm::database_system, std::string>&& v);
    /**@}*/

    /**
     * @brief Pragmas for the ODB ORM backend.
     */
    /**@{*/
    const std::list<std::string>& odb_pragmas() const;
    std::list<std::string>& odb_pragmas();
    void odb_pragmas(const std::list<std::string>& v);
    void odb_pragmas(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Name of the column to use for this attribute. If populated, will override the attribute name.
     */
    /**@{*/
    const std::string& column_name() const;
    std::string& column_name();
    void column_name(const std::string& v);
    void column_name(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, this attribute is a primary key for the relation.
     */
    /**@{*/
    bool is_primary_key() const;
    void is_primary_key(const bool v);
    /**@}*/

    /**
     * @brief If true, the attribute can be NULL.
     */
    /**@{*/
    const boost::optional<bool>& is_nullable() const;
    boost::optional<bool>& is_nullable();
    void is_nullable(const boost::optional<bool>& v);
    void is_nullable(const boost::optional<bool>&& v);
    /**@}*/

    /**
     * @brief If true, the value of this attribute is a composite value.
     */
    /**@{*/
    bool is_composite() const;
    void is_composite(const bool v);
    /**@}*/

public:
    bool operator==(const attribute_properties& rhs) const;
    bool operator!=(const attribute_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(attribute_properties& other) noexcept;
    attribute_properties& operator=(attribute_properties other);

private:
    std::unordered_map<dogen::logical::entities::orm::database_system, std::string> type_overrides_;
    std::list<std::string> odb_pragmas_;
    std::string column_name_;
    bool is_primary_key_;
    boost::optional<bool> is_nullable_;
    bool is_composite_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::orm::attribute_properties& lhs,
    dogen::logical::entities::orm::attribute_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
