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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VISUAL_STUDIO_PROJECT_REFERENCE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VISUAL_STUDIO_PROJECT_REFERENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace dogen::assets::meta_model::visual_studio {

class project_reference final {
public:
    project_reference() = default;
    project_reference(const project_reference&) = default;
    ~project_reference() = default;

public:
    project_reference(project_reference&& rhs);

public:
    project_reference(
        const std::string& guid,
        const std::string& name,
        const boost::filesystem::path& relative_path);

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

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const boost::filesystem::path& relative_path() const;
    boost::filesystem::path& relative_path();
    void relative_path(const boost::filesystem::path& v);
    void relative_path(const boost::filesystem::path&& v);

public:
    bool operator==(const project_reference& rhs) const;
    bool operator!=(const project_reference& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(project_reference& other) noexcept;
    project_reference& operator=(project_reference other);

private:
    std::string guid_;
    std::string name_;
    boost::filesystem::path relative_path_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::visual_studio::project_reference& lhs,
    dogen::assets::meta_model::visual_studio::project_reference& rhs) {
    lhs.swap(rhs);
}

}

#endif
