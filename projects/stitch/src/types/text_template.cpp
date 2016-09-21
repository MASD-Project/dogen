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
#include "dogen/stitch/types/text_template.hpp"

namespace dogen {
namespace stitch {

text_template::text_template(
    const dogen::stitch::configuration& configuration,
    const dogen::dynamic::object& extensions,
    const std::list<dogen::stitch::line>& lines)
    : configuration_(configuration),
      extensions_(extensions),
      lines_(lines) { }

void text_template::swap(text_template& other) noexcept {
    using std::swap;
    swap(configuration_, other.configuration_);
    swap(extensions_, other.extensions_);
    swap(lines_, other.lines_);
}

bool text_template::operator==(const text_template& rhs) const {
    return configuration_ == rhs.configuration_ &&
        extensions_ == rhs.extensions_ &&
        lines_ == rhs.lines_;
}

text_template& text_template::operator=(text_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::stitch::configuration& text_template::configuration() const {
    return configuration_;
}

dogen::stitch::configuration& text_template::configuration() {
    return configuration_;
}

void text_template::configuration(const dogen::stitch::configuration& v) {
    configuration_ = v;
}

void text_template::configuration(const dogen::stitch::configuration&& v) {
    configuration_ = std::move(v);
}

const dogen::dynamic::object& text_template::extensions() const {
    return extensions_;
}

dogen::dynamic::object& text_template::extensions() {
    return extensions_;
}

void text_template::extensions(const dogen::dynamic::object& v) {
    extensions_ = v;
}

void text_template::extensions(const dogen::dynamic::object&& v) {
    extensions_ = std::move(v);
}

const std::list<dogen::stitch::line>& text_template::lines() const {
    return lines_;
}

std::list<dogen::stitch::line>& text_template::lines() {
    return lines_;
}

void text_template::lines(const std::list<dogen::stitch::line>& v) {
    lines_ = v;
}

void text_template::lines(const std::list<dogen::stitch::line>&& v) {
    lines_ = std::move(v);
}

} }
