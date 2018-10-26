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
#include "masd.dogen/types/archive.hpp"

namespace masd::dogen {

archive::archive()
    : type_(static_cast<masd::dogen::archive_type>(0)) { }

archive::archive(
    const std::string& content,
    const masd::dogen::archive_type type)
    : content_(content),
      type_(type) { }

void archive::swap(archive& other) noexcept {
    using std::swap;
    swap(content_, other.content_);
    swap(type_, other.type_);
}

bool archive::operator==(const archive& rhs) const {
    return content_ == rhs.content_ &&
        type_ == rhs.type_;
}

archive& archive::operator=(archive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& archive::content() const {
    return content_;
}

std::string& archive::content() {
    return content_;
}

void archive::content(const std::string& v) {
    content_ = v;
}

void archive::content(const std::string&& v) {
    content_ = std::move(v);
}

masd::dogen::archive_type archive::type() const {
    return type_;
}

void archive::type(const masd::dogen::archive_type v) {
    type_ = v;
}

}
