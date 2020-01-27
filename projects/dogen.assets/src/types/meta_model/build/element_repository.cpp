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
#include "dogen.assets/types/meta_model/build/visual_studio_project.hpp"
#include "dogen.assets/types/meta_model/build/visual_studio_solution.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_project>& lhs,
const boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_project>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_solution>& lhs,
const boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_solution>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::assets::meta_model::build {

element_repository::element_repository(
    const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_project> >& visual_studio_projects,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_solution> >& visual_studio_solutions)
    : visual_studio_projects_(visual_studio_projects),
      visual_studio_solutions_(visual_studio_solutions) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(visual_studio_projects_, other.visual_studio_projects_);
    swap(visual_studio_solutions_, other.visual_studio_solutions_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return visual_studio_projects_ == rhs.visual_studio_projects_ &&
        visual_studio_solutions_ == rhs.visual_studio_solutions_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_project> >& element_repository::visual_studio_projects() const {
    return visual_studio_projects_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_project> >& element_repository::visual_studio_projects() {
    return visual_studio_projects_;
}

void element_repository::visual_studio_projects(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_project> >& v) {
    visual_studio_projects_ = v;
}

void element_repository::visual_studio_projects(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_project> >&& v) {
    visual_studio_projects_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_solution> >& element_repository::visual_studio_solutions() const {
    return visual_studio_solutions_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_solution> >& element_repository::visual_studio_solutions() {
    return visual_studio_solutions_;
}

void element_repository::visual_studio_solutions(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_solution> >& v) {
    visual_studio_solutions_ = v;
}

void element_repository::visual_studio_solutions(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::build::visual_studio_solution> >&& v) {
    visual_studio_solutions_ = std::move(v);
}

}
