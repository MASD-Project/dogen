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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_LOGICAL_LOCATION_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_LOGICAL_LOCATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>

namespace dogen::physical::entities {

/**
 * @brief Represents a point in logical space.
 */
class logical_location final {
public:
    logical_location() = default;
    logical_location(const logical_location&) = default;
    logical_location(logical_location&&) = default;
    ~logical_location() = default;

public:
    logical_location(
        const std::string& simple_name,
        const std::string& qualified_name,
        const std::list<std::string>& external_modules,
        const std::list<std::string>& model_modules,
        const std::list<std::string>& internal_modules);

public:
    const std::string& simple_name() const;
    std::string& simple_name();
    void simple_name(const std::string& v);
    void simple_name(const std::string&& v);

    const std::string& qualified_name() const;
    std::string& qualified_name();
    void qualified_name(const std::string& v);
    void qualified_name(const std::string&& v);

    const std::list<std::string>& external_modules() const;
    std::list<std::string>& external_modules();
    void external_modules(const std::list<std::string>& v);
    void external_modules(const std::list<std::string>&& v);

    const std::list<std::string>& model_modules() const;
    std::list<std::string>& model_modules();
    void model_modules(const std::list<std::string>& v);
    void model_modules(const std::list<std::string>&& v);

    const std::list<std::string>& internal_modules() const;
    std::list<std::string>& internal_modules();
    void internal_modules(const std::list<std::string>& v);
    void internal_modules(const std::list<std::string>&& v);

public:
    bool operator==(const logical_location& rhs) const;
    bool operator!=(const logical_location& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_location& other) noexcept;
    logical_location& operator=(logical_location other);

private:
    std::string simple_name_;
    std::string qualified_name_;
    std::list<std::string> external_modules_;
    std::list<std::string> model_modules_;
    std::list<std::string> internal_modules_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::logical_location& lhs,
    dogen::physical::entities::logical_location& rhs) {
    lhs.swap(rhs);
}

}

#endif
