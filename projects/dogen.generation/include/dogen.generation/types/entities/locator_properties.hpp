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
#ifndef DOGEN_GENERATION_TYPES_ENTITIES_LOCATOR_PROPERTIES_HPP
#define DOGEN_GENERATION_TYPES_ENTITIES_LOCATOR_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.generation/types/entities/model_segment_properties.hpp"
#include "dogen.generation/types/entities/directory_structure_styles.hpp"
#include "dogen.generation/types/entities/archetype_family_properties.hpp"
#include "dogen.generation/types/entities/intra_backend_segment_properties.hpp"

namespace dogen::generation::entities {

class locator_properties final {
public:
    locator_properties(const locator_properties&) = default;
    locator_properties(locator_properties&&) = default;
    ~locator_properties() = default;

public:
    locator_properties();

public:
    locator_properties(
        const dogen::generation::entities::directory_structure_styles directory_structure_style,
        const std::string& name_separator,
        const dogen::generation::entities::model_segment_properties& model_segment_properties,
        const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& intra_backend_segment_properties,
        const std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>& archetype_family_properties,
        const bool force_backend_directory,
        const bool disable_facet_directories);

public:
    dogen::generation::entities::directory_structure_styles directory_structure_style() const;
    void directory_structure_style(const dogen::generation::entities::directory_structure_styles v);

    /**
     * @brief Separator to use when concatenating sub-components of a path component.
     */
    /**@{*/
    const std::string& name_separator() const;
    std::string& name_separator();
    void name_separator(const std::string& v);
    void name_separator(const std::string&& v);
    /**@}*/

    const dogen::generation::entities::model_segment_properties& model_segment_properties() const;
    dogen::generation::entities::model_segment_properties& model_segment_properties();
    void model_segment_properties(const dogen::generation::entities::model_segment_properties& v);
    void model_segment_properties(const dogen::generation::entities::model_segment_properties&& v);

    const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& intra_backend_segment_properties() const;
    std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& intra_backend_segment_properties();
    void intra_backend_segment_properties(const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& v);
    void intra_backend_segment_properties(const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>&& v);

    const std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>& archetype_family_properties() const;
    std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>& archetype_family_properties();
    void archetype_family_properties(const std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>& v);
    void archetype_family_properties(const std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties>&& v);

    /**
     * @brief If true, the backend directory will be expressed, even when there is only one
     * backend enabled.
     */
    /**@{*/
    bool force_backend_directory() const;
    void force_backend_directory(const bool v);
    /**@}*/

    /**
     * @brief If true, directories for facets are not generated.
     */
    /**@{*/
    bool disable_facet_directories() const;
    void disable_facet_directories(const bool v);
    /**@}*/

public:
    bool operator==(const locator_properties& rhs) const;
    bool operator!=(const locator_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(locator_properties& other) noexcept;
    locator_properties& operator=(locator_properties other);

private:
    dogen::generation::entities::directory_structure_styles directory_structure_style_;
    std::string name_separator_;
    dogen::generation::entities::model_segment_properties model_segment_properties_;
    std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties> intra_backend_segment_properties_;
    std::unordered_map<std::string, dogen::generation::entities::archetype_family_properties> archetype_family_properties_;
    bool force_backend_directory_;
    bool disable_facet_directories_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::entities::locator_properties& lhs,
    dogen::generation::entities::locator_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
