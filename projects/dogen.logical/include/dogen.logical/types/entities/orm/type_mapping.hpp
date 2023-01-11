/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_ORM_TYPE_MAPPING_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_ORM_TYPE_MAPPING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/orm/database_system.hpp"
#include "dogen.logical/serialization/entities/orm/type_mapping_fwd_ser.hpp"

namespace dogen::logical::entities::orm {

class type_mapping final {
public:
    type_mapping() = default;
    type_mapping(const type_mapping&) = default;
    ~type_mapping() = default;

public:
    type_mapping(type_mapping&& rhs);

public:
    type_mapping(
        const std::string& source_type,
        const std::string& destination_type,
        const std::string& to_source_type,
        const std::string& to_destination_type,
        const boost::optional<dogen::logical::entities::orm::database_system>& database);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::logical::entities::orm::type_mapping& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::logical::entities::orm::type_mapping& v, unsigned int version);

public:
    /**
     * @brief Type which we intend to map from. Example: TEXT.
     */
    /**@{*/
    const std::string& source_type() const;
    std::string& source_type();
    void source_type(const std::string& v);
    void source_type(const std::string&& v);
    /**@}*/

    /**
     * @brief Type we intend to map to. Example: JSONB.
     */
    /**@{*/
    const std::string& destination_type() const;
    std::string& destination_type();
    void destination_type(const std::string& v);
    void destination_type(const std::string&& v);
    /**@}*/

    /**
     * @brief Function that converts into the source type.
     */
    /**@{*/
    const std::string& to_source_type() const;
    std::string& to_source_type();
    void to_source_type(const std::string& v);
    void to_source_type(const std::string&& v);
    /**@}*/

    /**
     * @brief Function that converts into the destination type.
     */
    /**@{*/
    const std::string& to_destination_type() const;
    std::string& to_destination_type();
    void to_destination_type(const std::string& v);
    void to_destination_type(const std::string&& v);
    /**@}*/

    /**
     * @brief Database to which the mapping applies. If none is supplied, it will apply to all.
     */
    /**@{*/
    const boost::optional<dogen::logical::entities::orm::database_system>& database() const;
    boost::optional<dogen::logical::entities::orm::database_system>& database();
    void database(const boost::optional<dogen::logical::entities::orm::database_system>& v);
    void database(const boost::optional<dogen::logical::entities::orm::database_system>&& v);
    /**@}*/

public:
    bool operator==(const type_mapping& rhs) const;
    bool operator!=(const type_mapping& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_mapping& other) noexcept;
    type_mapping& operator=(type_mapping other);

private:
    std::string source_type_;
    std::string destination_type_;
    std::string to_source_type_;
    std::string to_destination_type_;
    boost::optional<dogen::logical::entities::orm::database_system> database_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::orm::type_mapping& lhs,
    dogen::logical::entities::orm::type_mapping& rhs) {
    lhs.swap(rhs);
}

}

#endif
