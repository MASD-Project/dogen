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
#include "dogen/quilt.cpp/types/formatters/context.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

context::context(
    const dogen::quilt::cpp::settings::bundle& bundle,
    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_properties>& formatter_properties)
    : bundle_(bundle),
      formatter_properties_(formatter_properties) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(bundle_, other.bundle_);
    swap(formatter_properties_, other.formatter_properties_);
}

bool context::operator==(const context& rhs) const {
    return bundle_ == rhs.bundle_ &&
        formatter_properties_ == rhs.formatter_properties_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::quilt::cpp::settings::bundle& context::bundle() const {
    return bundle_;
}

dogen::quilt::cpp::settings::bundle& context::bundle() {
    return bundle_;
}

void context::bundle(const dogen::quilt::cpp::settings::bundle& v) {
    bundle_ = v;
}

void context::bundle(const dogen::quilt::cpp::settings::bundle&& v) {
    bundle_ = std::move(v);
}

const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_properties>& context::formatter_properties() const {
    return formatter_properties_;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_properties>& context::formatter_properties() {
    return formatter_properties_;
}

void context::formatter_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_properties>& v) {
    formatter_properties_ = v;
}

void context::formatter_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_properties>&& v) {
    formatter_properties_ = std::move(v);
}

} } } }
