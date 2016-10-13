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
#ifndef DOGEN_ANNOTATIONS_TYPES_OWNERSHIP_HIERARCHY_REPOSITORY_HPP
#define DOGEN_ANNOTATIONS_TYPES_OWNERSHIP_HIERARCHY_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen/annotations/types/ownership_hierarchy.hpp"
#include "dogen/annotations/serialization/ownership_hierarchy_repository_fwd_ser.hpp"

namespace dogen {
namespace annotations {

class ownership_hierarchy_repository final {
public:
    ownership_hierarchy_repository() = default;
    ownership_hierarchy_repository(const ownership_hierarchy_repository&) = default;
    ownership_hierarchy_repository(ownership_hierarchy_repository&&) = default;
    ~ownership_hierarchy_repository() = default;

public:
    ownership_hierarchy_repository(
        const std::vector<dogen::annotations::ownership_hierarchy>& ownership_hierarchies,
        const std::unordered_map<std::string, std::unordered_set<std::string> >& facet_names_by_model_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::ownership_hierarchy_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::ownership_hierarchy_repository& v, unsigned int version);

public:
    const std::vector<dogen::annotations::ownership_hierarchy>& ownership_hierarchies() const;
    std::vector<dogen::annotations::ownership_hierarchy>& ownership_hierarchies();
    void ownership_hierarchies(const std::vector<dogen::annotations::ownership_hierarchy>& v);
    void ownership_hierarchies(const std::vector<dogen::annotations::ownership_hierarchy>&& v);

    const std::unordered_map<std::string, std::unordered_set<std::string> >& facet_names_by_model_name() const;
    std::unordered_map<std::string, std::unordered_set<std::string> >& facet_names_by_model_name();
    void facet_names_by_model_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v);
    void facet_names_by_model_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v);

public:
    bool operator==(const ownership_hierarchy_repository& rhs) const;
    bool operator!=(const ownership_hierarchy_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(ownership_hierarchy_repository& other) noexcept;
    ownership_hierarchy_repository& operator=(ownership_hierarchy_repository other);

private:
    std::vector<dogen::annotations::ownership_hierarchy> ownership_hierarchies_;
    std::unordered_map<std::string, std::unordered_set<std::string> > facet_names_by_model_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::ownership_hierarchy_repository& lhs,
    dogen::annotations::ownership_hierarchy_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
