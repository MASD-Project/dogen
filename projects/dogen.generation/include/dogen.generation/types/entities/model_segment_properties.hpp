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
#ifndef DOGEN_GENERATION_TYPES_ENTITIES_MODEL_SEGMENT_PROPERTIES_HPP
#define DOGEN_GENERATION_TYPES_ENTITIES_MODEL_SEGMENT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.generation/types/entities/path_contribution_types.hpp"

namespace dogen::generation::entities {

/**
 * @brief Properties related to the model segment of the path.
 */
class model_segment_properties final {
public:
    model_segment_properties(const model_segment_properties&) = default;
    model_segment_properties(model_segment_properties&&) = default;
    ~model_segment_properties() = default;

public:
    model_segment_properties();

public:
    model_segment_properties(
        const std::string& directory,
        const dogen::generation::entities::path_contribution_types external_modules,
        const dogen::generation::entities::path_contribution_types model_modules);

public:
    /**
     * @brief If supplied, the override directory name will take precedence and all other
     * settings will be ignored.
     *
     * If not supplied the model path segment is computed from the remaining settings.
     */
    /**@{*/
    const std::string& directory() const;
    std::string& directory();
    void directory(const std::string& v);
    void directory(const std::string&& v);
    /**@}*/

    /**
     * @brief What kind of contribution do the external modules make to the final path.
     */
    /**@{*/
    dogen::generation::entities::path_contribution_types external_modules() const;
    void external_modules(const dogen::generation::entities::path_contribution_types v);
    /**@}*/

    /**
     * @brief What kind of contribution do the model modules make to the final path.
     */
    /**@{*/
    dogen::generation::entities::path_contribution_types model_modules() const;
    void model_modules(const dogen::generation::entities::path_contribution_types v);
    /**@}*/

public:
    bool operator==(const model_segment_properties& rhs) const;
    bool operator!=(const model_segment_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model_segment_properties& other) noexcept;
    model_segment_properties& operator=(model_segment_properties other);

private:
    std::string directory_;
    dogen::generation::entities::path_contribution_types external_modules_;
    dogen::generation::entities::path_contribution_types model_modules_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::entities::model_segment_properties& lhs,
    dogen::generation::entities::model_segment_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
