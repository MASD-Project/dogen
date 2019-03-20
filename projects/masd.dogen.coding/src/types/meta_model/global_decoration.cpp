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
#include "masd.dogen.coding/types/meta_model/global_decoration.hpp"

namespace masd::dogen::coding::meta_model {

global_decoration::global_decoration(
    const std::list<std::string>& copyrights,
    const std::string& licence_short_form,
    const std::string& licence_long_form,
    const std::string& generation_marker)
    : copyrights_(copyrights),
      licence_short_form_(licence_short_form),
      licence_long_form_(licence_long_form),
      generation_marker_(generation_marker) { }

void global_decoration::swap(global_decoration& other) noexcept {
    using std::swap;
    swap(copyrights_, other.copyrights_);
    swap(licence_short_form_, other.licence_short_form_);
    swap(licence_long_form_, other.licence_long_form_);
    swap(generation_marker_, other.generation_marker_);
}

bool global_decoration::operator==(const global_decoration& rhs) const {
    return copyrights_ == rhs.copyrights_ &&
        licence_short_form_ == rhs.licence_short_form_ &&
        licence_long_form_ == rhs.licence_long_form_ &&
        generation_marker_ == rhs.generation_marker_;
}

global_decoration& global_decoration::operator=(global_decoration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& global_decoration::copyrights() const {
    return copyrights_;
}

std::list<std::string>& global_decoration::copyrights() {
    return copyrights_;
}

void global_decoration::copyrights(const std::list<std::string>& v) {
    copyrights_ = v;
}

void global_decoration::copyrights(const std::list<std::string>&& v) {
    copyrights_ = std::move(v);
}

const std::string& global_decoration::licence_short_form() const {
    return licence_short_form_;
}

std::string& global_decoration::licence_short_form() {
    return licence_short_form_;
}

void global_decoration::licence_short_form(const std::string& v) {
    licence_short_form_ = v;
}

void global_decoration::licence_short_form(const std::string&& v) {
    licence_short_form_ = std::move(v);
}

const std::string& global_decoration::licence_long_form() const {
    return licence_long_form_;
}

std::string& global_decoration::licence_long_form() {
    return licence_long_form_;
}

void global_decoration::licence_long_form(const std::string& v) {
    licence_long_form_ = v;
}

void global_decoration::licence_long_form(const std::string&& v) {
    licence_long_form_ = std::move(v);
}

const std::string& global_decoration::generation_marker() const {
    return generation_marker_;
}

std::string& global_decoration::generation_marker() {
    return generation_marker_;
}

void global_decoration::generation_marker(const std::string& v) {
    generation_marker_ = v;
}

void global_decoration::generation_marker(const std::string&& v) {
    generation_marker_ = std::move(v);
}

}
