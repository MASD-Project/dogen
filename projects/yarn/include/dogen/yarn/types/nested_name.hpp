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
#ifndef DOGEN_YARN_TYPES_NESTED_NAME_HPP
#define DOGEN_YARN_TYPES_NESTED_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/nested_name.hpp"
#include "dogen/yarn/serialization/nested_name_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Adds support for name composition.
 *
 * A nested name has the responsibility of representing an instantiation of a generic
 * type with all of its type parameters, which themselves can also be generic types
 * and so on. It may also represent the simpler case of a non-generic type, in which
 * case only the parent name is populated and there are no children.
 *
 * Note that we avoid the name "composite name" here to avoid confusion with the
 * composite pattern.
 */
class nested_name final {
public:
    nested_name(const nested_name&) = default;
    nested_name(nested_name&&) = default;
    ~nested_name() = default;

public:
    nested_name();

public:
    nested_name(
        const dogen::yarn::name& parent,
        const std::list<dogen::yarn::nested_name>& children,
        const bool are_children_opaque,
        const bool is_circular_dependency);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const nested_name& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, nested_name& v, unsigned int version);

public:
    /**
     * @brief Name of the top-level, containing element.
     */
    /**@{*/
    const dogen::yarn::name& parent() const;
    dogen::yarn::name& parent();
    void parent(const dogen::yarn::name& v);
    void parent(const dogen::yarn::name&& v);
    /**@}*/

    /**
     * @brief Names of the child elements.
     */
    /**@{*/
    const std::list<dogen::yarn::nested_name>& children() const;
    std::list<dogen::yarn::nested_name>& children();
    void children(const std::list<dogen::yarn::nested_name>& v);
    void children(const std::list<dogen::yarn::nested_name>&& v);
    /**@}*/

    /**
     * @brief If true, the association with its children can be opaque.
     */
    /**@{*/
    bool are_children_opaque() const;
    void are_children_opaque(const bool v);
    /**@}*/

    /**
     * @brief If true, the presence of parent name causes a circular dependency.
     */
    /**@{*/
    bool is_circular_dependency() const;
    void is_circular_dependency(const bool v);
    /**@}*/

public:
    bool operator==(const nested_name& rhs) const;
    bool operator!=(const nested_name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(nested_name& other) noexcept;
    nested_name& operator=(nested_name other);

private:
    dogen::yarn::name parent_;
    std::list<dogen::yarn::nested_name> children_;
    bool are_children_opaque_;
    bool is_circular_dependency_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::nested_name& lhs,
    dogen::yarn::nested_name& rhs) {
    lhs.swap(rhs);
}

}

#endif
