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
#ifndef DOGEN_YARN_TYPES_META_MODEL_NAME_TREE_HPP
#define DOGEN_YARN_TYPES_META_MODEL_NAME_TREE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <map>
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/languages.hpp"
#include "dogen/yarn/types/meta_model/name_tree.hpp"
#include "dogen/yarn/hash/meta_model/languages_hash.hpp"
#include "dogen/yarn/serialization/meta_model/name_tree_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

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
        const dogen::yarn::meta_model::name& current,
        const std::list<dogen::yarn::meta_model::name_tree>& children,
        const bool are_children_opaque,
        const bool is_circular_dependency,
        const std::map<dogen::yarn::meta_model::languages, std::string>& qualified,
        const std::string& identifiable,
        const bool is_current_simple_type,
        const bool is_floating_point);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::name_tree& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::name_tree& v, unsigned int version);

public:
    /**
     * @brief Name for the current level of the tree.
     */
    /**@{*/
    const dogen::yarn::meta_model::name& current() const;
    dogen::yarn::meta_model::name& current();
    void current(const dogen::yarn::meta_model::name& v);
    void current(const dogen::yarn::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Names of the child elements.
     */
    /**@{*/
    const std::list<dogen::yarn::meta_model::name_tree>& children() const;
    std::list<dogen::yarn::meta_model::name_tree>& children();
    void children(const std::list<dogen::yarn::meta_model::name_tree>& v);
    void children(const std::list<dogen::yarn::meta_model::name_tree>&& v);
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
     * @brief If true, the presence of the current name causes a circular dependency.
     */
    /**@{*/
    bool is_circular_dependency() const;
    void is_circular_dependency(const bool v);
    /**@}*/

    /**
     * @brief Qualified name in a language specific representation.
     */
    /**@{*/
    const std::map<dogen::yarn::meta_model::languages, std::string>& qualified() const;
    std::map<dogen::yarn::meta_model::languages, std::string>& qualified();
    void qualified(const std::map<dogen::yarn::meta_model::languages, std::string>& v);
    void qualified(const std::map<dogen::yarn::meta_model::languages, std::string>&& v);
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

    /**
     * @brief Returns true if @e current is a simple type such as a built-in or an enumeration.
     */
    /**@{*/
    bool is_current_simple_type() const;
    void is_current_simple_type(const bool v);
    /**@}*/

    /**
     * @brief If true, "current" stores a floating point type.
     */
    /**@{*/
    bool is_floating_point() const;
    void is_floating_point(const bool v);
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
    dogen::yarn::meta_model::name current_;
    std::list<dogen::yarn::meta_model::name_tree> children_;
    bool are_children_opaque_;
    bool is_circular_dependency_;
    std::map<dogen::yarn::meta_model::languages, std::string> qualified_;
    std::string identifiable_;
    bool is_current_simple_type_;
    bool is_floating_point_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::name_tree& lhs,
    dogen::yarn::meta_model::name_tree& rhs) {
    lhs.swap(rhs);
}

}

#endif
