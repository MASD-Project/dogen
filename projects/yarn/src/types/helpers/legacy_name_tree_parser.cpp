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
#include "dogen/yarn/types/helpers/legacy_name_tree_parser.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

legacy_name_tree_parser::legacy_name_tree_parser(
    const std::unordered_set<std::string>& modules,
    const std::list<std::string>& external_modules,
    const std::string& model_name)
    : modules_(modules),
      external_modules_(external_modules),
      model_name_(model_name) { }

void legacy_name_tree_parser::swap(legacy_name_tree_parser& other) noexcept {
    using std::swap;
    swap(modules_, other.modules_);
    swap(external_modules_, other.external_modules_);
    swap(model_name_, other.model_name_);
}

bool legacy_name_tree_parser::operator==(const legacy_name_tree_parser& rhs) const {
    return modules_ == rhs.modules_ &&
        external_modules_ == rhs.external_modules_ &&
        model_name_ == rhs.model_name_;
}

legacy_name_tree_parser& legacy_name_tree_parser::operator=(legacy_name_tree_parser other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& legacy_name_tree_parser::modules() const {
    return modules_;
}

std::unordered_set<std::string>& legacy_name_tree_parser::modules() {
    return modules_;
}

void legacy_name_tree_parser::modules(const std::unordered_set<std::string>& v) {
    modules_ = v;
}

void legacy_name_tree_parser::modules(const std::unordered_set<std::string>&& v) {
    modules_ = std::move(v);
}

const std::list<std::string>& legacy_name_tree_parser::external_modules() const {
    return external_modules_;
}

std::list<std::string>& legacy_name_tree_parser::external_modules() {
    return external_modules_;
}

void legacy_name_tree_parser::external_modules(const std::list<std::string>& v) {
    external_modules_ = v;
}

void legacy_name_tree_parser::external_modules(const std::list<std::string>&& v) {
    external_modules_ = std::move(v);
}

const std::string& legacy_name_tree_parser::model_name() const {
    return model_name_;
}

std::string& legacy_name_tree_parser::model_name() {
    return model_name_;
}

void legacy_name_tree_parser::model_name(const std::string& v) {
    model_name_ = v;
}

void legacy_name_tree_parser::model_name(const std::string&& v) {
    model_name_ = std::move(v);
}

} } }
