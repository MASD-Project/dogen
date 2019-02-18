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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_ORM_ATTRIBUTE_PROPERTIES_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_ORM_ATTRIBUTE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "masd.dogen.coding/types/meta_model/orm_database_systems.hpp"
#include "masd.dogen.coding/hash/meta_model/orm_database_systems_hash.hpp"

namespace masd::dogen::coding::meta_model {

class orm_attribute_properties final {
public:
    orm_attribute_properties(const orm_attribute_properties&) = default;
    ~orm_attribute_properties() = default;

public:
    orm_attribute_properties();

public:
    orm_attribute_properties(orm_attribute_properties&& rhs);

public:
    orm_attribute_properties(
        const std::string& column_name,
        const bool is_primary_key,
        const boost::optional<bool>& is_nullable,
        const std::unordered_map<masd::dogen::coding::meta_model::orm_database_systems, std::string>& type_overrides,
        const bool is_composite);

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
    const boost::optional<bool>& is_nullable() const;
    boost::optional<bool>& is_nullable();
    void is_nullable(const boost::optional<bool>& v);
    void is_nullable(const boost::optional<bool>&& v);
    /**@}*/

    /**
     * @brief Override the default type for this attribute for a given database system.
     */
    /**@{*/
    const std::unordered_map<masd::dogen::coding::meta_model::orm_database_systems, std::string>& type_overrides() const;
    std::unordered_map<masd::dogen::coding::meta_model::orm_database_systems, std::string>& type_overrides();
    void type_overrides(const std::unordered_map<masd::dogen::coding::meta_model::orm_database_systems, std::string>& v);
    void type_overrides(const std::unordered_map<masd::dogen::coding::meta_model::orm_database_systems, std::string>&& v);
    /**@}*/

    /**
     * @brief If true, the value of this attribute is a composite value.
     */
    /**@{*/
    bool is_composite() const;
    void is_composite(const bool v);
    /**@}*/

public:
    bool operator==(const orm_attribute_properties& rhs) const;
    bool operator!=(const orm_attribute_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(orm_attribute_properties& other) noexcept;
    orm_attribute_properties& operator=(orm_attribute_properties other);

private:
    std::string column_name_;
    bool is_primary_key_;
    boost::optional<bool> is_nullable_;
    std::unordered_map<masd::dogen::coding::meta_model::orm_database_systems, std::string> type_overrides_;
    bool is_composite_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::orm_attribute_properties& lhs,
    masd::dogen::coding::meta_model::orm_attribute_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
