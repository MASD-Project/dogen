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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_BUILD_VISUAL_STUDIO_ITEM_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_BUILD_VISUAL_STUDIO_ITEM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::assets::meta_model::build {

/**
 * @brief Represents an MSBuild Item, used in Visual Studio projects.
 *
 * Documentation:  Contains a user-defined item and its metadata. Every item that is
 * used in a MSBuild project must be specified as a child of an ItemGroup element.
 */
class visual_studio_item final {
public:
    visual_studio_item() = default;
    visual_studio_item(const visual_studio_item&) = default;
    visual_studio_item(visual_studio_item&&) = default;
    ~visual_studio_item() = default;

public:
    visual_studio_item(
        const std::string& name,
        const std::string& include);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& include() const;
    std::string& include();
    void include(const std::string& v);
    void include(const std::string&& v);

public:
    bool operator==(const visual_studio_item& rhs) const;
    bool operator!=(const visual_studio_item& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(visual_studio_item& other) noexcept;
    visual_studio_item& operator=(visual_studio_item other);

private:
    std::string name_;
    std::string include_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::build::visual_studio_item& lhs,
    dogen::assets::meta_model::build::visual_studio_item& rhs) {
    lhs.swap(rhs);
}

}

#endif
