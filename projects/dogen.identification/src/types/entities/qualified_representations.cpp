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
#include "dogen.identification/types/entities/qualified_representations.hpp"

namespace dogen::identification::entities {

qualified_representations::qualified_representations(
    const std::string& dot,
    const std::string& colon,
    const std::string& identifiable)
    : dot_(dot),
      colon_(colon),
      identifiable_(identifiable) { }

void qualified_representations::swap(qualified_representations& other) noexcept {
    using std::swap;
    swap(dot_, other.dot_);
    swap(colon_, other.colon_);
    swap(identifiable_, other.identifiable_);
}

bool qualified_representations::operator==(const qualified_representations& rhs) const {
    return dot_ == rhs.dot_ &&
        colon_ == rhs.colon_ &&
        identifiable_ == rhs.identifiable_;
}

qualified_representations& qualified_representations::operator=(qualified_representations other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& qualified_representations::dot() const {
    return dot_;
}

std::string& qualified_representations::dot() {
    return dot_;
}

void qualified_representations::dot(const std::string& v) {
    dot_ = v;
}

void qualified_representations::dot(const std::string&& v) {
    dot_ = std::move(v);
}

const std::string& qualified_representations::colon() const {
    return colon_;
}

std::string& qualified_representations::colon() {
    return colon_;
}

void qualified_representations::colon(const std::string& v) {
    colon_ = v;
}

void qualified_representations::colon(const std::string&& v) {
    colon_ = std::move(v);
}

const std::string& qualified_representations::identifiable() const {
    return identifiable_;
}

std::string& qualified_representations::identifiable() {
    return identifiable_;
}

void qualified_representations::identifiable(const std::string& v) {
    identifiable_ = v;
}

void qualified_representations::identifiable(const std::string&& v) {
    identifiable_ = std::move(v);
}

}
