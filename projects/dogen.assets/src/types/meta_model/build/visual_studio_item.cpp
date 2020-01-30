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
#include "dogen.assets/types/meta_model/build/visual_studio_item.hpp"

namespace dogen::assets::meta_model::build {

visual_studio_item::visual_studio_item(
    const std::string& name,
    const std::string& include)
    : name_(name),
      include_(include) { }

void visual_studio_item::swap(visual_studio_item& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(include_, other.include_);
}

bool visual_studio_item::operator==(const visual_studio_item& rhs) const {
    return name_ == rhs.name_ &&
        include_ == rhs.include_;
}

visual_studio_item& visual_studio_item::operator=(visual_studio_item other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& visual_studio_item::name() const {
    return name_;
}

std::string& visual_studio_item::name() {
    return name_;
}

void visual_studio_item::name(const std::string& v) {
    name_ = v;
}

void visual_studio_item::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& visual_studio_item::include() const {
    return include_;
}

std::string& visual_studio_item::include() {
    return include_;
}

void visual_studio_item::include(const std::string& v) {
    include_ = v;
}

void visual_studio_item::include(const std::string&& v) {
    include_ = std::move(v);
}

}
