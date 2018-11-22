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
#include "masd.dogen.extraction/types/modeline_group.hpp"

namespace masd::dogen::extraction {

modeline_group::modeline_group(
    const std::string& name,
    const std::unordered_map<std::string, masd::dogen::extraction::modeline>& modelines)
    : name_(name),
      modelines_(modelines) { }

void modeline_group::swap(modeline_group& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(modelines_, other.modelines_);
}

bool modeline_group::operator==(const modeline_group& rhs) const {
    return name_ == rhs.name_ &&
        modelines_ == rhs.modelines_;
}

modeline_group& modeline_group::operator=(modeline_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& modeline_group::name() const {
    return name_;
}

std::string& modeline_group::name() {
    return name_;
}

void modeline_group::name(const std::string& v) {
    name_ = v;
}

void modeline_group::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::extraction::modeline>& modeline_group::modelines() const {
    return modelines_;
}

std::unordered_map<std::string, masd::dogen::extraction::modeline>& modeline_group::modelines() {
    return modelines_;
}

void modeline_group::modelines(const std::unordered_map<std::string, masd::dogen::extraction::modeline>& v) {
    modelines_ = v;
}

void modeline_group::modelines(const std::unordered_map<std::string, masd::dogen::extraction::modeline>&& v) {
    modelines_ = std::move(v);
}

}
