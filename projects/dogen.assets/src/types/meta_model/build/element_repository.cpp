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
#include "dogen.assets/types/meta_model/build/element_repository.hpp"
#include "dogen.assets/types/meta_model/build/visual_studio_component.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_component>& lhs,
const boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_component>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::assets::meta_model::build {

element_repository::element_repository(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_component> >& visual_studio_components)
    : visual_studio_components_(visual_studio_components) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(visual_studio_components_, other.visual_studio_components_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return visual_studio_components_ == rhs.visual_studio_components_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_component> >& element_repository::visual_studio_components() const {
    return visual_studio_components_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_component> >& element_repository::visual_studio_components() {
    return visual_studio_components_;
}

void element_repository::visual_studio_components(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_component> >& v) {
    visual_studio_components_ = v;
}

void element_repository::visual_studio_components(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_component> >&& v) {
    visual_studio_components_ = std::move(v);
}

}
