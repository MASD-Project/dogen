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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_VALUE_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_VALUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.logical/types/helpers/mapping_actions.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Value of a mapping.
 */
class mapping_value final {
public:
    mapping_value(const mapping_value&) = default;
    ~mapping_value() = default;

public:
    mapping_value();

public:
    mapping_value(mapping_value&& rhs);

public:
    mapping_value(
        const dogen::logical::helpers::mapping_actions mapping_action,
        const boost::optional<dogen::identification::entities::logical_name>& default_name);

public:
    dogen::logical::helpers::mapping_actions mapping_action() const;
    void mapping_action(const dogen::logical::helpers::mapping_actions v);

    const boost::optional<dogen::identification::entities::logical_name>& default_name() const;
    boost::optional<dogen::identification::entities::logical_name>& default_name();
    void default_name(const boost::optional<dogen::identification::entities::logical_name>& v);
    void default_name(const boost::optional<dogen::identification::entities::logical_name>&& v);

public:
    bool operator==(const mapping_value& rhs) const;
    bool operator!=(const mapping_value& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(mapping_value& other) noexcept;
    mapping_value& operator=(mapping_value other);

private:
    dogen::logical::helpers::mapping_actions mapping_action_;
    boost::optional<dogen::identification::entities::logical_name> default_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::helpers::mapping_value& lhs,
    dogen::logical::helpers::mapping_value& rhs) {
    lhs.swap(rhs);
}

}

#endif
