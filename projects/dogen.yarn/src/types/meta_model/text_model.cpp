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
#include "dogen.yarn/types/meta_model/text_model.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

text_model::text_model(
    const std::list<dogen::yarn::meta_model::artefact>& artefacts,
    const std::list<boost::filesystem::path>& managed_directories)
    : artefacts_(artefacts),
      managed_directories_(managed_directories) { }

void text_model::swap(text_model& other) noexcept {
    using std::swap;
    swap(artefacts_, other.artefacts_);
    swap(managed_directories_, other.managed_directories_);
}

bool text_model::operator==(const text_model& rhs) const {
    return artefacts_ == rhs.artefacts_ &&
        managed_directories_ == rhs.managed_directories_;
}

text_model& text_model::operator=(text_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::yarn::meta_model::artefact>& text_model::artefacts() const {
    return artefacts_;
}

std::list<dogen::yarn::meta_model::artefact>& text_model::artefacts() {
    return artefacts_;
}

void text_model::artefacts(const std::list<dogen::yarn::meta_model::artefact>& v) {
    artefacts_ = v;
}

void text_model::artefacts(const std::list<dogen::yarn::meta_model::artefact>&& v) {
    artefacts_ = std::move(v);
}

const std::list<boost::filesystem::path>& text_model::managed_directories() const {
    return managed_directories_;
}

std::list<boost::filesystem::path>& text_model::managed_directories() {
    return managed_directories_;
}

void text_model::managed_directories(const std::list<boost::filesystem::path>& v) {
    managed_directories_ = v;
}

void text_model::managed_directories(const std::list<boost::filesystem::path>&& v) {
    managed_directories_ = std::move(v);
}

} } }
