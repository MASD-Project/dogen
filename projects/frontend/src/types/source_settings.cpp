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
    : save_pre_processed_input_(static_cast<bool>(0)),
      disable_model_module_(static_cast<bool>(0)) { }

source_settings::source_settings(source_settings&& rhs)
    : save_pre_processed_input_(std::move(rhs.save_pre_processed_input_)),
      pre_processed_input_path_(std::move(rhs.pre_processed_input_path_)),
      disable_model_module_(std::move(rhs.disable_model_module_)) { }

source_settings::source_settings(
    const bool save_pre_processed_input,
    const boost::filesystem::path& pre_processed_input_path,
    const bool disable_model_module)
    : save_pre_processed_input_(save_pre_processed_input),
      pre_processed_input_path_(pre_processed_input_path),
      disable_model_module_(disable_model_module) { }

void source_settings::swap(source_settings& other) noexcept {
    using std::swap;
    swap(save_pre_processed_input_, other.save_pre_processed_input_);
    swap(pre_processed_input_path_, other.pre_processed_input_path_);
    swap(disable_model_module_, other.disable_model_module_);
}

bool source_settings::operator==(const source_settings& rhs) const {
    return save_pre_processed_input_ == rhs.save_pre_processed_input_ &&
        pre_processed_input_path_ == rhs.pre_processed_input_path_ &&
        disable_model_module_ == rhs.disable_model_module_;
}

source_settings& source_settings::operator=(source_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool source_settings::save_pre_processed_input() const {
    return save_pre_processed_input_;
}

void source_settings::save_pre_processed_input(const bool v) {
    save_pre_processed_input_ = v;
}

const boost::filesystem::path& source_settings::pre_processed_input_path() const {
    return pre_processed_input_path_;
}

boost::filesystem::path& source_settings::pre_processed_input_path() {
    return pre_processed_input_path_;
}

void source_settings::pre_processed_input_path(const boost::filesystem::path& v) {
    pre_processed_input_path_ = v;
}

void source_settings::pre_processed_input_path(const boost::filesystem::path&& v) {
    pre_processed_input_path_ = std::move(v);
}

bool source_settings::disable_model_module() const {
    return disable_model_module_;
}

void source_settings::disable_model_module(const bool v) {
    disable_model_module_ = v;
}

} }