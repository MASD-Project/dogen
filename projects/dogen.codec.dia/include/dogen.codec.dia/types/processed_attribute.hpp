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
#ifndef DOGEN_CODEC_DIA_TYPES_PROCESSED_ATTRIBUTE_HPP
#define DOGEN_CODEC_DIA_TYPES_PROCESSED_ATTRIBUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.codec.dia/types/processed_comment.hpp"

namespace dogen::codec::dia {

class processed_attribute final {
public:
    processed_attribute() = default;
    processed_attribute(const processed_attribute&) = default;
    processed_attribute(processed_attribute&&) = default;
    ~processed_attribute() = default;

public:
    processed_attribute(
        const std::string& name,
        const std::string& type,
        const dogen::codec::dia::processed_comment& comment,
        const std::string& value);

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
    const dogen::codec::dia::processed_comment& comment() const;
    dogen::codec::dia::processed_comment& comment();
    void comment(const dogen::codec::dia::processed_comment& v);
    void comment(const dogen::codec::dia::processed_comment&& v);
    /**@}*/

    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);

public:
    bool operator==(const processed_attribute& rhs) const;
    bool operator!=(const processed_attribute& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(processed_attribute& other) noexcept;
    processed_attribute& operator=(processed_attribute other);

private:
    std::string name_;
    std::string type_;
    dogen::codec::dia::processed_comment comment_;
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::codec::dia::processed_attribute& lhs,
    dogen::codec::dia::processed_attribute& rhs) {
    lhs.swap(rhs);
}

}

#endif
