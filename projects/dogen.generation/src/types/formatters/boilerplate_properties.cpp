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
#include "dogen.generation/types/formatters/boilerplate_properties.hpp"

namespace dogen::generation::formatters {

boilerplate_properties::boilerplate_properties()
    : technical_space_(static_cast<dogen::logical::entities::technical_space>(0)),
      generate_preamble_(static_cast<bool>(0)),
      generate_header_guards_(static_cast<bool>(0)) { }

boilerplate_properties::boilerplate_properties(
    const std::string& preamble,
    const std::string& postamble,
    const std::list<std::string>& dependencies,
    const std::string& header_guard,
    const dogen::logical::entities::technical_space technical_space,
    const bool generate_preamble,
    const bool generate_header_guards)
    : preamble_(preamble),
      postamble_(postamble),
      dependencies_(dependencies),
      header_guard_(header_guard),
      technical_space_(technical_space),
      generate_preamble_(generate_preamble),
      generate_header_guards_(generate_header_guards) { }

void boilerplate_properties::swap(boilerplate_properties& other) noexcept {
    using std::swap;
    swap(preamble_, other.preamble_);
    swap(postamble_, other.postamble_);
    swap(dependencies_, other.dependencies_);
    swap(header_guard_, other.header_guard_);
    swap(technical_space_, other.technical_space_);
    swap(generate_preamble_, other.generate_preamble_);
    swap(generate_header_guards_, other.generate_header_guards_);
}

bool boilerplate_properties::operator==(const boilerplate_properties& rhs) const {
    return preamble_ == rhs.preamble_ &&
        postamble_ == rhs.postamble_ &&
        dependencies_ == rhs.dependencies_ &&
        header_guard_ == rhs.header_guard_ &&
        technical_space_ == rhs.technical_space_ &&
        generate_preamble_ == rhs.generate_preamble_ &&
        generate_header_guards_ == rhs.generate_header_guards_;
}

boilerplate_properties& boilerplate_properties::operator=(boilerplate_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& boilerplate_properties::preamble() const {
    return preamble_;
}

std::string& boilerplate_properties::preamble() {
    return preamble_;
}

void boilerplate_properties::preamble(const std::string& v) {
    preamble_ = v;
}

void boilerplate_properties::preamble(const std::string&& v) {
    preamble_ = std::move(v);
}

const std::string& boilerplate_properties::postamble() const {
    return postamble_;
}

std::string& boilerplate_properties::postamble() {
    return postamble_;
}

void boilerplate_properties::postamble(const std::string& v) {
    postamble_ = v;
}

void boilerplate_properties::postamble(const std::string&& v) {
    postamble_ = std::move(v);
}

const std::list<std::string>& boilerplate_properties::dependencies() const {
    return dependencies_;
}

std::list<std::string>& boilerplate_properties::dependencies() {
    return dependencies_;
}

void boilerplate_properties::dependencies(const std::list<std::string>& v) {
    dependencies_ = v;
}

void boilerplate_properties::dependencies(const std::list<std::string>&& v) {
    dependencies_ = std::move(v);
}

const std::string& boilerplate_properties::header_guard() const {
    return header_guard_;
}

std::string& boilerplate_properties::header_guard() {
    return header_guard_;
}

void boilerplate_properties::header_guard(const std::string& v) {
    header_guard_ = v;
}

void boilerplate_properties::header_guard(const std::string&& v) {
    header_guard_ = std::move(v);
}

dogen::logical::entities::technical_space boilerplate_properties::technical_space() const {
    return technical_space_;
}

void boilerplate_properties::technical_space(const dogen::logical::entities::technical_space v) {
    technical_space_ = v;
}

bool boilerplate_properties::generate_preamble() const {
    return generate_preamble_;
}

void boilerplate_properties::generate_preamble(const bool v) {
    generate_preamble_ = v;
}

bool boilerplate_properties::generate_header_guards() const {
    return generate_header_guards_;
}

void boilerplate_properties::generate_header_guards(const bool v) {
    generate_header_guards_ = v;
}

}
