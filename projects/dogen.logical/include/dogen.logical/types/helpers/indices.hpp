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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_INDICES_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_INDICES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_set>

namespace dogen::logical::helpers {

class indices final {
public:
    indices() = default;
    indices(const indices&) = default;
    indices(indices&&) = default;
    ~indices() = default;

public:
    indices(
        const std::unordered_set<std::string>& objects_always_in_heap,
        const std::unordered_set<std::string>& elements_referable_by_attributes,
        const std::unordered_set<std::string>& primitive_underliers,
        const std::unordered_set<std::string>& enumeration_underliers,
        const std::unordered_set<std::string>& abstract_elements);

public:
    const std::unordered_set<std::string>& objects_always_in_heap() const;
    std::unordered_set<std::string>& objects_always_in_heap();
    void objects_always_in_heap(const std::unordered_set<std::string>& v);
    void objects_always_in_heap(const std::unordered_set<std::string>&& v);

    const std::unordered_set<std::string>& elements_referable_by_attributes() const;
    std::unordered_set<std::string>& elements_referable_by_attributes();
    void elements_referable_by_attributes(const std::unordered_set<std::string>& v);
    void elements_referable_by_attributes(const std::unordered_set<std::string>&& v);

    const std::unordered_set<std::string>& primitive_underliers() const;
    std::unordered_set<std::string>& primitive_underliers();
    void primitive_underliers(const std::unordered_set<std::string>& v);
    void primitive_underliers(const std::unordered_set<std::string>&& v);

    const std::unordered_set<std::string>& enumeration_underliers() const;
    std::unordered_set<std::string>& enumeration_underliers();
    void enumeration_underliers(const std::unordered_set<std::string>& v);
    void enumeration_underliers(const std::unordered_set<std::string>&& v);

    const std::unordered_set<std::string>& abstract_elements() const;
    std::unordered_set<std::string>& abstract_elements();
    void abstract_elements(const std::unordered_set<std::string>& v);
    void abstract_elements(const std::unordered_set<std::string>&& v);

public:
    bool operator==(const indices& rhs) const;
    bool operator!=(const indices& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(indices& other) noexcept;
    indices& operator=(indices other);

private:
    std::unordered_set<std::string> objects_always_in_heap_;
    std::unordered_set<std::string> elements_referable_by_attributes_;
    std::unordered_set<std::string> primitive_underliers_;
    std::unordered_set<std::string> enumeration_underliers_;
    std::unordered_set<std::string> abstract_elements_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::helpers::indices& lhs,
    dogen::logical::helpers::indices& rhs) {
    lhs.swap(rhs);
}

}

#endif
