/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml_to_cpp/types/inclusion_lists.hpp"

namespace dogen {
namespace sml_to_cpp {

inclusion_lists::inclusion_lists(
    const std::list<std::string>& system,
    const std::list<std::string>& user)
    : system_(system),
      user_(user) { }

void inclusion_lists::swap(inclusion_lists& other) noexcept {
    using std::swap;
    swap(system_, other.system_);
    swap(user_, other.user_);
}

bool inclusion_lists::operator==(const inclusion_lists& rhs) const {
    return system_ == rhs.system_ &&
        user_ == rhs.user_;
}

inclusion_lists& inclusion_lists::operator=(inclusion_lists other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& inclusion_lists::system() const {
    return system_;
}

std::list<std::string>& inclusion_lists::system() {
    return system_;
}

void inclusion_lists::system(const std::list<std::string>& v) {
    system_ = v;
}

void inclusion_lists::system(const std::list<std::string>&& v) {
    system_ = std::move(v);
}

const std::list<std::string>& inclusion_lists::user() const {
    return user_;
}

std::list<std::string>& inclusion_lists::user() {
    return user_;
}

void inclusion_lists::user(const std::list<std::string>& v) {
    user_ = v;
}

void inclusion_lists::user(const std::list<std::string>&& v) {
    user_ = std::move(v);
}

} }
