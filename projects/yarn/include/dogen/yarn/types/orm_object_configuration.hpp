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
#ifndef DOGEN_YARN_TYPES_ORM_OBJECT_CONFIGURATION_HPP
#define DOGEN_YARN_TYPES_ORM_OBJECT_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn/types/letter_cases.hpp"
#include "dogen/yarn/serialization/orm_object_configuration_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class orm_object_configuration final {
public:
    orm_object_configuration(const orm_object_configuration&) = default;
    ~orm_object_configuration() = default;

public:
    orm_object_configuration();

public:
    orm_object_configuration(orm_object_configuration&& rhs);

public:
    orm_object_configuration(
        const bool generate_mapping,
        const std::string& schema_name,
        const std::string& table_name,
        const bool is_value,
        const bool has_primary_key,
        const boost::optional<dogen::yarn::letter_cases>& letter_case);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::orm_object_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::orm_object_configuration& v, unsigned int version);

public:
    /**
     * @brief If true, object-relational mapping will be generated for this element.
     */
    /**@{*/
    bool generate_mapping() const;
    void generate_mapping(const bool v);
    /**@}*/

    const std::string& schema_name() const;
    std::string& schema_name();
    void schema_name(const std::string& v);
    void schema_name(const std::string&& v);

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

    const boost::optional<dogen::yarn::letter_cases>& letter_case() const;
    boost::optional<dogen::yarn::letter_cases>& letter_case();
    void letter_case(const boost::optional<dogen::yarn::letter_cases>& v);
    void letter_case(const boost::optional<dogen::yarn::letter_cases>&& v);

public:
    bool operator==(const orm_object_configuration& rhs) const;
    bool operator!=(const orm_object_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(orm_object_configuration& other) noexcept;
    orm_object_configuration& operator=(orm_object_configuration other);

private:
    bool generate_mapping_;
    std::string schema_name_;
    std::string table_name_;
    bool is_value_;
    bool has_primary_key_;
    boost::optional<dogen::yarn::letter_cases> letter_case_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::orm_object_configuration& lhs,
    dogen::yarn::orm_object_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
