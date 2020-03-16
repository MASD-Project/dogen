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
#ifndef DOGEN_GENERATION_TYPES_ENTITIES_INTRA_BACKEND_SEGMENT_PROPERTIES_HPP
#define DOGEN_GENERATION_TYPES_ENTITIES_INTRA_BACKEND_SEGMENT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen.generation/types/entities/path_contribution_types.hpp"

namespace dogen::generation::entities {

class intra_backend_segment_properties final {
public:
    intra_backend_segment_properties(const intra_backend_segment_properties&) = default;
    ~intra_backend_segment_properties() = default;

public:
    intra_backend_segment_properties();

public:
    intra_backend_segment_properties(intra_backend_segment_properties&& rhs);

public:
    intra_backend_segment_properties(
        const boost::filesystem::path& override_parent_path,
        const boost::filesystem::path& path_segment,
        const dogen::generation::entities::path_contribution_types external_modules,
        const dogen::generation::entities::path_contribution_types model_modules,
        const dogen::generation::entities::path_contribution_types internal_modules,
        const dogen::generation::entities::path_contribution_types facet);

public:
    /**
     * @brief If supplied, this path is used as the parent path instead of the output path.
     *
     * This is useful for example when you want to place the include files outside of the
     * model directory.
     */
    /**@{*/
    const boost::filesystem::path& override_parent_path() const;
    boost::filesystem::path& override_parent_path();
    void override_parent_path(const boost::filesystem::path& v);
    void override_parent_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Path segment to use for this intra-backend segment.
     */
    /**@{*/
    const boost::filesystem::path& path_segment() const;
    boost::filesystem::path& path_segment();
    void path_segment(const boost::filesystem::path& v);
    void path_segment(const boost::filesystem::path&& v);
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

    /**
     * @brief What kind of contribution do the internal modules make to the final path.
     */
    /**@{*/
    dogen::generation::entities::path_contribution_types internal_modules() const;
    void internal_modules(const dogen::generation::entities::path_contribution_types v);
    /**@}*/

    /**
     * @brief What kind of contribution does the facet make to the final path.
     */
    /**@{*/
    dogen::generation::entities::path_contribution_types facet() const;
    void facet(const dogen::generation::entities::path_contribution_types v);
    /**@}*/

public:
    bool operator==(const intra_backend_segment_properties& rhs) const;
    bool operator!=(const intra_backend_segment_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(intra_backend_segment_properties& other) noexcept;
    intra_backend_segment_properties& operator=(intra_backend_segment_properties other);

private:
    boost::filesystem::path override_parent_path_;
    boost::filesystem::path path_segment_;
    dogen::generation::entities::path_contribution_types external_modules_;
    dogen::generation::entities::path_contribution_types model_modules_;
    dogen::generation::entities::path_contribution_types internal_modules_;
    dogen::generation::entities::path_contribution_types facet_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::entities::intra_backend_segment_properties& lhs,
    dogen::generation::entities::intra_backend_segment_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
