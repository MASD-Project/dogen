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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_ORM_OBJECT_PROPERTIES_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_ORM_OBJECT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/orm/letter_case.hpp"
#include "dogen.logical/types/entities/orm/odb_options.hpp"
#include "dogen.logical/types/entities/orm/type_mapping.hpp"

namespace dogen::logical::entities::orm {

class object_properties final {
public:
    object_properties(const object_properties&) = default;
    ~object_properties() = default;

public:
    object_properties();

public:
    object_properties(object_properties&& rhs);

public:
    object_properties(
        const dogen::logical::entities::orm::odb_options& odb_options,
        const std::string& schema_name,
        const std::string& capitalised_schema_name,
        const boost::optional<dogen::logical::entities::orm::letter_case>& letter_case,
        const bool generate_mapping,
        const std::list<dogen::logical::entities::orm::type_mapping>& type_mappings,
        const std::list<std::string>& odb_pragmas,
        const std::string& table_name,
        const bool is_value,
        const bool has_primary_key);

public:
    const dogen::logical::entities::orm::odb_options& odb_options() const;
    dogen::logical::entities::orm::odb_options& odb_options();
    void odb_options(const dogen::logical::entities::orm::odb_options& v);
    void odb_options(const dogen::logical::entities::orm::odb_options&& v);

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
     * @brief Schema name with the correct capitalisation.
     */
    /**@{*/
    const std::string& capitalised_schema_name() const;
    std::string& capitalised_schema_name();
    void capitalised_schema_name(const std::string& v);
    void capitalised_schema_name(const std::string&& v);
    /**@}*/

    /**
     * @brief What case to use for the database identifiers.
     */
    /**@{*/
    const boost::optional<dogen::logical::entities::orm::letter_case>& letter_case() const;
    boost::optional<dogen::logical::entities::orm::letter_case>& letter_case();
    void letter_case(const boost::optional<dogen::logical::entities::orm::letter_case>& v);
    void letter_case(const boost::optional<dogen::logical::entities::orm::letter_case>&& v);
    /**@}*/

    /**
     * @brief If true, object-relational mapping will be generated for this element.
     */
    /**@{*/
    bool generate_mapping() const;
    void generate_mapping(const bool v);
    /**@}*/

    /**
     * @brief List of mappings of relational database types.
     */
    /**@{*/
    const std::list<dogen::logical::entities::orm::type_mapping>& type_mappings() const;
    std::list<dogen::logical::entities::orm::type_mapping>& type_mappings();
    void type_mappings(const std::list<dogen::logical::entities::orm::type_mapping>& v);
    void type_mappings(const std::list<dogen::logical::entities::orm::type_mapping>&& v);
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

public:
    bool operator==(const object_properties& rhs) const;
    bool operator!=(const object_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(object_properties& other) noexcept;
    object_properties& operator=(object_properties other);

private:
    dogen::logical::entities::orm::odb_options odb_options_;
    std::string schema_name_;
    std::string capitalised_schema_name_;
    boost::optional<dogen::logical::entities::orm::letter_case> letter_case_;
    bool generate_mapping_;
    std::list<dogen::logical::entities::orm::type_mapping> type_mappings_;
    std::list<std::string> odb_pragmas_;
    std::string table_name_;
    bool is_value_;
    bool has_primary_key_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::orm::object_properties& lhs,
    dogen::logical::entities::orm::object_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
