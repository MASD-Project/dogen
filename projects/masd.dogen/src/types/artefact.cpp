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
#include "masd.dogen/types/artefact.hpp"

namespace masd::dogen {

artefact::artefact(
    const std::string& name,
    const std::string& content,
    const std::string& diff,
    const masd::dogen::operation& operation)
    : name_(name),
      content_(content),
      diff_(diff),
      operation_(operation) { }

void artefact::swap(artefact& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(content_, other.content_);
    swap(diff_, other.diff_);
    swap(operation_, other.operation_);
}

bool artefact::operator==(const artefact& rhs) const {
    return name_ == rhs.name_ &&
        content_ == rhs.content_ &&
        diff_ == rhs.diff_ &&
        operation_ == rhs.operation_;
}

artefact& artefact::operator=(artefact other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& artefact::name() const {
    return name_;
}

std::string& artefact::name() {
    return name_;
}

void artefact::name(const std::string& v) {
    name_ = v;
}

void artefact::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& artefact::content() const {
    return content_;
}

std::string& artefact::content() {
    return content_;
}

void artefact::content(const std::string& v) {
    content_ = v;
}

void artefact::content(const std::string&& v) {
    content_ = std::move(v);
}

const std::string& artefact::diff() const {
    return diff_;
}

std::string& artefact::diff() {
    return diff_;
}

void artefact::diff(const std::string& v) {
    diff_ = v;
}

void artefact::diff(const std::string&& v) {
    diff_ = std::move(v);
}

const masd::dogen::operation& artefact::operation() const {
    return operation_;
}

masd::dogen::operation& artefact::operation() {
    return operation_;
}

void artefact::operation(const masd::dogen::operation& v) {
    operation_ = v;
}

void artefact::operation(const masd::dogen::operation&& v) {
    operation_ = std::move(v);
}

}
