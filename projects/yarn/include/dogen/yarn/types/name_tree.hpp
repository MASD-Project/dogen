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
#ifndef DOGEN_YARN_TYPES_NAME_TREE_HPP
#define DOGEN_YARN_TYPES_NAME_TREE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/serialization/name_tree_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Adds support for name composition as a tree-like structure.
 *
 * A name tree has the responsibility of representing an instantiation of a generic
 * type with all of its type parameters, which themselves can also be generic types
 * and so on. It may also represent the simpler case of a non-generic type, in which
 * case only the parent name is populated and there are no children.
 */
class name_tree final {
public:
    name_tree(const name_tree&) = default;
    name_tree(name_tree&&) = default;
    ~name_tree() = default;

public:
    name_tree();

public:
    name_tree(
        const dogen::yarn::name& parent,
        const std::list<dogen::yarn::name_tree>& children,
        const bool are_children_opaque,
        const bool is_circular_dependency,
        const std::string& encoded,
        const std::string& identifiable);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const name_tree& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, name_tree& v, unsigned int version);

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
    const std::list<dogen::yarn::name_tree>& children() const;
    std::list<dogen::yarn::name_tree>& children();
    void children(const std::list<dogen::yarn::name_tree>& v);
    void children(const std::list<dogen::yarn::name_tree>&& v);
    /**@}*/

    /**
     * @brief If true, the association with its children can be opaque.
     *
     * Children are considered opaque when the parent does not require knowledge
     * about the childs' internal structure. This is the case, for example, with C and
     * C++ pointers, references and so on.
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

    /**
     * @brief Textual representaion of the name tree and its children, using a dogen grammar.
     */
    /**@{*/
    const std::string& encoded() const;
    std::string& encoded();
    void encoded(const std::string& v);
    void encoded(const std::string&& v);
    /**@}*/

    /**
     * @brief Representation of the named tree that can usable as an identifier across all
     * supported languages.
     */
    /**@{*/
    const std::string& identifiable() const;
    std::string& identifiable();
    void identifiable(const std::string& v);
    void identifiable(const std::string&& v);
    /**@}*/

public:
    bool operator==(const name_tree& rhs) const;
    bool operator!=(const name_tree& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(name_tree& other) noexcept;
    name_tree& operator=(name_tree other);

private:
    dogen::yarn::name parent_;
    std::list<dogen::yarn::name_tree> children_;
    bool are_children_opaque_;
    bool is_circular_dependency_;
    std::string encoded_;
    std::string identifiable_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::name_tree& lhs,
    dogen::yarn::name_tree& rhs) {
    lhs.swap(rhs);
}

}

#endif
