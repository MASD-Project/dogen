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
#include "dogen.text.csharp/types/formattables/artefact_properties.hpp"

namespace dogen::text::csharp::formattables {

artefact_properties::artefact_properties(artefact_properties&& rhs)
    : relative_path_(std::move(rhs.relative_path_)),
      using_dependencies_(std::move(rhs.using_dependencies_)) { }

artefact_properties::artefact_properties(
    const boost::filesystem::path& relative_path,
    const std::list<std::string>& using_dependencies)
    : relative_path_(relative_path),
      using_dependencies_(using_dependencies) { }

void artefact_properties::swap(artefact_properties& other) noexcept {
    using std::swap;
    swap(relative_path_, other.relative_path_);
    swap(using_dependencies_, other.using_dependencies_);
}

bool artefact_properties::operator==(const artefact_properties& rhs) const {
    return relative_path_ == rhs.relative_path_ &&
        using_dependencies_ == rhs.using_dependencies_;
}

artefact_properties& artefact_properties::operator=(artefact_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& artefact_properties::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& artefact_properties::relative_path() {
    return relative_path_;
}

void artefact_properties::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void artefact_properties::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

const std::list<std::string>& artefact_properties::using_dependencies() const {
    return using_dependencies_;
}

std::list<std::string>& artefact_properties::using_dependencies() {
    return using_dependencies_;
}

void artefact_properties::using_dependencies(const std::list<std::string>& v) {
    using_dependencies_ = v;
}

void artefact_properties::using_dependencies(const std::list<std::string>&& v) {
    using_dependencies_ = std::move(v);
}

}
