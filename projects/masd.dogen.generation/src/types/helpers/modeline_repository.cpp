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
#include "masd.dogen.generation/types/helpers/modeline_repository.hpp"

namespace masd::dogen::generation::helpers {

modeline_repository::modeline_repository(const std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >& modelines_by_group_by_technical_space)
    : modelines_by_group_by_technical_space_(modelines_by_group_by_technical_space) { }

void modeline_repository::swap(modeline_repository& other) noexcept {
    using std::swap;
    swap(modelines_by_group_by_technical_space_, other.modelines_by_group_by_technical_space_);
}

bool modeline_repository::operator==(const modeline_repository& rhs) const {
    return modelines_by_group_by_technical_space_ == rhs.modelines_by_group_by_technical_space_;
}

modeline_repository& modeline_repository::operator=(modeline_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >& modeline_repository::modelines_by_group_by_technical_space() const {
    return modelines_by_group_by_technical_space_;
}

std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >& modeline_repository::modelines_by_group_by_technical_space() {
    return modelines_by_group_by_technical_space_;
}

void modeline_repository::modelines_by_group_by_technical_space(const std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >& v) {
    modelines_by_group_by_technical_space_ = v;
}

void modeline_repository::modelines_by_group_by_technical_space(const std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >&& v) {
    modelines_by_group_by_technical_space_ = std::move(v);
}

}
