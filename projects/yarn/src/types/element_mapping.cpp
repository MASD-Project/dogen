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
#include "dogen/yarn/types/element_mapping.hpp"

namespace dogen {
namespace yarn {

element_mapping::element_mapping(
    const std::string& id,
    const std::unordered_map<dogen::yarn::languages, dogen::yarn::name>& names_by_language)
    : id_(id),
      names_by_language_(names_by_language) { }

void element_mapping::swap(element_mapping& other) noexcept {
    using std::swap;
    swap(id_, other.id_);
    swap(names_by_language_, other.names_by_language_);
}

bool element_mapping::operator==(const element_mapping& rhs) const {
    return id_ == rhs.id_ &&
        names_by_language_ == rhs.names_by_language_;
}

element_mapping& element_mapping::operator=(element_mapping other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& element_mapping::id() const {
    return id_;
}

std::string& element_mapping::id() {
    return id_;
}

void element_mapping::id(const std::string& v) {
    id_ = v;
}

void element_mapping::id(const std::string&& v) {
    id_ = std::move(v);
}

const std::unordered_map<dogen::yarn::languages, dogen::yarn::name>& element_mapping::names_by_language() const {
    return names_by_language_;
}

std::unordered_map<dogen::yarn::languages, dogen::yarn::name>& element_mapping::names_by_language() {
    return names_by_language_;
}

void element_mapping::names_by_language(const std::unordered_map<dogen::yarn::languages, dogen::yarn::name>& v) {
    names_by_language_ = v;
}

void element_mapping::names_by_language(const std::unordered_map<dogen::yarn::languages, dogen::yarn::name>&& v) {
    names_by_language_ = std::move(v);
}

} }
