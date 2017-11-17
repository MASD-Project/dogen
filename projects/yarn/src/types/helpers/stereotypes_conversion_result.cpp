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
#include "dogen/yarn/types/helpers/stereotypes_conversion_result.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

stereotypes_conversion_result::stereotypes_conversion_result(
    const std::list<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes,
    const std::vector<std::string>& unknown_stereotypes)
    : well_known_stereotypes_(well_known_stereotypes),
      unknown_stereotypes_(unknown_stereotypes) { }

void stereotypes_conversion_result::swap(stereotypes_conversion_result& other) noexcept {
    using std::swap;
    swap(well_known_stereotypes_, other.well_known_stereotypes_);
    swap(unknown_stereotypes_, other.unknown_stereotypes_);
}

bool stereotypes_conversion_result::operator==(const stereotypes_conversion_result& rhs) const {
    return well_known_stereotypes_ == rhs.well_known_stereotypes_ &&
        unknown_stereotypes_ == rhs.unknown_stereotypes_;
}

stereotypes_conversion_result& stereotypes_conversion_result::operator=(stereotypes_conversion_result other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::yarn::meta_model::well_known_stereotypes>& stereotypes_conversion_result::well_known_stereotypes() const {
    return well_known_stereotypes_;
}

std::list<dogen::yarn::meta_model::well_known_stereotypes>& stereotypes_conversion_result::well_known_stereotypes() {
    return well_known_stereotypes_;
}

void stereotypes_conversion_result::well_known_stereotypes(const std::list<dogen::yarn::meta_model::well_known_stereotypes>& v) {
    well_known_stereotypes_ = v;
}

void stereotypes_conversion_result::well_known_stereotypes(const std::list<dogen::yarn::meta_model::well_known_stereotypes>&& v) {
    well_known_stereotypes_ = std::move(v);
}

const std::vector<std::string>& stereotypes_conversion_result::unknown_stereotypes() const {
    return unknown_stereotypes_;
}

std::vector<std::string>& stereotypes_conversion_result::unknown_stereotypes() {
    return unknown_stereotypes_;
}

void stereotypes_conversion_result::unknown_stereotypes(const std::vector<std::string>& v) {
    unknown_stereotypes_ = v;
}

void stereotypes_conversion_result::unknown_stereotypes(const std::vector<std::string>&& v) {
    unknown_stereotypes_ = std::move(v);
}

} } }
