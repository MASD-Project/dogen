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
#include "masd.dogen.dia/types/attribute.hpp"

namespace masd::dogen::dia {

attribute::attribute(
    const std::string& name,
    const std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >& values)
    : name_(name),
      values_(values) { }

void attribute::swap(attribute& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(values_, other.values_);
}

bool attribute::operator==(const attribute& rhs) const {
    return name_ == rhs.name_ &&
        values_ == rhs.values_;
}

attribute& attribute::operator=(attribute other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& attribute::name() const {
    return name_;
}

std::string& attribute::name() {
    return name_;
}

void attribute::name(const std::string& v) {
    name_ = v;
}

void attribute::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >& attribute::values() const {
    return values_;
}

std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >& attribute::values() {
    return values_;
}

void attribute::values(const std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >& v) {
    values_ = v;
}

void attribute::values(const std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >&& v) {
    values_ = std::move(v);
}

}
