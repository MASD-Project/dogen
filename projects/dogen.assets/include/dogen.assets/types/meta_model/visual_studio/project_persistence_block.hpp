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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VISUAL_STUDIO_PROJECT_PERSISTENCE_BLOCK_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VISUAL_STUDIO_PROJECT_PERSISTENCE_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace dogen::assets::meta_model::visual_studio {

class project_persistence_block final {
public:
    project_persistence_block() = default;
    project_persistence_block(const project_persistence_block&) = default;
    ~project_persistence_block() = default;

public:
    project_persistence_block(project_persistence_block&& rhs);

public:
    project_persistence_block(
        const std::string& guid,
        const std::string& name,
        const boost::filesystem::path& relative_path,
        const std::string& type_guid);

public:
    /**
     * @brief GUID that uniquely identifies this element.
     */
    /**@{*/
    const std::string& guid() const;
    std::string& guid();
    void guid(const std::string& v);
    void guid(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the project.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Relative path to the project file.
     */
    /**@{*/
    const boost::filesystem::path& relative_path() const;
    boost::filesystem::path& relative_path();
    void relative_path(const boost::filesystem::path& v);
    void relative_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief GUID used by Visual Studio to identify projects of this type.
     */
    /**@{*/
    const std::string& type_guid() const;
    std::string& type_guid();
    void type_guid(const std::string& v);
    void type_guid(const std::string&& v);
    /**@}*/

public:
    bool operator==(const project_persistence_block& rhs) const;
    bool operator!=(const project_persistence_block& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(project_persistence_block& other) noexcept;
    project_persistence_block& operator=(project_persistence_block other);

private:
    std::string guid_;
    std::string name_;
    boost::filesystem::path relative_path_;
    std::string type_guid_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::visual_studio::project_persistence_block& lhs,
    dogen::assets::meta_model::visual_studio::project_persistence_block& rhs) {
    lhs.swap(rhs);
}

}

#endif
