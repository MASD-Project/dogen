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
#include "dogen.org/types/entities/document.hpp"

namespace dogen::org::entities {

document::document(
    const std::list<dogen::org::entities::affiliated_keyword>& affiliated_keywords,
    const std::list<dogen::org::entities::drawer>& drawers,
    const dogen::org::entities::section& section,
    const std::list<dogen::org::entities::headline>& headlines)
    : affiliated_keywords_(affiliated_keywords),
      drawers_(drawers),
      section_(section),
      headlines_(headlines) { }

void document::swap(document& other) noexcept {
    using std::swap;
    swap(affiliated_keywords_, other.affiliated_keywords_);
    swap(drawers_, other.drawers_);
    swap(section_, other.section_);
    swap(headlines_, other.headlines_);
}

bool document::operator==(const document& rhs) const {
    return affiliated_keywords_ == rhs.affiliated_keywords_ &&
        drawers_ == rhs.drawers_ &&
        section_ == rhs.section_ &&
        headlines_ == rhs.headlines_;
}

document& document::operator=(document other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::org::entities::affiliated_keyword>& document::affiliated_keywords() const {
    return affiliated_keywords_;
}

std::list<dogen::org::entities::affiliated_keyword>& document::affiliated_keywords() {
    return affiliated_keywords_;
}

void document::affiliated_keywords(const std::list<dogen::org::entities::affiliated_keyword>& v) {
    affiliated_keywords_ = v;
}

void document::affiliated_keywords(const std::list<dogen::org::entities::affiliated_keyword>&& v) {
    affiliated_keywords_ = std::move(v);
}

const std::list<dogen::org::entities::drawer>& document::drawers() const {
    return drawers_;
}

std::list<dogen::org::entities::drawer>& document::drawers() {
    return drawers_;
}

void document::drawers(const std::list<dogen::org::entities::drawer>& v) {
    drawers_ = v;
}

void document::drawers(const std::list<dogen::org::entities::drawer>&& v) {
    drawers_ = std::move(v);
}

const dogen::org::entities::section& document::section() const {
    return section_;
}

dogen::org::entities::section& document::section() {
    return section_;
}

void document::section(const dogen::org::entities::section& v) {
    section_ = v;
}

void document::section(const dogen::org::entities::section&& v) {
    section_ = std::move(v);
}

const std::list<dogen::org::entities::headline>& document::headlines() const {
    return headlines_;
}

std::list<dogen::org::entities::headline>& document::headlines() {
    return headlines_;
}

void document::headlines(const std::list<dogen::org::entities::headline>& v) {
    headlines_ = v;
}

void document::headlines(const std::list<dogen::org::entities::headline>&& v) {
    headlines_ = std::move(v);
}

}
