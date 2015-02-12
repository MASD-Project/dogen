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
#include "dogen/cpp/types/settings/local_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

local_settings::local_settings(local_settings&& rhs)
    : general_settings_(std::move(rhs.general_settings_)),
      formatter_settings_(std::move(rhs.formatter_settings_)),
      type_settings_(std::move(rhs.type_settings_)) { }

local_settings::local_settings(
    const boost::optional<dogen::formatters::general_settings>& general_settings,
    const std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>& formatter_settings,
    const boost::optional<dogen::cpp::settings::type_settings>& type_settings)
    : general_settings_(general_settings),
      formatter_settings_(formatter_settings),
      type_settings_(type_settings) { }

void local_settings::swap(local_settings& other) noexcept {
    using std::swap;
    swap(general_settings_, other.general_settings_);
    swap(formatter_settings_, other.formatter_settings_);
    swap(type_settings_, other.type_settings_);
}

bool local_settings::operator==(const local_settings& rhs) const {
    return general_settings_ == rhs.general_settings_ &&
        formatter_settings_ == rhs.formatter_settings_ &&
        type_settings_ == rhs.type_settings_;
}

local_settings& local_settings::operator=(local_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::general_settings>& local_settings::general_settings() const {
    return general_settings_;
}

boost::optional<dogen::formatters::general_settings>& local_settings::general_settings() {
    return general_settings_;
}

void local_settings::general_settings(const boost::optional<dogen::formatters::general_settings>& v) {
    general_settings_ = v;
}

void local_settings::general_settings(const boost::optional<dogen::formatters::general_settings>&& v) {
    general_settings_ = std::move(v);
}

const std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>& local_settings::formatter_settings() const {
    return formatter_settings_;
}

std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>& local_settings::formatter_settings() {
    return formatter_settings_;
}

void local_settings::formatter_settings(const std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>& v) {
    formatter_settings_ = v;
}

void local_settings::formatter_settings(const std::unordered_map<std::string, dogen::cpp::settings::local_formatter_settings>&& v) {
    formatter_settings_ = std::move(v);
}

const boost::optional<dogen::cpp::settings::type_settings>& local_settings::type_settings() const {
    return type_settings_;
}

boost::optional<dogen::cpp::settings::type_settings>& local_settings::type_settings() {
    return type_settings_;
}

void local_settings::type_settings(const boost::optional<dogen::cpp::settings::type_settings>& v) {
    type_settings_ = v;
}

void local_settings::type_settings(const boost::optional<dogen::cpp::settings::type_settings>&& v) {
    type_settings_ = std::move(v);
}

} } }