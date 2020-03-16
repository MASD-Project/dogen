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
#include "dogen.generation/types/transforms/formatting_configuration.hpp"

namespace dogen::generation::transforms {

formatting_configuration::formatting_configuration()
    : style_(static_cast<dogen::generation::entities::formatting_styles>(0)) { }

formatting_configuration::formatting_configuration(
    const dogen::generation::entities::formatting_styles style,
    const std::string& input)
    : style_(style),
      input_(input) { }

void formatting_configuration::swap(formatting_configuration& other) noexcept {
    using std::swap;
    swap(style_, other.style_);
    swap(input_, other.input_);
}

bool formatting_configuration::operator==(const formatting_configuration& rhs) const {
    return style_ == rhs.style_ &&
        input_ == rhs.input_;
}

formatting_configuration& formatting_configuration::operator=(formatting_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::generation::entities::formatting_styles formatting_configuration::style() const {
    return style_;
}

void formatting_configuration::style(const dogen::generation::entities::formatting_styles v) {
    style_ = v;
}

const std::string& formatting_configuration::input() const {
    return input_;
}

std::string& formatting_configuration::input() {
    return input_;
}

void formatting_configuration::input(const std::string& v) {
    input_ = v;
}

void formatting_configuration::input(const std::string&& v) {
    input_ = std::move(v);
}

}
