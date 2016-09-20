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
#include "dogen/formatters/types/decoration.hpp"

namespace dogen {
namespace formatters {

decoration::decoration(decoration&& rhs)
    : modeline_(std::move(rhs.modeline_)),
      licence_(std::move(rhs.licence_)),
      code_generation_marker_(std::move(rhs.code_generation_marker_)) { }

decoration::decoration(
    const boost::optional<dogen::formatters::modeline>& modeline,
    const boost::optional<dogen::formatters::licence>& licence,
    const std::string& code_generation_marker)
    : modeline_(modeline),
      licence_(licence),
      code_generation_marker_(code_generation_marker) { }

void decoration::swap(decoration& other) noexcept {
    using std::swap;
    swap(modeline_, other.modeline_);
    swap(licence_, other.licence_);
    swap(code_generation_marker_, other.code_generation_marker_);
}

bool decoration::operator==(const decoration& rhs) const {
    return modeline_ == rhs.modeline_ &&
        licence_ == rhs.licence_ &&
        code_generation_marker_ == rhs.code_generation_marker_;
}

decoration& decoration::operator=(decoration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::modeline>& decoration::modeline() const {
    return modeline_;
}

boost::optional<dogen::formatters::modeline>& decoration::modeline() {
    return modeline_;
}

void decoration::modeline(const boost::optional<dogen::formatters::modeline>& v) {
    modeline_ = v;
}

void decoration::modeline(const boost::optional<dogen::formatters::modeline>&& v) {
    modeline_ = std::move(v);
}

const boost::optional<dogen::formatters::licence>& decoration::licence() const {
    return licence_;
}

boost::optional<dogen::formatters::licence>& decoration::licence() {
    return licence_;
}

void decoration::licence(const boost::optional<dogen::formatters::licence>& v) {
    licence_ = v;
}

void decoration::licence(const boost::optional<dogen::formatters::licence>&& v) {
    licence_ = std::move(v);
}

const std::string& decoration::code_generation_marker() const {
    return code_generation_marker_;
}

std::string& decoration::code_generation_marker() {
    return code_generation_marker_;
}

void decoration::code_generation_marker(const std::string& v) {
    code_generation_marker_ = v;
}

void decoration::code_generation_marker(const std::string&& v) {
    code_generation_marker_ = std::move(v);
}

} }
