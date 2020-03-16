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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ELEMENT_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/paths.hpp"

namespace dogen::physical::entities {

/**
 * @brief Represents an entity which we would like to place in physical space.
 */
class element final {
public:
    element() = default;
    element(const element&) = default;
    element(element&&) = default;
    ~element() = default;

public:
    element(
        const std::string& simple_name,
        const std::string& qualified_name,
        const std::list<std::string>& external_modules,
        const std::list<std::string>& model_modules,
        const std::list<std::string>& internal_modules,
        const std::unordered_map<std::string, dogen::physical::entities::paths>& paths);

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

    const std::unordered_map<std::string, dogen::physical::entities::paths>& paths() const;
    std::unordered_map<std::string, dogen::physical::entities::paths>& paths();
    void paths(const std::unordered_map<std::string, dogen::physical::entities::paths>& v);
    void paths(const std::unordered_map<std::string, dogen::physical::entities::paths>&& v);

public:
    bool operator==(const element& rhs) const;
    bool operator!=(const element& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element& other) noexcept;
    element& operator=(element other);

private:
    std::string simple_name_;
    std::string qualified_name_;
    std::list<std::string> external_modules_;
    std::list<std::string> model_modules_;
    std::list<std::string> internal_modules_;
    std::unordered_map<std::string, dogen::physical::entities::paths> paths_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::element& lhs,
    dogen::physical::entities::element& rhs) {
    lhs.swap(rhs);
}

}

#endif
