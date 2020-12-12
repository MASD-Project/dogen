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
#ifndef DOGEN_DIA_TYPES_ENTITIES_CHILD_NODE_HPP
#define DOGEN_DIA_TYPES_ENTITIES_CHILD_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::dia::entities {

/**
 * @brief Represents a child_node in a diagram.
 *
 * Child nodes are used in Dia to represent the relationship between a package and the entities it contains.
 * For example, if class O1 is inside package O0 then class O1 will have a child node element with a parent
 * pointing to O0.
 */
class child_node final {
public:
    child_node() = default;
    child_node(const child_node&) = default;
    child_node(child_node&&) = default;
    ~child_node() = default;

public:
    explicit child_node(const std::string& parent);

public:
    /**
     * @brief Parent for this object.
     */
    /**@{*/
    const std::string& parent() const;
    std::string& parent();
    void parent(const std::string& v);
    void parent(const std::string&& v);
    /**@}*/

public:
    bool operator==(const child_node& rhs) const;
    bool operator!=(const child_node& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(child_node& other) noexcept;
    child_node& operator=(child_node other);

private:
    std::string parent_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::child_node& lhs,
    dogen::dia::entities::child_node& rhs) {
    lhs.swap(rhs);
}

}

#endif
