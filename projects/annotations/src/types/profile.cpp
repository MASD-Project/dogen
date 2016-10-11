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
    const std::unordered_map<std::string, dogen::annotations::field_instance_definition>& instance_definitions,
    const dogen::annotations::annotation& content)
    : name_(name),
      parents_(parents),
      instance_definitions_(instance_definitions),
      content_(content) { }

void profile::swap(profile& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(parents_, other.parents_);
    swap(instance_definitions_, other.instance_definitions_);
    swap(content_, other.content_);
}

bool profile::operator==(const profile& rhs) const {
    return name_ == rhs.name_ &&
        parents_ == rhs.parents_ &&
        instance_definitions_ == rhs.instance_definitions_ &&
        content_ == rhs.content_;
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

const std::unordered_map<std::string, dogen::annotations::field_instance_definition>& profile::instance_definitions() const {
    return instance_definitions_;
}

std::unordered_map<std::string, dogen::annotations::field_instance_definition>& profile::instance_definitions() {
    return instance_definitions_;
}

void profile::instance_definitions(const std::unordered_map<std::string, dogen::annotations::field_instance_definition>& v) {
    instance_definitions_ = v;
}

void profile::instance_definitions(const std::unordered_map<std::string, dogen::annotations::field_instance_definition>&& v) {
    instance_definitions_ = std::move(v);
}

const dogen::annotations::annotation& profile::content() const {
    return content_;
}

dogen::annotations::annotation& profile::content() {
    return content_;
}

void profile::content(const dogen::annotations::annotation& v) {
    content_ = v;
}

void profile::content(const dogen::annotations::annotation&& v) {
    content_ = std::move(v);
}

} }
