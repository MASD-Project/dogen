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
#include "dogen/cpp/types/settings/global_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

global_settings::global_settings(
    const dogen::formatters::general_settings& general_settings,
    const dogen::cpp::settings::cpp_settings& cpp_settings,
    const std::unordered_map<std::string, dogen::cpp::settings::facet_settings>& facet_settings,
    const std::unordered_map<std::string, dogen::cpp::settings::global_formatter_settings>& formatter_settings)
    : general_settings_(general_settings),
      cpp_settings_(cpp_settings),
      facet_settings_(facet_settings),
      formatter_settings_(formatter_settings) { }

void global_settings::swap(global_settings& other) noexcept {
    using std::swap;
    swap(general_settings_, other.general_settings_);
    swap(cpp_settings_, other.cpp_settings_);
    swap(facet_settings_, other.facet_settings_);
    swap(formatter_settings_, other.formatter_settings_);
}

bool global_settings::operator==(const global_settings& rhs) const {
    return general_settings_ == rhs.general_settings_ &&
        cpp_settings_ == rhs.cpp_settings_ &&
        facet_settings_ == rhs.facet_settings_ &&
        formatter_settings_ == rhs.formatter_settings_;
}

global_settings& global_settings::operator=(global_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::formatters::general_settings& global_settings::general_settings() const {
    return general_settings_;
}

dogen::formatters::general_settings& global_settings::general_settings() {
    return general_settings_;
}

void global_settings::general_settings(const dogen::formatters::general_settings& v) {
    general_settings_ = v;
}

void global_settings::general_settings(const dogen::formatters::general_settings&& v) {
    general_settings_ = std::move(v);
}

const dogen::cpp::settings::cpp_settings& global_settings::cpp_settings() const {
    return cpp_settings_;
}

dogen::cpp::settings::cpp_settings& global_settings::cpp_settings() {
    return cpp_settings_;
}

void global_settings::cpp_settings(const dogen::cpp::settings::cpp_settings& v) {
    cpp_settings_ = v;
}

void global_settings::cpp_settings(const dogen::cpp::settings::cpp_settings&& v) {
    cpp_settings_ = std::move(v);
}

const std::unordered_map<std::string, dogen::cpp::settings::facet_settings>& global_settings::facet_settings() const {
    return facet_settings_;
}

std::unordered_map<std::string, dogen::cpp::settings::facet_settings>& global_settings::facet_settings() {
    return facet_settings_;
}

void global_settings::facet_settings(const std::unordered_map<std::string, dogen::cpp::settings::facet_settings>& v) {
    facet_settings_ = v;
}

void global_settings::facet_settings(const std::unordered_map<std::string, dogen::cpp::settings::facet_settings>&& v) {
    facet_settings_ = std::move(v);
}

const std::unordered_map<std::string, dogen::cpp::settings::global_formatter_settings>& global_settings::formatter_settings() const {
    return formatter_settings_;
}

std::unordered_map<std::string, dogen::cpp::settings::global_formatter_settings>& global_settings::formatter_settings() {
    return formatter_settings_;
}

void global_settings::formatter_settings(const std::unordered_map<std::string, dogen::cpp::settings::global_formatter_settings>& v) {
    formatter_settings_ = v;
}

void global_settings::formatter_settings(const std::unordered_map<std::string, dogen::cpp::settings::global_formatter_settings>&& v) {
    formatter_settings_ = std::move(v);
}

} } }