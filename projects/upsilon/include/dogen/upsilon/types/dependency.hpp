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
#ifndef DOGEN_UPSILON_TYPES_DEPENDENCY_HPP
#define DOGEN_UPSILON_TYPES_DEPENDENCY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/upsilon/serialization/dependency_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class dependency final {
public:
    dependency() = default;
    dependency(const dependency&) = default;
    dependency(dependency&&) = default;
    ~dependency() = default;

public:
    explicit dependency(const std::string& name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::dependency& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::dependency& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

public:
    bool operator==(const dependency& rhs) const;
    bool operator!=(const dependency& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(dependency& other) noexcept;
    dependency& operator=(dependency other);

private:
    std::string name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::dependency& lhs,
    dogen::upsilon::dependency& rhs) {
    lhs.swap(rhs);
}

}

#endif
