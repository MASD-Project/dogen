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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_ANNOTATION_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_ANNOTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.variability/types/value_fwd.hpp"
#include "masd.dogen.variability/types/scope_types.hpp"

namespace masd::dogen::variability {

/**
 * @brief Represents an annotation that can be associated with an external object.
 */
class annotation final {
public:
    annotation(const annotation&) = default;
    annotation(annotation&&) = default;
    ~annotation() = default;

public:
    annotation();

public:
    annotation(
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::value> >& tagged_values,
        const masd::dogen::variability::scope_types scope);

public:
    /**
     * @brief All tagged values in this annotation. Each entry is a key-value-pair of id and value.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::value> >& tagged_values() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::value> >& tagged_values();
    void tagged_values(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::value> >& v);
    void tagged_values(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::value> >&& v);
    /**@}*/

    masd::dogen::variability::scope_types scope() const;
    void scope(const masd::dogen::variability::scope_types v);

public:
    bool operator==(const annotation& rhs) const;
    bool operator!=(const annotation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(annotation& other) noexcept;
    annotation& operator=(annotation other);

private:
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::value> > tagged_values_;
    masd::dogen::variability::scope_types scope_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::annotation& lhs,
    masd::dogen::variability::annotation& rhs) {
    lhs.swap(rhs);
}

}

#endif
