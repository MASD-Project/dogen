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
#ifndef DOGEN_YARN_TYPES_INDICES_HPP
#define DOGEN_YARN_TYPES_INDICES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen/annotations/types/raw_aggregate.hpp"
#include "dogen/yarn/serialization/indices_fwd_ser.hpp"

namespace dogen {
namespace yarn {

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
        const std::unordered_map<std::string, dogen::annotations::raw_aggregate>& raw_aggregates);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::indices& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::indices& v, unsigned int version);

public:
    const std::unordered_set<std::string>& objects_always_in_heap() const;
    std::unordered_set<std::string>& objects_always_in_heap();
    void objects_always_in_heap(const std::unordered_set<std::string>& v);
    void objects_always_in_heap(const std::unordered_set<std::string>&& v);

    const std::unordered_set<std::string>& elements_referable_by_attributes() const;
    std::unordered_set<std::string>& elements_referable_by_attributes();
    void elements_referable_by_attributes(const std::unordered_set<std::string>& v);
    void elements_referable_by_attributes(const std::unordered_set<std::string>&& v);

    const std::unordered_map<std::string, dogen::annotations::raw_aggregate>& raw_aggregates() const;
    std::unordered_map<std::string, dogen::annotations::raw_aggregate>& raw_aggregates();
    void raw_aggregates(const std::unordered_map<std::string, dogen::annotations::raw_aggregate>& v);
    void raw_aggregates(const std::unordered_map<std::string, dogen::annotations::raw_aggregate>&& v);

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
    std::unordered_map<std::string, dogen::annotations::raw_aggregate> raw_aggregates_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::indices& lhs,
    dogen::yarn::indices& rhs) {
    lhs.swap(rhs);
}

}

#endif
