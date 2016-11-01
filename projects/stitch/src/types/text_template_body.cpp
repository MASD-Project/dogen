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
#include "dogen/stitch/types/text_template_body.hpp"

namespace dogen {
namespace stitch {

text_template_body::text_template_body(
    const dogen::annotations::scribble_group& scribble_group,
    const std::list<dogen::stitch::line>& lines)
    : scribble_group_(scribble_group),
      lines_(lines) { }

void text_template_body::swap(text_template_body& other) noexcept {
    using std::swap;
    swap(scribble_group_, other.scribble_group_);
    swap(lines_, other.lines_);
}

bool text_template_body::operator==(const text_template_body& rhs) const {
    return scribble_group_ == rhs.scribble_group_ &&
        lines_ == rhs.lines_;
}

text_template_body& text_template_body::operator=(text_template_body other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::annotations::scribble_group& text_template_body::scribble_group() const {
    return scribble_group_;
}

dogen::annotations::scribble_group& text_template_body::scribble_group() {
    return scribble_group_;
}

void text_template_body::scribble_group(const dogen::annotations::scribble_group& v) {
    scribble_group_ = v;
}

void text_template_body::scribble_group(const dogen::annotations::scribble_group&& v) {
    scribble_group_ = std::move(v);
}

const std::list<dogen::stitch::line>& text_template_body::lines() const {
    return lines_;
}

std::list<dogen::stitch::line>& text_template_body::lines() {
    return lines_;
}

void text_template_body::lines(const std::list<dogen::stitch::line>& v) {
    lines_ = v;
}

void text_template_body::lines(const std::list<dogen::stitch::line>&& v) {
    lines_ = std::move(v);
}

} }
