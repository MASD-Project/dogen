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
#ifndef DOGEN_YARN_TYPES_ORM_ATTRIBUTE_CONFIGURATION_HPP
#define DOGEN_YARN_TYPES_ORM_ATTRIBUTE_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/orm_database_systems.hpp"
#include "dogen/yarn/hash/orm_database_systems_hash.hpp"
#include "dogen/yarn/serialization/orm_attribute_configuration_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class orm_attribute_configuration final {
public:
    orm_attribute_configuration(const orm_attribute_configuration&) = default;
    orm_attribute_configuration(orm_attribute_configuration&&) = default;
    ~orm_attribute_configuration() = default;

public:
    orm_attribute_configuration();

public:
    orm_attribute_configuration(
        const std::string& column_name,
        const bool is_primary_key,
        const bool is_nullable,
        const std::unordered_map<dogen::yarn::orm_database_systems, std::string>& type_overrides);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::orm_attribute_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::orm_attribute_configuration& v, unsigned int version);

public:
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
    bool is_nullable() const;
    void is_nullable(const bool v);
    /**@}*/

    /**
     * @brief Override the default type for this attribute for a given database system.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::orm_database_systems, std::string>& type_overrides() const;
    std::unordered_map<dogen::yarn::orm_database_systems, std::string>& type_overrides();
    void type_overrides(const std::unordered_map<dogen::yarn::orm_database_systems, std::string>& v);
    void type_overrides(const std::unordered_map<dogen::yarn::orm_database_systems, std::string>&& v);
    /**@}*/

public:
    bool operator==(const orm_attribute_configuration& rhs) const;
    bool operator!=(const orm_attribute_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(orm_attribute_configuration& other) noexcept;
    orm_attribute_configuration& operator=(orm_attribute_configuration other);

private:
    std::string column_name_;
    bool is_primary_key_;
    bool is_nullable_;
    std::unordered_map<dogen::yarn::orm_database_systems, std::string> type_overrides_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::orm_attribute_configuration& lhs,
    dogen::yarn::orm_attribute_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
