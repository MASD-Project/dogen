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
#include "dogen/annotations/types/scribble.hpp"

namespace dogen {
namespace annotations {

scribble::scribble()
    : scope_(static_cast<dogen::annotations::scope_types>(0)) { }

scribble::scribble(
    const std::list<std::pair<std::string, std::string> >& entries,
    const dogen::annotations::scope_types scope)
    : entries_(entries),
      scope_(scope) { }

void scribble::swap(scribble& other) noexcept {
    using std::swap;
    swap(entries_, other.entries_);
    swap(scope_, other.scope_);
}

bool scribble::operator==(const scribble& rhs) const {
    return entries_ == rhs.entries_ &&
        scope_ == rhs.scope_;
}

scribble& scribble::operator=(scribble other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::pair<std::string, std::string> >& scribble::entries() const {
    return entries_;
}

std::list<std::pair<std::string, std::string> >& scribble::entries() {
    return entries_;
}

void scribble::entries(const std::list<std::pair<std::string, std::string> >& v) {
    entries_ = v;
}

void scribble::entries(const std::list<std::pair<std::string, std::string> >&& v) {
    entries_ = std::move(v);
}

dogen::annotations::scope_types scribble::scope() const {
    return scope_;
}

void scribble::scope(const dogen::annotations::scope_types v) {
    scope_ = v;
}

} }
