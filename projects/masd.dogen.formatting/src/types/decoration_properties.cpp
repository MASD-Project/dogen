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
#include "dogen.formatting/types/decoration_properties.hpp"

namespace dogen::formatting {

decoration_properties::decoration_properties()
    : generate_decoration_(static_cast<bool>(0)) { }

decoration_properties::decoration_properties(decoration_properties&& rhs)
    : generate_decoration_(std::move(rhs.generate_decoration_)),
      modeline_(std::move(rhs.modeline_)),
      licence_(std::move(rhs.licence_)),
      code_generation_marker_(std::move(rhs.code_generation_marker_)) { }

decoration_properties::decoration_properties(
    const bool generate_decoration,
    const boost::optional<dogen::formatting::modeline>& modeline,
    const boost::optional<dogen::formatting::licence>& licence,
    const std::string& code_generation_marker)
    : generate_decoration_(generate_decoration),
      modeline_(modeline),
      licence_(licence),
      code_generation_marker_(code_generation_marker) { }

void decoration_properties::swap(decoration_properties& other) noexcept {
    using std::swap;
    swap(generate_decoration_, other.generate_decoration_);
    swap(modeline_, other.modeline_);
    swap(licence_, other.licence_);
    swap(code_generation_marker_, other.code_generation_marker_);
}

bool decoration_properties::operator==(const decoration_properties& rhs) const {
    return generate_decoration_ == rhs.generate_decoration_ &&
        modeline_ == rhs.modeline_ &&
        licence_ == rhs.licence_ &&
        code_generation_marker_ == rhs.code_generation_marker_;
}

decoration_properties& decoration_properties::operator=(decoration_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool decoration_properties::generate_decoration() const {
    return generate_decoration_;
}

void decoration_properties::generate_decoration(const bool v) {
    generate_decoration_ = v;
}

const boost::optional<dogen::formatting::modeline>& decoration_properties::modeline() const {
    return modeline_;
}

boost::optional<dogen::formatting::modeline>& decoration_properties::modeline() {
    return modeline_;
}

void decoration_properties::modeline(const boost::optional<dogen::formatting::modeline>& v) {
    modeline_ = v;
}

void decoration_properties::modeline(const boost::optional<dogen::formatting::modeline>&& v) {
    modeline_ = std::move(v);
}

const boost::optional<dogen::formatting::licence>& decoration_properties::licence() const {
    return licence_;
}

boost::optional<dogen::formatting::licence>& decoration_properties::licence() {
    return licence_;
}

void decoration_properties::licence(const boost::optional<dogen::formatting::licence>& v) {
    licence_ = v;
}

void decoration_properties::licence(const boost::optional<dogen::formatting::licence>&& v) {
    licence_ = std::move(v);
}

const std::string& decoration_properties::code_generation_marker() const {
    return code_generation_marker_;
}

std::string& decoration_properties::code_generation_marker() {
    return code_generation_marker_;
}

void decoration_properties::code_generation_marker(const std::string& v) {
    code_generation_marker_ = v;
}

void decoration_properties::code_generation_marker(const std::string&& v) {
    code_generation_marker_ = std::move(v);
}

}
