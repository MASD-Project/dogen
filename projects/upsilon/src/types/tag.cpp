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
#include "dogen/upsilon/types/tag.hpp"

namespace dogen {
namespace upsilon {

tag::tag(
    const std::string& name,
    const std::string& comment)
    : name_(name),
      comment_(comment) { }

void tag::swap(tag& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(comment_, other.comment_);
}

bool tag::operator==(const tag& rhs) const {
    return name_ == rhs.name_ &&
        comment_ == rhs.comment_;
}

tag& tag::operator=(tag other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& tag::name() const {
    return name_;
}

std::string& tag::name() {
    return name_;
}

void tag::name(const std::string& v) {
    name_ = v;
}

void tag::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& tag::comment() const {
    return comment_;
}

std::string& tag::comment() {
    return comment_;
}

void tag::comment(const std::string& v) {
    comment_ = v;
}

void tag::comment(const std::string&& v) {
    comment_ = std::move(v);
}

} }
