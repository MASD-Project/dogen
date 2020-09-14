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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.identification/types/entities/physical_meta_name.hpp"

namespace dogen::physical::entities {

/**
 * @brief Properties related to the archetype.
 */
class archetype_properties final {
public:
    archetype_properties(const archetype_properties&) = default;
    ~archetype_properties() = default;

public:
    archetype_properties();

public:
    archetype_properties(archetype_properties&& rhs);

public:
    archetype_properties(
        const dogen::identification::entities::physical_meta_name& meta_name,
        const bool enabled,
        const boost::optional<bool>& overwrite,
        const std::string& postfix);

public:
    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::identification::entities::physical_meta_name& meta_name() const;
    dogen::identification::entities::physical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::physical_meta_name& v);
    void meta_name(const dogen::identification::entities::physical_meta_name&& v);
    /**@}*/

    /**
     * @brief If true, the archetype is enabled.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    /**
     * @brief If true, all artefacts for this archetype will be set to overwrite.
     */
    /**@{*/
    const boost::optional<bool>& overwrite() const;
    boost::optional<bool>& overwrite();
    void overwrite(const boost::optional<bool>& v);
    void overwrite(const boost::optional<bool>&& v);
    /**@}*/

    /**
     * @brief Postfix to apply to all artefacts of this archetype.
     */
    /**@{*/
    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);
    /**@}*/

public:
    bool operator==(const archetype_properties& rhs) const;
    bool operator!=(const archetype_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_properties& other) noexcept;
    archetype_properties& operator=(archetype_properties other);

private:
    dogen::identification::entities::physical_meta_name meta_name_;
    bool enabled_;
    boost::optional<bool> overwrite_;
    std::string postfix_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::archetype_properties& lhs,
    dogen::physical::entities::archetype_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
