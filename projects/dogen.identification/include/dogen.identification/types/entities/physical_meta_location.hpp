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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_PHYSICAL_META_LOCATION_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_PHYSICAL_META_LOCATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::identification::entities {

/**
 * @brief Location of an entity or set of entities in the physical meta-model.
 *
 * These must be populated in order, e.g. in order to have a backend we must have a
 * meta-model; in order to have a facet we must have a backend and in order to have
 * a formatter we must have a facet. We may not have any.
 */
class physical_meta_location final {
public:
    physical_meta_location() = default;
    physical_meta_location(const physical_meta_location&) = default;
    physical_meta_location(physical_meta_location&&) = default;
    ~physical_meta_location() = default;

public:
    physical_meta_location(
        const std::string& meta_model,
        const std::string& backend,
        const std::string& part,
        const std::string& facet,
        const std::string& archetype);

public:
    /**
     * @brief Top-most container for the physical space.
     *
     * The meta-model is always expected to be  @e masd.
     */
    /**@{*/
    const std::string& meta_model() const;
    std::string& meta_model();
    void meta_model(const std::string& v);
    void meta_model(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the backend where this element is located, if any.
     */
    /**@{*/
    const std::string& backend() const;
    std::string& backend();
    void backend(const std::string& v);
    void backend(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the part where this element is located, if any.
     */
    /**@{*/
    const std::string& part() const;
    std::string& part();
    void part(const std::string& v);
    void part(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the facet where this element is located, if any.
     */
    /**@{*/
    const std::string& facet() const;
    std::string& facet();
    void facet(const std::string& v);
    void facet(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the archetype for this element, if applicable.
     */
    /**@{*/
    const std::string& archetype() const;
    std::string& archetype();
    void archetype(const std::string& v);
    void archetype(const std::string&& v);
    /**@}*/

public:
    bool operator==(const physical_meta_location& rhs) const;
    bool operator!=(const physical_meta_location& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(physical_meta_location& other) noexcept;
    physical_meta_location& operator=(physical_meta_location other);

private:
    std::string meta_model_;
    std::string backend_;
    std::string part_;
    std::string facet_;
    std::string archetype_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::physical_meta_location& lhs,
    dogen::identification::entities::physical_meta_location& rhs) {
    lhs.swap(rhs);
}

}

#endif
