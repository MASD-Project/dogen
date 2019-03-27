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
#include "masd.dogen.coding/types/meta_model/decoration.hpp"

namespace masd::dogen::coding::meta_model {

decoration::decoration(
    const std::string& top_modeline,
    const std::string& bottom_modeline,
    const std::list<std::string>& copyrights,
    const std::string& licence_short_form,
    const std::string& generation_marker)
    : top_modeline_(top_modeline),
      bottom_modeline_(bottom_modeline),
      copyrights_(copyrights),
      licence_short_form_(licence_short_form),
      generation_marker_(generation_marker) { }

void decoration::swap(decoration& other) noexcept {
    using std::swap;
    swap(top_modeline_, other.top_modeline_);
    swap(bottom_modeline_, other.bottom_modeline_);
    swap(copyrights_, other.copyrights_);
    swap(licence_short_form_, other.licence_short_form_);
    swap(generation_marker_, other.generation_marker_);
}

bool decoration::operator==(const decoration& rhs) const {
    return top_modeline_ == rhs.top_modeline_ &&
        bottom_modeline_ == rhs.bottom_modeline_ &&
        copyrights_ == rhs.copyrights_ &&
        licence_short_form_ == rhs.licence_short_form_ &&
        generation_marker_ == rhs.generation_marker_;
}

decoration& decoration::operator=(decoration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& decoration::top_modeline() const {
    return top_modeline_;
}

std::string& decoration::top_modeline() {
    return top_modeline_;
}

void decoration::top_modeline(const std::string& v) {
    top_modeline_ = v;
}

void decoration::top_modeline(const std::string&& v) {
    top_modeline_ = std::move(v);
}

const std::string& decoration::bottom_modeline() const {
    return bottom_modeline_;
}

std::string& decoration::bottom_modeline() {
    return bottom_modeline_;
}

void decoration::bottom_modeline(const std::string& v) {
    bottom_modeline_ = v;
}

void decoration::bottom_modeline(const std::string&& v) {
    bottom_modeline_ = std::move(v);
}

const std::list<std::string>& decoration::copyrights() const {
    return copyrights_;
}

std::list<std::string>& decoration::copyrights() {
    return copyrights_;
}

void decoration::copyrights(const std::list<std::string>& v) {
    copyrights_ = v;
}

void decoration::copyrights(const std::list<std::string>&& v) {
    copyrights_ = std::move(v);
}

const std::string& decoration::licence_short_form() const {
    return licence_short_form_;
}

std::string& decoration::licence_short_form() {
    return licence_short_form_;
}

void decoration::licence_short_form(const std::string& v) {
    licence_short_form_ = v;
}

void decoration::licence_short_form(const std::string&& v) {
    licence_short_form_ = std::move(v);
}

const std::string& decoration::generation_marker() const {
    return generation_marker_;
}

std::string& decoration::generation_marker() {
    return generation_marker_;
}

void decoration::generation_marker(const std::string& v) {
    generation_marker_ = v;
}

void decoration::generation_marker(const std::string&& v) {
    generation_marker_ = std::move(v);
}

}
