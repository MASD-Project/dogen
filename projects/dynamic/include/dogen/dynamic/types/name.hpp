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
#ifndef DOGEN_DYNAMIC_TYPES_NAME_HPP
#define DOGEN_DYNAMIC_TYPES_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/dynamic/serialization/name_fwd_ser.hpp"

namespace dogen {
namespace dynamic {

class name final {
public:
    name() = default;
    name(const name&) = default;
    name(name&&) = default;
    ~name() = default;

public:
    name(
        const std::string& simple_name,
        const std::string& owner,
        const std::string& complete_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const name& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, name& v, unsigned int version);

public:
    const std::string& simple_name() const;
    std::string& simple_name();
    void simple_name(const std::string& v);
    void simple_name(const std::string&& v);

    const std::string& owner() const;
    std::string& owner();
    void owner(const std::string& v);
    void owner(const std::string&& v);

    const std::string& complete_name() const;
    std::string& complete_name();
    void complete_name(const std::string& v);
    void complete_name(const std::string&& v);

public:
    bool operator==(const name& rhs) const;
    bool operator!=(const name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(name& other) noexcept;
    name& operator=(name other);

private:
    std::string simple_name_;
    std::string owner_;
    std::string complete_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dynamic::name& lhs,
    dogen::dynamic::name& rhs) {
    lhs.swap(rhs);
}

}

#endif
