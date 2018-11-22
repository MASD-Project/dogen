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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_ORM_OBJECT_PROPERTIES_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_ORM_OBJECT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "masd.dogen.coding/types/meta_model/letter_cases.hpp"

namespace masd::dogen::coding::meta_model {

class orm_object_properties final {
public:
    orm_object_properties(const orm_object_properties&) = default;
    ~orm_object_properties() = default;

public:
    orm_object_properties();

public:
    orm_object_properties(orm_object_properties&& rhs);

public:
    orm_object_properties(
        const bool generate_mapping,
        const std::string& schema_name,
        const std::string& table_name,
        const bool is_value,
        const bool has_primary_key,
        const boost::optional<masd::dogen::coding::meta_model::letter_cases>& letter_case);

public:
    /**
     * @brief If true, object-relational mapping will be generated for this element.
     */
    /**@{*/
    bool generate_mapping() const;
    void generate_mapping(const bool v);
    /**@}*/

    /**
     * @brief Name of the database schema in which to place this element.
     */
    /**@{*/
    const std::string& schema_name() const;
    std::string& schema_name();
    void schema_name(const std::string& v);
    void schema_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the table to map this element to.
     */
    /**@{*/
    const std::string& table_name() const;
    std::string& table_name();
    void table_name(const std::string& v);
    void table_name(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, treat this object as a value type (e.g. simple type) rather than as an object.
     */
    /**@{*/
    bool is_value() const;
    void is_value(const bool v);
    /**@}*/

    /**
     * @brief True if the object has an attribute marked as a primary key, false otherwise.
     */
    /**@{*/
    bool has_primary_key() const;
    void has_primary_key(const bool v);
    /**@}*/

    /**
     * @brief What case to use for the database identifiers.
     */
    /**@{*/
    const boost::optional<masd::dogen::coding::meta_model::letter_cases>& letter_case() const;
    boost::optional<masd::dogen::coding::meta_model::letter_cases>& letter_case();
    void letter_case(const boost::optional<masd::dogen::coding::meta_model::letter_cases>& v);
    void letter_case(const boost::optional<masd::dogen::coding::meta_model::letter_cases>&& v);
    /**@}*/

public:
    bool operator==(const orm_object_properties& rhs) const;
    bool operator!=(const orm_object_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(orm_object_properties& other) noexcept;
    orm_object_properties& operator=(orm_object_properties other);

private:
    bool generate_mapping_;
    std::string schema_name_;
    std::string table_name_;
    bool is_value_;
    bool has_primary_key_;
    boost::optional<masd::dogen::coding::meta_model::letter_cases> letter_case_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::orm_object_properties& lhs,
    masd::dogen::coding::meta_model::orm_object_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
