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
#include "dogen.dia/types/entities/layer.hpp"

namespace dogen::dia::entities {

layer::layer()
    : visible_(static_cast<bool>(0)),
      active_(static_cast<bool>(0)) { }

layer::layer(
    const std::string& name,
    const bool visible,
    const bool active,
    const std::vector<dogen::dia::entities::object>& objects)
    : name_(name),
      visible_(visible),
      active_(active),
      objects_(objects) { }

void layer::swap(layer& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(visible_, other.visible_);
    swap(active_, other.active_);
    swap(objects_, other.objects_);
}

bool layer::operator==(const layer& rhs) const {
    return name_ == rhs.name_ &&
        visible_ == rhs.visible_ &&
        active_ == rhs.active_ &&
        objects_ == rhs.objects_;
}

layer& layer::operator=(layer other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& layer::name() const {
    return name_;
}

std::string& layer::name() {
    return name_;
}

void layer::name(const std::string& v) {
    name_ = v;
}

void layer::name(const std::string&& v) {
    name_ = std::move(v);
}

bool layer::visible() const {
    return visible_;
}

void layer::visible(const bool v) {
    visible_ = v;
}

bool layer::active() const {
    return active_;
}

void layer::active(const bool v) {
    active_ = v;
}

const std::vector<dogen::dia::entities::object>& layer::objects() const {
    return objects_;
}

std::vector<dogen::dia::entities::object>& layer::objects() {
    return objects_;
}

void layer::objects(const std::vector<dogen::dia::entities::object>& v) {
    objects_ = v;
}

void layer::objects(const std::vector<dogen::dia::entities::object>&& v) {
    objects_ = std::move(v);
}

}
