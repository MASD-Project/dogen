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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_LOCATION_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_LOCATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>

namespace dogen::logical::meta_model {

/**
 * @brief Identifies a hierarchy of containment within the asset space.
 *
 * Elements exist at unique points within the asset space called @e
 * addresses.  However, certain elements have the ability to contain
 * other elements, creating in effect new dimensions in assets space. The
 * location class keeps track of these dimensions. Note that the
 * attributes of this class are hierarchical, i.e.  external modules
 * contain model modules and so forth. These attributes are best thought
 * of as a single linked list, where segments of that linked list have
 * different meaning. However, because we care about these meanings, we
 * implemented the type with a number of linked lists, one per meaning.
 *
 * A location is not necessarily connected to modules, although these are
 * the main model elements that provide containment. For example, inner
 * classes are contained within classes; in assets terms it means a
 * location should also have an "object" attribute to represent this
 * relationship.
 *
 * Also, note that the location class itself encodes the address of the
 * element that owns that location; returning to the linked list idea,
 * the tail of the linked list is the name of the element, and the
 * remaining linked list provides the location of the element.
 */
class location final {
public:
    location() = default;
    location(const location&) = default;
    location(location&&) = default;
    ~location() = default;

public:
    location(
        const std::list<std::string>& external_modules,
        const std::list<std::string>& model_modules,
        const std::list<std::string>& internal_modules,
        const std::string& element);

public:
    /**
     * @brief All modules external to the model itself.
     *
     * It is sometimes useful to create a model within a set of existing
     * modules. In this case, the model does not own the existing modules and
     * they are considered "external" to the model. This is useful, for
     * example, when declaring a model within a larger project such as @e
     * dogen::logical. In this case, @e dogen is the external module.
     */
    /**@{*/
    const std::list<std::string>& external_modules() const;
    std::list<std::string>& external_modules();
    void external_modules(const std::list<std::string>& v);
    void external_modules(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Modules related to just the model itself.
     *
     * It is only different from the model name if the model name is composite;
     * that is, if the model name has multiple fields separated by dots, e.g. @ a.b.
     */
    /**@{*/
    const std::list<std::string>& model_modules() const;
    std::list<std::string>& model_modules();
    void model_modules(const std::list<std::string>& v);
    void model_modules(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Sub-modules within a model.
     */
    /**@{*/
    const std::list<std::string>& internal_modules() const;
    std::list<std::string>& internal_modules();
    void internal_modules(const std::list<std::string>& v);
    void internal_modules(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Name of the owning element, if any.
     *
     * For coding elements which are located within other assets elements
     * that are not modules, such as attributes, inner classes, etc.
     */
    /**@{*/
    const std::string& element() const;
    std::string& element();
    void element(const std::string& v);
    void element(const std::string&& v);
    /**@}*/

public:
    bool operator==(const location& rhs) const;
    bool operator!=(const location& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(location& other) noexcept;
    location& operator=(location other);

private:
    std::list<std::string> external_modules_;
    std::list<std::string> model_modules_;
    std::list<std::string> internal_modules_;
    std::string element_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::meta_model::location& lhs,
    dogen::logical::meta_model::location& rhs) {
    lhs.swap(rhs);
}

}

#endif
