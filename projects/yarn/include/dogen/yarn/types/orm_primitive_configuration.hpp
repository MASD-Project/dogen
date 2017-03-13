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
#ifndef DOGEN_YARN_TYPES_ORM_PRIMITIVE_CONFIGURATION_HPP
#define DOGEN_YARN_TYPES_ORM_PRIMITIVE_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn/types/letter_cases.hpp"
#include "dogen/yarn/serialization/orm_primitive_configuration_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class orm_primitive_configuration final {
public:
    orm_primitive_configuration(const orm_primitive_configuration&) = default;
    ~orm_primitive_configuration() = default;

public:
    orm_primitive_configuration();

public:
    orm_primitive_configuration(orm_primitive_configuration&& rhs);

public:
    orm_primitive_configuration(
        const bool generate_mapping,
        const std::string& schema_name,
        const boost::optional<dogen::yarn::letter_cases>& letter_case);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::orm_primitive_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::orm_primitive_configuration& v, unsigned int version);

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
     * @brief What case to use for the database identifiers.
     */
    /**@{*/
    const boost::optional<dogen::yarn::letter_cases>& letter_case() const;
    boost::optional<dogen::yarn::letter_cases>& letter_case();
    void letter_case(const boost::optional<dogen::yarn::letter_cases>& v);
    void letter_case(const boost::optional<dogen::yarn::letter_cases>&& v);
    /**@}*/

public:
    bool operator==(const orm_primitive_configuration& rhs) const;
    bool operator!=(const orm_primitive_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(orm_primitive_configuration& other) noexcept;
    orm_primitive_configuration& operator=(orm_primitive_configuration other);

private:
    bool generate_mapping_;
    std::string schema_name_;
    boost::optional<dogen::yarn::letter_cases> letter_case_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::orm_primitive_configuration& lhs,
    dogen::yarn::orm_primitive_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
