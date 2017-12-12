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
#include "dogen.formatters/types/repository.hpp"

namespace dogen {
namespace formatters {

repository::repository(
    const std::unordered_map<std::string, dogen::formatters::modeline_group>& modeline_groups,
    const std::unordered_map<std::string, std::string>& licence_texts)
    : modeline_groups_(modeline_groups),
      licence_texts_(licence_texts) { }

void repository::swap(repository& other) noexcept {
    using std::swap;
    swap(modeline_groups_, other.modeline_groups_);
    swap(licence_texts_, other.licence_texts_);
}

bool repository::operator==(const repository& rhs) const {
    return modeline_groups_ == rhs.modeline_groups_ &&
        licence_texts_ == rhs.licence_texts_;
}

repository& repository::operator=(repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::formatters::modeline_group>& repository::modeline_groups() const {
    return modeline_groups_;
}

std::unordered_map<std::string, dogen::formatters::modeline_group>& repository::modeline_groups() {
    return modeline_groups_;
}

void repository::modeline_groups(const std::unordered_map<std::string, dogen::formatters::modeline_group>& v) {
    modeline_groups_ = v;
}

void repository::modeline_groups(const std::unordered_map<std::string, dogen::formatters::modeline_group>&& v) {
    modeline_groups_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& repository::licence_texts() const {
    return licence_texts_;
}

std::unordered_map<std::string, std::string>& repository::licence_texts() {
    return licence_texts_;
}

void repository::licence_texts(const std::unordered_map<std::string, std::string>& v) {
    licence_texts_ = v;
}

void repository::licence_texts(const std::unordered_map<std::string, std::string>&& v) {
    licence_texts_ = std::move(v);
}

} }
