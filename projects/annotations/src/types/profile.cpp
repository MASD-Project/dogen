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
#include "dogen/annotations/types/profile.hpp"

namespace dogen {
namespace annotations {

profile::profile(
    const std::string& name,
    const std::list<std::string>& parents,
    const std::unordered_map<std::string, dogen::annotations::value_template>& value_templates)
    : name_(name),
      parents_(parents),
      value_templates_(value_templates) { }

void profile::swap(profile& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(parents_, other.parents_);
    swap(value_templates_, other.value_templates_);
}

bool profile::operator==(const profile& rhs) const {
    return name_ == rhs.name_ &&
        parents_ == rhs.parents_ &&
        value_templates_ == rhs.value_templates_;
}

profile& profile::operator=(profile other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& profile::name() const {
    return name_;
}

std::string& profile::name() {
    return name_;
}

void profile::name(const std::string& v) {
    name_ = v;
}

void profile::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& profile::parents() const {
    return parents_;
}

std::list<std::string>& profile::parents() {
    return parents_;
}

void profile::parents(const std::list<std::string>& v) {
    parents_ = v;
}

void profile::parents(const std::list<std::string>&& v) {
    parents_ = std::move(v);
}

const std::unordered_map<std::string, dogen::annotations::value_template>& profile::value_templates() const {
    return value_templates_;
}

std::unordered_map<std::string, dogen::annotations::value_template>& profile::value_templates() {
    return value_templates_;
}

void profile::value_templates(const std::unordered_map<std::string, dogen::annotations::value_template>& v) {
    value_templates_ = v;
}

void profile::value_templates(const std::unordered_map<std::string, dogen::annotations::value_template>&& v) {
    value_templates_ = std::move(v);
}

} }
