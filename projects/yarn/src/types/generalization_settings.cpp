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
#include "dogen/yarn/types/generalization_settings.hpp"

namespace dogen {
namespace yarn {

generalization_settings::generalization_settings(generalization_settings&& rhs)
    : is_final_(std::move(rhs.is_final_)),
      parent_(std::move(rhs.parent_)) { }

generalization_settings::generalization_settings(
    const boost::optional<bool>& is_final,
    const boost::optional<std::string>& parent)
    : is_final_(is_final),
      parent_(parent) { }

void generalization_settings::swap(generalization_settings& other) noexcept {
    using std::swap;
    swap(is_final_, other.is_final_);
    swap(parent_, other.parent_);
}

bool generalization_settings::operator==(const generalization_settings& rhs) const {
    return is_final_ == rhs.is_final_ &&
        parent_ == rhs.parent_;
}

generalization_settings& generalization_settings::operator=(generalization_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<bool>& generalization_settings::is_final() const {
    return is_final_;
}

boost::optional<bool>& generalization_settings::is_final() {
    return is_final_;
}

void generalization_settings::is_final(const boost::optional<bool>& v) {
    is_final_ = v;
}

void generalization_settings::is_final(const boost::optional<bool>&& v) {
    is_final_ = std::move(v);
}

const boost::optional<std::string>& generalization_settings::parent() const {
    return parent_;
}

boost::optional<std::string>& generalization_settings::parent() {
    return parent_;
}

void generalization_settings::parent(const boost::optional<std::string>& v) {
    parent_ = v;
}

void generalization_settings::parent(const boost::optional<std::string>&& v) {
    parent_ = std::move(v);
}

} }
