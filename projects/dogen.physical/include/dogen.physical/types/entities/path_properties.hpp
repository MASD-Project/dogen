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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_PATH_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_PATH_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"

namespace dogen::physical::entities {

class path_properties final {
public:
    path_properties() = default;
    path_properties(const path_properties&) = default;
    ~path_properties() = default;

public:
    path_properties(path_properties&& rhs);

public:
    path_properties(
        const boost::filesystem::path& file_path,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::filesystem::path>& relative_paths);

public:
    /**
     * @brief Full path to the file corresponding to this artefact.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Paths relative to the part's root directory.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::filesystem::path>& relative_paths() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, boost::filesystem::path>& relative_paths();
    void relative_paths(const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::filesystem::path>& v);
    void relative_paths(const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::filesystem::path>&& v);
    /**@}*/

public:
    bool operator==(const path_properties& rhs) const;
    bool operator!=(const path_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_properties& other) noexcept;
    path_properties& operator=(path_properties other);

private:
    boost::filesystem::path file_path_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, boost::filesystem::path> relative_paths_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::path_properties& lhs,
    dogen::physical::entities::path_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
