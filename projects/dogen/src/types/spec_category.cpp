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
#include "dogen/types/spec_category.hpp"

namespace dogen {

spec_category::spec_category(
    const std::string& name,
    const std::list<dogen::spec_entry>& entries,
    const std::string& description)
    : name_(name),
      entries_(entries),
      description_(description) { }

void spec_category::swap(spec_category& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(entries_, other.entries_);
    swap(description_, other.description_);
}

bool spec_category::operator==(const spec_category& rhs) const {
    return name_ == rhs.name_ &&
        entries_ == rhs.entries_ &&
        description_ == rhs.description_;
}

spec_category& spec_category::operator=(spec_category other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& spec_category::name() const {
    return name_;
}

std::string& spec_category::name() {
    return name_;
}

void spec_category::name(const std::string& v) {
    name_ = v;
}

void spec_category::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<dogen::spec_entry>& spec_category::entries() const {
    return entries_;
}

std::list<dogen::spec_entry>& spec_category::entries() {
    return entries_;
}

void spec_category::entries(const std::list<dogen::spec_entry>& v) {
    entries_ = v;
}

void spec_category::entries(const std::list<dogen::spec_entry>&& v) {
    entries_ = std::move(v);
}

const std::string& spec_category::description() const {
    return description_;
}

std::string& spec_category::description() {
    return description_;
}

void spec_category::description(const std::string& v) {
    description_ = v;
}

void spec_category::description(const std::string&& v) {
    description_ = std::move(v);
}

}
