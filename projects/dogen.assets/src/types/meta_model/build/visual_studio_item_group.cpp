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
#include "dogen.assets/types/meta_model/build/visual_studio_item_group.hpp"

namespace dogen::assets::meta_model::build {

visual_studio_item_group::visual_studio_item_group(const std::list<dogen::assets::meta_model::build::visual_studio_item>& items)
    : items_(items) { }

void visual_studio_item_group::swap(visual_studio_item_group& other) noexcept {
    using std::swap;
    swap(items_, other.items_);
}

bool visual_studio_item_group::operator==(const visual_studio_item_group& rhs) const {
    return items_ == rhs.items_;
}

visual_studio_item_group& visual_studio_item_group::operator=(visual_studio_item_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::assets::meta_model::build::visual_studio_item>& visual_studio_item_group::items() const {
    return items_;
}

std::list<dogen::assets::meta_model::build::visual_studio_item>& visual_studio_item_group::items() {
    return items_;
}

void visual_studio_item_group::items(const std::list<dogen::assets::meta_model::build::visual_studio_item>& v) {
    items_ = v;
}

void visual_studio_item_group::items(const std::list<dogen::assets::meta_model::build::visual_studio_item>&& v) {
    items_ = std::move(v);
}

}
