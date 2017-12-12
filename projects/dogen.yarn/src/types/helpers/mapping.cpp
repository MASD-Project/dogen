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
#include "dogen/yarn/types/helpers/mapping.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

mapping::mapping(
    const std::string& lam_id,
    const std::unordered_map<dogen::yarn::meta_model::languages, dogen::yarn::helpers::mapping_value>& by_language)
    : lam_id_(lam_id),
      by_language_(by_language) { }

void mapping::swap(mapping& other) noexcept {
    using std::swap;
    swap(lam_id_, other.lam_id_);
    swap(by_language_, other.by_language_);
}

bool mapping::operator==(const mapping& rhs) const {
    return lam_id_ == rhs.lam_id_ &&
        by_language_ == rhs.by_language_;
}

mapping& mapping::operator=(mapping other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& mapping::lam_id() const {
    return lam_id_;
}

std::string& mapping::lam_id() {
    return lam_id_;
}

void mapping::lam_id(const std::string& v) {
    lam_id_ = v;
}

void mapping::lam_id(const std::string&& v) {
    lam_id_ = std::move(v);
}

const std::unordered_map<dogen::yarn::meta_model::languages, dogen::yarn::helpers::mapping_value>& mapping::by_language() const {
    return by_language_;
}

std::unordered_map<dogen::yarn::meta_model::languages, dogen::yarn::helpers::mapping_value>& mapping::by_language() {
    return by_language_;
}

void mapping::by_language(const std::unordered_map<dogen::yarn::meta_model::languages, dogen::yarn::helpers::mapping_value>& v) {
    by_language_ = v;
}

void mapping::by_language(const std::unordered_map<dogen::yarn::meta_model::languages, dogen::yarn::helpers::mapping_value>&& v) {
    by_language_ = std::move(v);
}

} } }
