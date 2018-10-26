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
#include "masd.dogen/types/artefact_container.hpp"

namespace masd::dogen {

artefact_container::artefact_container()
    : type_(static_cast<masd::dogen::artefact_group_type>(0)),
      has_diffs_(static_cast<bool>(0)) { }

artefact_container::artefact_container(
    const std::string& name,
    const masd::dogen::artefact_group_type type,
    const std::list<masd::dogen::artefact>& artefacts,
    const bool has_diffs)
    : name_(name),
      type_(type),
      artefacts_(artefacts),
      has_diffs_(has_diffs) { }

void artefact_container::swap(artefact_container& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(type_, other.type_);
    swap(artefacts_, other.artefacts_);
    swap(has_diffs_, other.has_diffs_);
}

bool artefact_container::operator==(const artefact_container& rhs) const {
    return name_ == rhs.name_ &&
        type_ == rhs.type_ &&
        artefacts_ == rhs.artefacts_ &&
        has_diffs_ == rhs.has_diffs_;
}

artefact_container& artefact_container::operator=(artefact_container other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& artefact_container::name() const {
    return name_;
}

std::string& artefact_container::name() {
    return name_;
}

void artefact_container::name(const std::string& v) {
    name_ = v;
}

void artefact_container::name(const std::string&& v) {
    name_ = std::move(v);
}

masd::dogen::artefact_group_type artefact_container::type() const {
    return type_;
}

void artefact_container::type(const masd::dogen::artefact_group_type v) {
    type_ = v;
}

const std::list<masd::dogen::artefact>& artefact_container::artefacts() const {
    return artefacts_;
}

std::list<masd::dogen::artefact>& artefact_container::artefacts() {
    return artefacts_;
}

void artefact_container::artefacts(const std::list<masd::dogen::artefact>& v) {
    artefacts_ = v;
}

void artefact_container::artefacts(const std::list<masd::dogen::artefact>&& v) {
    artefacts_ = std::move(v);
}

bool artefact_container::has_diffs() const {
    return has_diffs_;
}

void artefact_container::has_diffs(const bool v) {
    has_diffs_ = v;
}

}
