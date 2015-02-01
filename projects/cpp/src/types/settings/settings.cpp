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
#include "dogen/cpp/types/settings/settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

settings::settings(
    const dogen::cpp::settings::global_settings& global_settings,
    const std::unordered_map<std::string, std::unordered_map<std::string, dogen::cpp::settings::local_settings> >& local_settings)
    : global_settings_(global_settings),
      local_settings_(local_settings) { }

void settings::swap(settings& other) noexcept {
    using std::swap;
    swap(global_settings_, other.global_settings_);
    swap(local_settings_, other.local_settings_);
}

bool settings::operator==(const settings& rhs) const {
    return global_settings_ == rhs.global_settings_ &&
        local_settings_ == rhs.local_settings_;
}

settings& settings::operator=(settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::cpp::settings::global_settings& settings::global_settings() const {
    return global_settings_;
}

dogen::cpp::settings::global_settings& settings::global_settings() {
    return global_settings_;
}

void settings::global_settings(const dogen::cpp::settings::global_settings& v) {
    global_settings_ = v;
}

void settings::global_settings(const dogen::cpp::settings::global_settings&& v) {
    global_settings_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_map<std::string, dogen::cpp::settings::local_settings> >& settings::local_settings() const {
    return local_settings_;
}

std::unordered_map<std::string, std::unordered_map<std::string, dogen::cpp::settings::local_settings> >& settings::local_settings() {
    return local_settings_;
}

void settings::local_settings(const std::unordered_map<std::string, std::unordered_map<std::string, dogen::cpp::settings::local_settings> >& v) {
    local_settings_ = v;
}

void settings::local_settings(const std::unordered_map<std::string, std::unordered_map<std::string, dogen::cpp::settings::local_settings> >&& v) {
    local_settings_ = std::move(v);
}

} } }