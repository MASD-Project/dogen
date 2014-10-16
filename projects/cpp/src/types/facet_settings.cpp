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
#include "dogen/cpp/types/facet_settings.hpp"

namespace dogen {
namespace cpp {

facet_settings::facet_settings()
    : enabled_(static_cast<bool>(0)) { }

facet_settings::facet_settings(
    const bool enabled,
    const std::string& directory_name,
    const std::string& postfix)
    : enabled_(enabled),
      directory_name_(directory_name),
      postfix_(postfix) { }

void facet_settings::swap(facet_settings& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(directory_name_, other.directory_name_);
    swap(postfix_, other.postfix_);
}

bool facet_settings::operator==(const facet_settings& rhs) const {
    return enabled_ == rhs.enabled_ &&
        directory_name_ == rhs.directory_name_ &&
        postfix_ == rhs.postfix_;
}

facet_settings& facet_settings::operator=(facet_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool facet_settings::enabled() const {
    return enabled_;
}

void facet_settings::enabled(const bool v) {
    enabled_ = v;
}

const std::string& facet_settings::directory_name() const {
    return directory_name_;
}

std::string& facet_settings::directory_name() {
    return directory_name_;
}

void facet_settings::directory_name(const std::string& v) {
    directory_name_ = v;
}

void facet_settings::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

const std::string& facet_settings::postfix() const {
    return postfix_;
}

std::string& facet_settings::postfix() {
    return postfix_;
}

void facet_settings::postfix(const std::string& v) {
    postfix_ = v;
}

void facet_settings::postfix(const std::string&& v) {
    postfix_ = std::move(v);
}

} }