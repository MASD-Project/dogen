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
#ifndef DOGEN_YARN_DIA_TYPES_PROCESSED_PROPERTY_HPP
#define DOGEN_YARN_DIA_TYPES_PROCESSED_PROPERTY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/yarn_dia/types/processed_comment.hpp"
#include "dogen/yarn_dia/serialization/processed_property_fwd_ser.hpp"

namespace dogen {
namespace yarn_dia {

class processed_property final {
public:
    processed_property() = default;
    processed_property(const processed_property&) = default;
    processed_property(processed_property&&) = default;
    ~processed_property() = default;

public:
    processed_property(
        const std::string& name,
        const std::string& type,
        const dogen::yarn_dia::processed_comment& comment);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const processed_property& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, processed_property& v, unsigned int version);

public:
    /**
     * @brief Name of the property.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Type of the property.
     */
    /**@{*/
    const std::string& type() const;
    std::string& type();
    void type(const std::string& v);
    void type(const std::string&& v);
    /**@}*/

    /**
     * @brief Any comments associated with the property.
     */
    /**@{*/
    const dogen::yarn_dia::processed_comment& comment() const;
    dogen::yarn_dia::processed_comment& comment();
    void comment(const dogen::yarn_dia::processed_comment& v);
    void comment(const dogen::yarn_dia::processed_comment&& v);
    /**@}*/

public:
    bool operator==(const processed_property& rhs) const;
    bool operator!=(const processed_property& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(processed_property& other) noexcept;
    processed_property& operator=(processed_property other);

private:
    std::string name_;
    std::string type_;
    dogen::yarn_dia::processed_comment comment_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn_dia::processed_property& lhs,
    dogen::yarn_dia::processed_property& rhs) {
    lhs.swap(rhs);
}

}

#endif
