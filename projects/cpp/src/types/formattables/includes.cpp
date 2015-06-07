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
#include "dogen/cpp/types/formattables/includes.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

includes::includes(
    const std::list<boost::filesystem::path>& system,
    const std::list<boost::filesystem::path>& user)
    : system_(system),
      user_(user) { }

void includes::swap(includes& other) noexcept {
    using std::swap;
    swap(system_, other.system_);
    swap(user_, other.user_);
}

bool includes::operator==(const includes& rhs) const {
    return system_ == rhs.system_ &&
        user_ == rhs.user_;
}

includes& includes::operator=(includes other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<boost::filesystem::path>& includes::system() const {
    return system_;
}

std::list<boost::filesystem::path>& includes::system() {
    return system_;
}

void includes::system(const std::list<boost::filesystem::path>& v) {
    system_ = v;
}

void includes::system(const std::list<boost::filesystem::path>&& v) {
    system_ = std::move(v);
}

const std::list<boost::filesystem::path>& includes::user() const {
    return user_;
}

std::list<boost::filesystem::path>& includes::user() {
    return user_;
}

void includes::user(const std::list<boost::filesystem::path>& v) {
    user_ = v;
}

void includes::user(const std::list<boost::filesystem::path>&& v) {
    user_ = std::move(v);
}

} } }
