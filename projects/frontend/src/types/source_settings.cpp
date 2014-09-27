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
#include "dogen/frontend/types/source_settings.hpp"

namespace dogen {
namespace frontend {

source_settings::source_settings()
    : save_original_input_(static_cast<bool>(0)) { }

source_settings::source_settings(
    const bool save_original_input,
    const std::string& original_input_extension)
    : save_original_input_(save_original_input),
      original_input_extension_(original_input_extension) { }

void source_settings::swap(source_settings& other) noexcept {
    using std::swap;
    swap(save_original_input_, other.save_original_input_);
    swap(original_input_extension_, other.original_input_extension_);
}

bool source_settings::operator==(const source_settings& rhs) const {
    return save_original_input_ == rhs.save_original_input_ &&
        original_input_extension_ == rhs.original_input_extension_;
}

source_settings& source_settings::operator=(source_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool source_settings::save_original_input() const {
    return save_original_input_;
}

void source_settings::save_original_input(const bool v) {
    save_original_input_ = v;
}

const std::string& source_settings::original_input_extension() const {
    return original_input_extension_;
}

std::string& source_settings::original_input_extension() {
    return original_input_extension_;
}

void source_settings::original_input_extension(const std::string& v) {
    original_input_extension_ = v;
}

void source_settings::original_input_extension(const std::string&& v) {
    original_input_extension_ = std::move(v);
}

} }