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
#include "dogen/quilt.cpp/types/formattables/decoration_profile.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

decoration_profile::decoration_profile(
    const std::string& licence_name,
    const std::list<std::string>& copyright_notices,
    const std::string& modeline_group_name)
    : licence_name_(licence_name),
      copyright_notices_(copyright_notices),
      modeline_group_name_(modeline_group_name) { }

void decoration_profile::swap(decoration_profile& other) noexcept {
    using std::swap;
    swap(licence_name_, other.licence_name_);
    swap(copyright_notices_, other.copyright_notices_);
    swap(modeline_group_name_, other.modeline_group_name_);
}

bool decoration_profile::operator==(const decoration_profile& rhs) const {
    return licence_name_ == rhs.licence_name_ &&
        copyright_notices_ == rhs.copyright_notices_ &&
        modeline_group_name_ == rhs.modeline_group_name_;
}

decoration_profile& decoration_profile::operator=(decoration_profile other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& decoration_profile::licence_name() const {
    return licence_name_;
}

std::string& decoration_profile::licence_name() {
    return licence_name_;
}

void decoration_profile::licence_name(const std::string& v) {
    licence_name_ = v;
}

void decoration_profile::licence_name(const std::string&& v) {
    licence_name_ = std::move(v);
}

const std::list<std::string>& decoration_profile::copyright_notices() const {
    return copyright_notices_;
}

std::list<std::string>& decoration_profile::copyright_notices() {
    return copyright_notices_;
}

void decoration_profile::copyright_notices(const std::list<std::string>& v) {
    copyright_notices_ = v;
}

void decoration_profile::copyright_notices(const std::list<std::string>&& v) {
    copyright_notices_ = std::move(v);
}

const std::string& decoration_profile::modeline_group_name() const {
    return modeline_group_name_;
}

std::string& decoration_profile::modeline_group_name() {
    return modeline_group_name_;
}

void decoration_profile::modeline_group_name(const std::string& v) {
    modeline_group_name_ = v;
}

void decoration_profile::modeline_group_name(const std::string&& v) {
    modeline_group_name_ = std::move(v);
}

} } } }
