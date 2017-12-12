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
    const std::unordered_set<std::string>& labels,
    const std::list<dogen::annotations::entry_template>& templates)
    : name_(name),
      parents_(parents),
      labels_(labels),
      templates_(templates) { }

void profile::swap(profile& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(parents_, other.parents_);
    swap(labels_, other.labels_);
    swap(templates_, other.templates_);
}

bool profile::operator==(const profile& rhs) const {
    return name_ == rhs.name_ &&
        parents_ == rhs.parents_ &&
        labels_ == rhs.labels_ &&
        templates_ == rhs.templates_;
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

const std::unordered_set<std::string>& profile::labels() const {
    return labels_;
}

std::unordered_set<std::string>& profile::labels() {
    return labels_;
}

void profile::labels(const std::unordered_set<std::string>& v) {
    labels_ = v;
}

void profile::labels(const std::unordered_set<std::string>&& v) {
    labels_ = std::move(v);
}

const std::list<dogen::annotations::entry_template>& profile::templates() const {
    return templates_;
}

std::list<dogen::annotations::entry_template>& profile::templates() {
    return templates_;
}

void profile::templates(const std::list<dogen::annotations::entry_template>& v) {
    templates_ = v;
}

void profile::templates(const std::list<dogen::annotations::entry_template>&& v) {
    templates_ = std::move(v);
}

} }
