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
#include "masd.dogen.extraction/types/modeline.hpp"

namespace masd::dogen::extraction {

modeline::modeline()
    : editor_(static_cast<masd::dogen::extraction::editors>(0)),
      location_(static_cast<masd::dogen::extraction::modeline_locations>(0)) { }

modeline::modeline(
    const std::string& name,
    const masd::dogen::extraction::editors editor,
    const masd::dogen::extraction::modeline_locations location,
    const std::list<masd::dogen::extraction::modeline_field>& fields)
    : name_(name),
      editor_(editor),
      location_(location),
      fields_(fields) { }

void modeline::swap(modeline& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(editor_, other.editor_);
    swap(location_, other.location_);
    swap(fields_, other.fields_);
}

bool modeline::operator==(const modeline& rhs) const {
    return name_ == rhs.name_ &&
        editor_ == rhs.editor_ &&
        location_ == rhs.location_ &&
        fields_ == rhs.fields_;
}

modeline& modeline::operator=(modeline other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& modeline::name() const {
    return name_;
}

std::string& modeline::name() {
    return name_;
}

void modeline::name(const std::string& v) {
    name_ = v;
}

void modeline::name(const std::string&& v) {
    name_ = std::move(v);
}

masd::dogen::extraction::editors modeline::editor() const {
    return editor_;
}

void modeline::editor(const masd::dogen::extraction::editors v) {
    editor_ = v;
}

masd::dogen::extraction::modeline_locations modeline::location() const {
    return location_;
}

void modeline::location(const masd::dogen::extraction::modeline_locations v) {
    location_ = v;
}

const std::list<masd::dogen::extraction::modeline_field>& modeline::fields() const {
    return fields_;
}

std::list<masd::dogen::extraction::modeline_field>& modeline::fields() {
    return fields_;
}

void modeline::fields(const std::list<masd::dogen::extraction::modeline_field>& v) {
    fields_ = v;
}

void modeline::fields(const std::list<masd::dogen::extraction::modeline_field>&& v) {
    fields_ = std::move(v);
}

}
