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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_MANUAL_ASSOCIATIONS_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_MANUAL_ASSOCIATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.identification/types/entities/logical_name.hpp"

namespace dogen::logical::entities {

/**
 * @brief Stores the set of associations between this element and other elements of this
 * model. These have been added manually to the model.
 */
class manual_associations final {
public:
    manual_associations() = default;
    manual_associations(const manual_associations&) = default;
    manual_associations(manual_associations&&) = default;
    ~manual_associations() = default;

public:
    manual_associations(
        const std::list<dogen::identification::entities::logical_name>& aggregation,
        const std::list<dogen::identification::entities::logical_name>& composition,
        const std::list<dogen::identification::entities::logical_name>& association);

public:
    /**
     * @brief Represents a part-to-whole relationship between elements.
     */
    /**@{*/
    const std::list<dogen::identification::entities::logical_name>& aggregation() const;
    std::list<dogen::identification::entities::logical_name>& aggregation();
    void aggregation(const std::list<dogen::identification::entities::logical_name>& v);
    void aggregation(const std::list<dogen::identification::entities::logical_name>&& v);
    /**@}*/

    /**
     * @brief Represents a part-to-whole relationship between elements.
     */
    /**@{*/
    const std::list<dogen::identification::entities::logical_name>& composition() const;
    std::list<dogen::identification::entities::logical_name>& composition();
    void composition(const std::list<dogen::identification::entities::logical_name>& v);
    void composition(const std::list<dogen::identification::entities::logical_name>&& v);
    /**@}*/

    /**
     * @brief Binary relationship between two elements.
     */
    /**@{*/
    const std::list<dogen::identification::entities::logical_name>& association() const;
    std::list<dogen::identification::entities::logical_name>& association();
    void association(const std::list<dogen::identification::entities::logical_name>& v);
    void association(const std::list<dogen::identification::entities::logical_name>&& v);
    /**@}*/

public:
    bool operator==(const manual_associations& rhs) const;
    bool operator!=(const manual_associations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(manual_associations& other) noexcept;
    manual_associations& operator=(manual_associations other);

private:
    std::list<dogen::identification::entities::logical_name> aggregation_;
    std::list<dogen::identification::entities::logical_name> composition_;
    std::list<dogen::identification::entities::logical_name> association_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::manual_associations& lhs,
    dogen::logical::entities::manual_associations& rhs) {
    lhs.swap(rhs);
}

}

#endif
