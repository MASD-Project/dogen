/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_ENUMERATOR_INFO_HPP
#define DOGEN_CPP_TYPES_ENUMERATOR_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/cpp/serialization/enumerator_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents a member of an enumeration.
 */
class enumerator_info final {
public:
    enumerator_info() = default;
    enumerator_info(const enumerator_info&) = default;
    enumerator_info(enumerator_info&&) = default;
    ~enumerator_info() = default;

public:
    enumerator_info(
        const std::string& name,
        const std::string& value,
        const std::string& documentation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const enumerator_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, enumerator_info& v, unsigned int version);

public:
    /**
     * @brief Name of the enumeration member.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Numeric value for the member.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

    /**
     * @brief Documentation for the enumerator.
     *
     * Should be very short as it is used inline.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

public:
    bool operator==(const enumerator_info& rhs) const;
    bool operator!=(const enumerator_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(enumerator_info& other) noexcept;
    enumerator_info& operator=(enumerator_info other);

private:
    std::string name_;
    std::string value_;
    std::string documentation_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::enumerator_info& lhs,
    dogen::cpp::enumerator_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
