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
#include "dogen.engine/types/helpers/stereotypes_conversion_result.hpp"

namespace dogen::engine::helpers {

stereotypes_conversion_result::stereotypes_conversion_result(
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes)
    : static_stereotypes_(static_stereotypes),
      dynamic_stereotypes_(dynamic_stereotypes) { }

void stereotypes_conversion_result::swap(stereotypes_conversion_result& other) noexcept {
    using std::swap;
    swap(static_stereotypes_, other.static_stereotypes_);
    swap(dynamic_stereotypes_, other.dynamic_stereotypes_);
}

bool stereotypes_conversion_result::operator==(const stereotypes_conversion_result& rhs) const {
    return static_stereotypes_ == rhs.static_stereotypes_ &&
        dynamic_stereotypes_ == rhs.dynamic_stereotypes_;
}

stereotypes_conversion_result& stereotypes_conversion_result::operator=(stereotypes_conversion_result other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::logical::entities::static_stereotypes>& stereotypes_conversion_result::static_stereotypes() const {
    return static_stereotypes_;
}

std::list<dogen::logical::entities::static_stereotypes>& stereotypes_conversion_result::static_stereotypes() {
    return static_stereotypes_;
}

void stereotypes_conversion_result::static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>& v) {
    static_stereotypes_ = v;
}

void stereotypes_conversion_result::static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>&& v) {
    static_stereotypes_ = std::move(v);
}

const std::list<std::string>& stereotypes_conversion_result::dynamic_stereotypes() const {
    return dynamic_stereotypes_;
}

std::list<std::string>& stereotypes_conversion_result::dynamic_stereotypes() {
    return dynamic_stereotypes_;
}

void stereotypes_conversion_result::dynamic_stereotypes(const std::list<std::string>& v) {
    dynamic_stereotypes_ = v;
}

void stereotypes_conversion_result::dynamic_stereotypes(const std::list<std::string>&& v) {
    dynamic_stereotypes_ = std::move(v);
}

}
