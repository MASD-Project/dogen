/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml_to_om/types/context.hpp"

namespace dogen {
namespace sml_to_om {

context::context(const dogen::om::cpp_project& project)
    : project_(project) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(project_, other.project_);
}

bool context::operator==(const context& rhs) const {
    return project_ == rhs.project_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::om::cpp_project& context::project() const {
    return project_;
}

dogen::om::cpp_project& context::project() {
    return project_;
}

void context::project(const dogen::om::cpp_project& v) {
    project_ = v;
}

void context::project(const dogen::om::cpp_project&& v) {
    project_ = std::move(v);
}

} }