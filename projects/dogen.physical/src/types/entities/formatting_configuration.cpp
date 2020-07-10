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
#include "dogen.physical/types/entities/formatting_configuration.hpp"

namespace dogen::physical::entities {

formatting_configuration::formatting_configuration()
    : styles_(static_cast<dogen::physical::entities::formatting_styles>(0)) { }

formatting_configuration::formatting_configuration(
    const dogen::physical::entities::formatting_styles styles,
    const std::string& input)
    : styles_(styles),
      input_(input) { }

void formatting_configuration::swap(formatting_configuration& other) noexcept {
    using std::swap;
    swap(styles_, other.styles_);
    swap(input_, other.input_);
}

bool formatting_configuration::operator==(const formatting_configuration& rhs) const {
    return styles_ == rhs.styles_ &&
        input_ == rhs.input_;
}

formatting_configuration& formatting_configuration::operator=(formatting_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::physical::entities::formatting_styles formatting_configuration::styles() const {
    return styles_;
}

void formatting_configuration::styles(const dogen::physical::entities::formatting_styles v) {
    styles_ = v;
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
