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
#ifndef DOGEN_UPSILON_TYPES_TYPE_NAME_HPP
#define DOGEN_UPSILON_TYPES_TYPE_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/upsilon/serialization/type_name_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class type_name final {
public:
    type_name() = default;
    type_name(const type_name&) = default;
    type_name(type_name&&) = default;
    ~type_name() = default;

public:
    type_name(
        const std::string& name,
        const std::string& schema_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::type_name& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::type_name& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& schema_name() const;
    std::string& schema_name();
    void schema_name(const std::string& v);
    void schema_name(const std::string&& v);

public:
    bool operator==(const type_name& rhs) const;
    bool operator!=(const type_name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_name& other) noexcept;
    type_name& operator=(type_name other);

private:
    std::string name_;
    std::string schema_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::type_name& lhs,
    dogen::upsilon::type_name& rhs) {
    lhs.swap(rhs);
}

}

#endif
