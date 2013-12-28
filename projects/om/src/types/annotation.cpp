/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/om/types/annotation.hpp"

namespace dogen {
namespace om {

annotation::annotation(annotation&& rhs)
    : modeline_(std::move(rhs.modeline_)),
      licence_(std::move(rhs.licence_)),
      code_generation_marker_(std::move(rhs.code_generation_marker_)) { }

annotation::annotation(
    const boost::optional<dogen::om::modeline>& modeline,
    const boost::optional<dogen::om::licence>& licence,
    const std::string& code_generation_marker)
    : modeline_(modeline),
      licence_(licence),
      code_generation_marker_(code_generation_marker) { }

void annotation::swap(annotation& other) noexcept {
    using std::swap;
    swap(modeline_, other.modeline_);
    swap(licence_, other.licence_);
    swap(code_generation_marker_, other.code_generation_marker_);
}

bool annotation::operator==(const annotation& rhs) const {
    return modeline_ == rhs.modeline_ &&
        licence_ == rhs.licence_ &&
        code_generation_marker_ == rhs.code_generation_marker_;
}

annotation& annotation::operator=(annotation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::om::modeline>& annotation::modeline() const {
    return modeline_;
}

boost::optional<dogen::om::modeline>& annotation::modeline() {
    return modeline_;
}

void annotation::modeline(const boost::optional<dogen::om::modeline>& v) {
    modeline_ = v;
}

void annotation::modeline(const boost::optional<dogen::om::modeline>&& v) {
    modeline_ = std::move(v);
}

const boost::optional<dogen::om::licence>& annotation::licence() const {
    return licence_;
}

boost::optional<dogen::om::licence>& annotation::licence() {
    return licence_;
}

void annotation::licence(const boost::optional<dogen::om::licence>& v) {
    licence_ = v;
}

void annotation::licence(const boost::optional<dogen::om::licence>&& v) {
    licence_ = std::move(v);
}

const std::string& annotation::code_generation_marker() const {
    return code_generation_marker_;
}

std::string& annotation::code_generation_marker() {
    return code_generation_marker_;
}

void annotation::code_generation_marker(const std::string& v) {
    code_generation_marker_ = v;
}

void annotation::code_generation_marker(const std::string&& v) {
    code_generation_marker_ = std::move(v);
}

} }