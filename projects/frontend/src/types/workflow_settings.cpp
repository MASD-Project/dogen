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
#include "dogen/frontend/types/workflow_settings.hpp"

namespace dogen {
namespace frontend {

workflow_settings::workflow_settings()
    : save_original_input_(static_cast<bool>(0)),
      save_intermediate_sml_(static_cast<bool>(0)),
      save_merged_sml_(static_cast<bool>(0)),
      disable_model_module_(static_cast<bool>(0)) { }

workflow_settings::workflow_settings(
    const bool save_original_input,
    const std::string& original_input_extension,
    const bool save_intermediate_sml,
    const bool save_merged_sml,
    const std::string& sml_extension,
    const bool disable_model_module)
    : save_original_input_(save_original_input),
      original_input_extension_(original_input_extension),
      save_intermediate_sml_(save_intermediate_sml),
      save_merged_sml_(save_merged_sml),
      sml_extension_(sml_extension),
      disable_model_module_(disable_model_module) { }

void workflow_settings::swap(workflow_settings& other) noexcept {
    using std::swap;
    swap(save_original_input_, other.save_original_input_);
    swap(original_input_extension_, other.original_input_extension_);
    swap(save_intermediate_sml_, other.save_intermediate_sml_);
    swap(save_merged_sml_, other.save_merged_sml_);
    swap(sml_extension_, other.sml_extension_);
    swap(disable_model_module_, other.disable_model_module_);
}

bool workflow_settings::operator==(const workflow_settings& rhs) const {
    return save_original_input_ == rhs.save_original_input_ &&
        original_input_extension_ == rhs.original_input_extension_ &&
        save_intermediate_sml_ == rhs.save_intermediate_sml_ &&
        save_merged_sml_ == rhs.save_merged_sml_ &&
        sml_extension_ == rhs.sml_extension_ &&
        disable_model_module_ == rhs.disable_model_module_;
}

workflow_settings& workflow_settings::operator=(workflow_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool workflow_settings::save_original_input() const {
    return save_original_input_;
}

void workflow_settings::save_original_input(const bool v) {
    save_original_input_ = v;
}

const std::string& workflow_settings::original_input_extension() const {
    return original_input_extension_;
}

std::string& workflow_settings::original_input_extension() {
    return original_input_extension_;
}

void workflow_settings::original_input_extension(const std::string& v) {
    original_input_extension_ = v;
}

void workflow_settings::original_input_extension(const std::string&& v) {
    original_input_extension_ = std::move(v);
}

bool workflow_settings::save_intermediate_sml() const {
    return save_intermediate_sml_;
}

void workflow_settings::save_intermediate_sml(const bool v) {
    save_intermediate_sml_ = v;
}

bool workflow_settings::save_merged_sml() const {
    return save_merged_sml_;
}

void workflow_settings::save_merged_sml(const bool v) {
    save_merged_sml_ = v;
}

const std::string& workflow_settings::sml_extension() const {
    return sml_extension_;
}

std::string& workflow_settings::sml_extension() {
    return sml_extension_;
}

void workflow_settings::sml_extension(const std::string& v) {
    sml_extension_ = v;
}

void workflow_settings::sml_extension(const std::string&& v) {
    sml_extension_ = std::move(v);
}

bool workflow_settings::disable_model_module() const {
    return disable_model_module_;
}

void workflow_settings::disable_model_module(const bool v) {
    disable_model_module_ = v;
}

} }