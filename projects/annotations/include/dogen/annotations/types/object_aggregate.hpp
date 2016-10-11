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
#ifndef DOGEN_ANNOTATIONS_TYPES_OBJECT_AGGREGATE_HPP
#define DOGEN_ANNOTATIONS_TYPES_OBJECT_AGGREGATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/annotations/types/object.hpp"
#include "dogen/annotations/serialization/object_aggregate_fwd_ser.hpp"

namespace dogen {
namespace annotations {

class object_aggregate final {
public:
    object_aggregate() = default;
    object_aggregate(const object_aggregate&) = default;
    object_aggregate(object_aggregate&&) = default;
    ~object_aggregate() = default;

public:
    object_aggregate(
        const dogen::annotations::object& element,
        const std::unordered_map<std::string, dogen::annotations::object>& attributes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::object_aggregate& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::object_aggregate& v, unsigned int version);

public:
    const dogen::annotations::object& element() const;
    dogen::annotations::object& element();
    void element(const dogen::annotations::object& v);
    void element(const dogen::annotations::object&& v);

    const std::unordered_map<std::string, dogen::annotations::object>& attributes() const;
    std::unordered_map<std::string, dogen::annotations::object>& attributes();
    void attributes(const std::unordered_map<std::string, dogen::annotations::object>& v);
    void attributes(const std::unordered_map<std::string, dogen::annotations::object>&& v);

public:
    bool operator==(const object_aggregate& rhs) const;
    bool operator!=(const object_aggregate& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(object_aggregate& other) noexcept;
    object_aggregate& operator=(object_aggregate other);

private:
    dogen::annotations::object element_;
    std::unordered_map<std::string, dogen::annotations::object> attributes_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::object_aggregate& lhs,
    dogen::annotations::object_aggregate& rhs) {
    lhs.swap(rhs);
}

}

#endif
