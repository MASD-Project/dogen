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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_ORM_PRIMITIVE_PROPERTIES_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_ORM_PRIMITIVE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen.logical/types/meta_model/orm/letter_case.hpp"
#include "dogen.logical/types/meta_model/orm/odb_options.hpp"
#include "dogen.logical/types/meta_model/orm/type_mapping.hpp"
#include "dogen.logical/types/meta_model/orm/database_system.hpp"
#include "dogen.logical/hash/meta_model/orm/database_system_hash.hpp"

namespace dogen::logical::meta_model::orm {

class primitive_properties final {
public:
    primitive_properties(const primitive_properties&) = default;
    ~primitive_properties() = default;

public:
    primitive_properties();

public:
    primitive_properties(primitive_properties&& rhs);

public:
    primitive_properties(
        const dogen::logical::meta_model::orm::odb_options& odb_options,
        const std::string& schema_name,
        const std::string& capitalised_schema_name,
        const boost::optional<dogen::logical::meta_model::orm::letter_case>& letter_case,
        const bool generate_mapping,
        const std::list<dogen::logical::meta_model::orm::type_mapping>& type_mappings,
        const std::list<std::string>& odb_pragmas,
        const std::unordered_map<dogen::logical::meta_model::orm::database_system, std::string>& type_overrides);

public:
    const dogen::logical::meta_model::orm::odb_options& odb_options() const;
    dogen::logical::meta_model::orm::odb_options& odb_options();
    void odb_options(const dogen::logical::meta_model::orm::odb_options& v);
    void odb_options(const dogen::logical::meta_model::orm::odb_options&& v);

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
    const boost::optional<dogen::logical::meta_model::orm::letter_case>& letter_case() const;
    boost::optional<dogen::logical::meta_model::orm::letter_case>& letter_case();
    void letter_case(const boost::optional<dogen::logical::meta_model::orm::letter_case>& v);
    void letter_case(const boost::optional<dogen::logical::meta_model::orm::letter_case>&& v);
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
    const std::list<dogen::logical::meta_model::orm::type_mapping>& type_mappings() const;
    std::list<dogen::logical::meta_model::orm::type_mapping>& type_mappings();
    void type_mappings(const std::list<dogen::logical::meta_model::orm::type_mapping>& v);
    void type_mappings(const std::list<dogen::logical::meta_model::orm::type_mapping>&& v);
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
     * @brief Override the default type for this attribute for a given database system.
     */
    /**@{*/
    const std::unordered_map<dogen::logical::meta_model::orm::database_system, std::string>& type_overrides() const;
    std::unordered_map<dogen::logical::meta_model::orm::database_system, std::string>& type_overrides();
    void type_overrides(const std::unordered_map<dogen::logical::meta_model::orm::database_system, std::string>& v);
    void type_overrides(const std::unordered_map<dogen::logical::meta_model::orm::database_system, std::string>&& v);
    /**@}*/

public:
    bool operator==(const primitive_properties& rhs) const;
    bool operator!=(const primitive_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(primitive_properties& other) noexcept;
    primitive_properties& operator=(primitive_properties other);

private:
    dogen::logical::meta_model::orm::odb_options odb_options_;
    std::string schema_name_;
    std::string capitalised_schema_name_;
    boost::optional<dogen::logical::meta_model::orm::letter_case> letter_case_;
    bool generate_mapping_;
    std::list<dogen::logical::meta_model::orm::type_mapping> type_mappings_;
    std::list<std::string> odb_pragmas_;
    std::unordered_map<dogen::logical::meta_model::orm::database_system, std::string> type_overrides_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::meta_model::orm::primitive_properties& lhs,
    dogen::logical::meta_model::orm::primitive_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
