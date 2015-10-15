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
#include "dogen/yarn/types/location.hpp"

namespace dogen {
namespace yarn {

location::location(
    const std::string& original_model_name,
    const std::list<std::string>& external_module_path,
    const std::list<std::string>& model_module_path,
    const std::list<std::string>& internal_module_path)
    : original_model_name_(original_model_name),
      external_module_path_(external_module_path),
      model_module_path_(model_module_path),
      internal_module_path_(internal_module_path) { }

void location::swap(location& other) noexcept {
    using std::swap;
    swap(original_model_name_, other.original_model_name_);
    swap(external_module_path_, other.external_module_path_);
    swap(model_module_path_, other.model_module_path_);
    swap(internal_module_path_, other.internal_module_path_);
}

bool location::operator==(const location& rhs) const {
    return original_model_name_ == rhs.original_model_name_ &&
        external_module_path_ == rhs.external_module_path_ &&
        model_module_path_ == rhs.model_module_path_ &&
        internal_module_path_ == rhs.internal_module_path_;
}

location& location::operator=(location other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& location::original_model_name() const {
    return original_model_name_;
}

std::string& location::original_model_name() {
    return original_model_name_;
}

void location::original_model_name(const std::string& v) {
    original_model_name_ = v;
}

void location::original_model_name(const std::string&& v) {
    original_model_name_ = std::move(v);
}

const std::list<std::string>& location::external_module_path() const {
    return external_module_path_;
}

std::list<std::string>& location::external_module_path() {
    return external_module_path_;
}

void location::external_module_path(const std::list<std::string>& v) {
    external_module_path_ = v;
}

void location::external_module_path(const std::list<std::string>&& v) {
    external_module_path_ = std::move(v);
}

const std::list<std::string>& location::model_module_path() const {
    return model_module_path_;
}

std::list<std::string>& location::model_module_path() {
    return model_module_path_;
}

void location::model_module_path(const std::list<std::string>& v) {
    model_module_path_ = v;
}

void location::model_module_path(const std::list<std::string>&& v) {
    model_module_path_ = std::move(v);
}

const std::list<std::string>& location::internal_module_path() const {
    return internal_module_path_;
}

std::list<std::string>& location::internal_module_path() {
    return internal_module_path_;
}

void location::internal_module_path(const std::list<std::string>& v) {
    internal_module_path_ = v;
}

void location::internal_module_path(const std::list<std::string>&& v) {
    internal_module_path_ = std::move(v);
}

} }
