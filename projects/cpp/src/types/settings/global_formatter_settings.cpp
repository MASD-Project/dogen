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
#include "dogen/cpp/types/settings/global_formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

global_formatter_settings::global_formatter_settings()
    : enabled_(static_cast<bool>(0)) { }

global_formatter_settings::global_formatter_settings(
    const bool enabled,
    const std::string& postfix)
    : enabled_(enabled),
      postfix_(postfix) { }

void global_formatter_settings::swap(global_formatter_settings& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(postfix_, other.postfix_);
}

bool global_formatter_settings::operator==(const global_formatter_settings& rhs) const {
    return enabled_ == rhs.enabled_ &&
        postfix_ == rhs.postfix_;
}

global_formatter_settings& global_formatter_settings::operator=(global_formatter_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool global_formatter_settings::enabled() const {
    return enabled_;
}

void global_formatter_settings::enabled(const bool v) {
    enabled_ = v;
}

const std::string& global_formatter_settings::postfix() const {
    return postfix_;
}

std::string& global_formatter_settings::postfix() {
    return postfix_;
}

void global_formatter_settings::postfix(const std::string& v) {
    postfix_ = v;
}

void global_formatter_settings::postfix(const std::string&& v) {
    postfix_ = std::move(v);
}

} } }