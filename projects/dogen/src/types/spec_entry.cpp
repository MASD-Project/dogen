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
#include "dogen/types/spec_entry.hpp"

namespace dogen {

spec_entry::spec_entry(
    const std::string& name,
    const std::string& description)
    : name_(name),
      description_(description) { }

void spec_entry::swap(spec_entry& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(description_, other.description_);
}

bool spec_entry::operator==(const spec_entry& rhs) const {
    return name_ == rhs.name_ &&
        description_ == rhs.description_;
}

spec_entry& spec_entry::operator=(spec_entry other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& spec_entry::name() const {
    return name_;
}

std::string& spec_entry::name() {
    return name_;
}

void spec_entry::name(const std::string& v) {
    name_ = v;
}

void spec_entry::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& spec_entry::description() const {
    return description_;
}

std::string& spec_entry::description() {
    return description_;
}

void spec_entry::description(const std::string& v) {
    description_ = v;
}

void spec_entry::description(const std::string&& v) {
    description_ = std::move(v);
}

}
