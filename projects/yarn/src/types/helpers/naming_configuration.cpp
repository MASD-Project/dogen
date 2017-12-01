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
#include "dogen/yarn/types/helpers/naming_configuration.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

naming_configuration::naming_configuration()
    : in_global_module_(static_cast<bool>(0)) { }

naming_configuration::naming_configuration(
    const std::string& external_modules,
    const std::string& model_modules,
    const bool in_global_module)
    : external_modules_(external_modules),
      model_modules_(model_modules),
      in_global_module_(in_global_module) { }

void naming_configuration::swap(naming_configuration& other) noexcept {
    using std::swap;
    swap(external_modules_, other.external_modules_);
    swap(model_modules_, other.model_modules_);
    swap(in_global_module_, other.in_global_module_);
}

bool naming_configuration::operator==(const naming_configuration& rhs) const {
    return external_modules_ == rhs.external_modules_ &&
        model_modules_ == rhs.model_modules_ &&
        in_global_module_ == rhs.in_global_module_;
}

naming_configuration& naming_configuration::operator=(naming_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& naming_configuration::external_modules() const {
    return external_modules_;
}

std::string& naming_configuration::external_modules() {
    return external_modules_;
}

void naming_configuration::external_modules(const std::string& v) {
    external_modules_ = v;
}

void naming_configuration::external_modules(const std::string&& v) {
    external_modules_ = std::move(v);
}

const std::string& naming_configuration::model_modules() const {
    return model_modules_;
}

std::string& naming_configuration::model_modules() {
    return model_modules_;
}

void naming_configuration::model_modules(const std::string& v) {
    model_modules_ = v;
}

void naming_configuration::model_modules(const std::string&& v) {
    model_modules_ = std::move(v);
}

bool naming_configuration::in_global_module() const {
    return in_global_module_;
}

void naming_configuration::in_global_module(const bool v) {
    in_global_module_ = v;
}

} } }
