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
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_configuration.hpp"

namespace masd::dogen::generation::cpp::fabric {

visual_studio_configuration::visual_studio_configuration(
    const std::string& project_solution_guid,
    const std::string& project_guid)
    : project_solution_guid_(project_solution_guid),
      project_guid_(project_guid) { }

void visual_studio_configuration::swap(visual_studio_configuration& other) noexcept {
    using std::swap;
    swap(project_solution_guid_, other.project_solution_guid_);
    swap(project_guid_, other.project_guid_);
}

bool visual_studio_configuration::operator==(const visual_studio_configuration& rhs) const {
    return project_solution_guid_ == rhs.project_solution_guid_ &&
        project_guid_ == rhs.project_guid_;
}

visual_studio_configuration& visual_studio_configuration::operator=(visual_studio_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& visual_studio_configuration::project_solution_guid() const {
    return project_solution_guid_;
}

std::string& visual_studio_configuration::project_solution_guid() {
    return project_solution_guid_;
}

void visual_studio_configuration::project_solution_guid(const std::string& v) {
    project_solution_guid_ = v;
}

void visual_studio_configuration::project_solution_guid(const std::string&& v) {
    project_solution_guid_ = std::move(v);
}

const std::string& visual_studio_configuration::project_guid() const {
    return project_guid_;
}

std::string& visual_studio_configuration::project_guid() {
    return project_guid_;
}

void visual_studio_configuration::project_guid(const std::string& v) {
    project_guid_ = v;
}

void visual_studio_configuration::project_guid(const std::string&& v) {
    project_guid_ = std::move(v);
}

}
