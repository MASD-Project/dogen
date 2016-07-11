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
#include "dogen/quilt.cpp/types/settings/streaming_settings.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

streaming_settings::streaming_settings()
    : requires_quoting_(static_cast<bool>(0)),
      requires_dereferencing_(static_cast<bool>(0)),
      remove_unprintable_characters_(static_cast<bool>(0)) { }

streaming_settings::streaming_settings(
    const bool requires_quoting,
    const bool requires_dereferencing,
    const std::string& string_conversion_method,
    const bool remove_unprintable_characters)
    : requires_quoting_(requires_quoting),
      requires_dereferencing_(requires_dereferencing),
      string_conversion_method_(string_conversion_method),
      remove_unprintable_characters_(remove_unprintable_characters) { }

void streaming_settings::swap(streaming_settings& other) noexcept {
    using std::swap;
    swap(requires_quoting_, other.requires_quoting_);
    swap(requires_dereferencing_, other.requires_dereferencing_);
    swap(string_conversion_method_, other.string_conversion_method_);
    swap(remove_unprintable_characters_, other.remove_unprintable_characters_);
}

bool streaming_settings::operator==(const streaming_settings& rhs) const {
    return requires_quoting_ == rhs.requires_quoting_ &&
        requires_dereferencing_ == rhs.requires_dereferencing_ &&
        string_conversion_method_ == rhs.string_conversion_method_ &&
        remove_unprintable_characters_ == rhs.remove_unprintable_characters_;
}

streaming_settings& streaming_settings::operator=(streaming_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool streaming_settings::requires_quoting() const {
    return requires_quoting_;
}

void streaming_settings::requires_quoting(const bool v) {
    requires_quoting_ = v;
}

bool streaming_settings::requires_dereferencing() const {
    return requires_dereferencing_;
}

void streaming_settings::requires_dereferencing(const bool v) {
    requires_dereferencing_ = v;
}

const std::string& streaming_settings::string_conversion_method() const {
    return string_conversion_method_;
}

std::string& streaming_settings::string_conversion_method() {
    return string_conversion_method_;
}

void streaming_settings::string_conversion_method(const std::string& v) {
    string_conversion_method_ = v;
}

void streaming_settings::string_conversion_method(const std::string&& v) {
    string_conversion_method_ = std::move(v);
}

bool streaming_settings::remove_unprintable_characters() const {
    return remove_unprintable_characters_;
}

void streaming_settings::remove_unprintable_characters(const bool v) {
    remove_unprintable_characters_ = v;
}

} } } }
