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
#include "masd.dogen.coding/types/meta_model/configuration_entry.hpp"

namespace masd::dogen::coding::meta_model {

configuration_entry::configuration_entry(
    const masd::dogen::variability::annotation& annotation,
    const std::string& name,
    const std::list<std::string>& value)
    : annotation_(annotation),
      name_(name),
      value_(value) { }

void configuration_entry::swap(configuration_entry& other) noexcept {
    using std::swap;
    swap(annotation_, other.annotation_);
    swap(name_, other.name_);
    swap(value_, other.value_);
}

bool configuration_entry::operator==(const configuration_entry& rhs) const {
    return annotation_ == rhs.annotation_ &&
        name_ == rhs.name_ &&
        value_ == rhs.value_;
}

configuration_entry& configuration_entry::operator=(configuration_entry other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::variability::annotation& configuration_entry::annotation() const {
    return annotation_;
}

masd::dogen::variability::annotation& configuration_entry::annotation() {
    return annotation_;
}

void configuration_entry::annotation(const masd::dogen::variability::annotation& v) {
    annotation_ = v;
}

void configuration_entry::annotation(const masd::dogen::variability::annotation&& v) {
    annotation_ = std::move(v);
}

const std::string& configuration_entry::name() const {
    return name_;
}

std::string& configuration_entry::name() {
    return name_;
}

void configuration_entry::name(const std::string& v) {
    name_ = v;
}

void configuration_entry::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& configuration_entry::value() const {
    return value_;
}

std::list<std::string>& configuration_entry::value() {
    return value_;
}

void configuration_entry::value(const std::list<std::string>& v) {
    value_ = v;
}

void configuration_entry::value(const std::list<std::string>&& v) {
    value_ = std::move(v);
}

}
