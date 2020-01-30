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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_BUILD_VISUAL_STUDIO_ITEM_GROUP_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_BUILD_VISUAL_STUDIO_ITEM_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.assets/types/meta_model/build/visual_studio_item.hpp"

namespace dogen::assets::meta_model::build {

/**
 * @brief Represents an MSBuild ItemGroup.
 *
 * Documented as follows: Contains a set of user-defined Item elements. Every item
 * used in a MSBuild project must be specified as a child of an ItemGroup element.
 */
class visual_studio_item_group final {
public:
    visual_studio_item_group() = default;
    visual_studio_item_group(const visual_studio_item_group&) = default;
    visual_studio_item_group(visual_studio_item_group&&) = default;
    ~visual_studio_item_group() = default;

public:
    explicit visual_studio_item_group(const std::list<dogen::assets::meta_model::build::visual_studio_item>& items);

public:
    /**
     * @brief Set of MSBuild Items that make up this ItemGroup.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::build::visual_studio_item>& items() const;
    std::list<dogen::assets::meta_model::build::visual_studio_item>& items();
    void items(const std::list<dogen::assets::meta_model::build::visual_studio_item>& v);
    void items(const std::list<dogen::assets::meta_model::build::visual_studio_item>&& v);
    /**@}*/

public:
    bool operator==(const visual_studio_item_group& rhs) const;
    bool operator!=(const visual_studio_item_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(visual_studio_item_group& other) noexcept;
    visual_studio_item_group& operator=(visual_studio_item_group other);

private:
    std::list<dogen::assets::meta_model::build::visual_studio_item> items_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::build::visual_studio_item_group& lhs,
    dogen::assets::meta_model::build::visual_studio_item_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
