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
#include "dogen.text.cpp/types/formattables/artefact_properties.hpp"

namespace dogen::text::cpp::formattables {

artefact_properties::artefact_properties(const std::list<std::string>& inclusion_dependencies)
    : inclusion_dependencies_(inclusion_dependencies) { }

void artefact_properties::swap(artefact_properties& other) noexcept {
    using std::swap;
    swap(inclusion_dependencies_, other.inclusion_dependencies_);
}

bool artefact_properties::operator==(const artefact_properties& rhs) const {
    return inclusion_dependencies_ == rhs.inclusion_dependencies_;
}

artefact_properties& artefact_properties::operator=(artefact_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& artefact_properties::inclusion_dependencies() const {
    return inclusion_dependencies_;
}

std::list<std::string>& artefact_properties::inclusion_dependencies() {
    return inclusion_dependencies_;
}

void artefact_properties::inclusion_dependencies(const std::list<std::string>& v) {
    inclusion_dependencies_ = v;
}

void artefact_properties::inclusion_dependencies(const std::list<std::string>&& v) {
    inclusion_dependencies_ = std::move(v);
}

}
