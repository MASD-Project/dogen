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
#include "dogen/formatters/types/decoration_configuration.hpp"

namespace dogen {
namespace formatters {

decoration_configuration::decoration_configuration()
    : generate_preamble_(static_cast<bool>(0)) { }

decoration_configuration::decoration_configuration(decoration_configuration&& rhs)
    : generate_preamble_(std::move(rhs.generate_preamble_)),
      modeline_(std::move(rhs.modeline_)),
      licence_(std::move(rhs.licence_)),
      code_generation_marker_(std::move(rhs.code_generation_marker_)) { }

decoration_configuration::decoration_configuration(
    const bool generate_preamble,
    const boost::optional<dogen::formatters::modeline>& modeline,
    const boost::optional<dogen::formatters::licence>& licence,
    const std::string& code_generation_marker)
    : generate_preamble_(generate_preamble),
      modeline_(modeline),
      licence_(licence),
      code_generation_marker_(code_generation_marker) { }

void decoration_configuration::swap(decoration_configuration& other) noexcept {
    using std::swap;
    swap(generate_preamble_, other.generate_preamble_);
    swap(modeline_, other.modeline_);
    swap(licence_, other.licence_);
    swap(code_generation_marker_, other.code_generation_marker_);
}

bool decoration_configuration::operator==(const decoration_configuration& rhs) const {
    return generate_preamble_ == rhs.generate_preamble_ &&
        modeline_ == rhs.modeline_ &&
        licence_ == rhs.licence_ &&
        code_generation_marker_ == rhs.code_generation_marker_;
}

decoration_configuration& decoration_configuration::operator=(decoration_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool decoration_configuration::generate_preamble() const {
    return generate_preamble_;
}

void decoration_configuration::generate_preamble(const bool v) {
    generate_preamble_ = v;
}

const boost::optional<dogen::formatters::modeline>& decoration_configuration::modeline() const {
    return modeline_;
}

boost::optional<dogen::formatters::modeline>& decoration_configuration::modeline() {
    return modeline_;
}

void decoration_configuration::modeline(const boost::optional<dogen::formatters::modeline>& v) {
    modeline_ = v;
}

void decoration_configuration::modeline(const boost::optional<dogen::formatters::modeline>&& v) {
    modeline_ = std::move(v);
}

const boost::optional<dogen::formatters::licence>& decoration_configuration::licence() const {
    return licence_;
}

boost::optional<dogen::formatters::licence>& decoration_configuration::licence() {
    return licence_;
}

void decoration_configuration::licence(const boost::optional<dogen::formatters::licence>& v) {
    licence_ = v;
}

void decoration_configuration::licence(const boost::optional<dogen::formatters::licence>&& v) {
    licence_ = std::move(v);
}

const std::string& decoration_configuration::code_generation_marker() const {
    return code_generation_marker_;
}

std::string& decoration_configuration::code_generation_marker() {
    return code_generation_marker_;
}

void decoration_configuration::code_generation_marker(const std::string& v) {
    code_generation_marker_ = v;
}

void decoration_configuration::code_generation_marker(const std::string&& v) {
    code_generation_marker_ = std::move(v);
}

} }
