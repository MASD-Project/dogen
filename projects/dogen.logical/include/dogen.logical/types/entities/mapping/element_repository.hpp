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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_MAPPING_ELEMENT_REPOSITORY_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_MAPPING_ELEMENT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/mapping/fixed_mappable_fwd.hpp"
#include "dogen.logical/types/entities/mapping/extensible_mappable_fwd.hpp"

namespace dogen::logical::entities::mapping {

class element_repository final {
public:
    element_repository() = default;
    element_repository(const element_repository&) = default;
    element_repository(element_repository&&) = default;
    ~element_repository() = default;

public:
    element_repository(
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable> >& extensible_mappables,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable> >& fixed_mappables);

public:
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable> >& extensible_mappables() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable> >& extensible_mappables();
    void extensible_mappables(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable> >& v);
    void extensible_mappables(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable> >& fixed_mappables() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable> >& fixed_mappables();
    void fixed_mappables(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable> >& v);
    void fixed_mappables(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable> >&& v);

public:
    bool operator==(const element_repository& rhs) const;
    bool operator!=(const element_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_repository& other) noexcept;
    element_repository& operator=(element_repository other);

private:
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable> > extensible_mappables_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable> > fixed_mappables_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::mapping::element_repository& lhs,
    dogen::logical::entities::mapping::element_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
