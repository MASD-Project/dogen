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
#include "dogen/config/types/annotation_settings.hpp"

namespace dogen {
namespace config {

annotation_settings::annotation_settings()
    : generate_preamble_(static_cast<bool>(0)) { }

annotation_settings::annotation_settings(
    const bool generate_preamble,
    const std::list<std::string>& copyright,
    const std::string& licence_name,
    const std::list<std::string>& modeline_group_name,
    const dogen::config::code_generation_marker_settings& code_generation_marker)
    : generate_preamble_(generate_preamble),
      copyright_(copyright),
      licence_name_(licence_name),
      modeline_group_name_(modeline_group_name),
      code_generation_marker_(code_generation_marker) { }

void annotation_settings::swap(annotation_settings& other) noexcept {
    using std::swap;
    swap(generate_preamble_, other.generate_preamble_);
    swap(copyright_, other.copyright_);
    swap(licence_name_, other.licence_name_);
    swap(modeline_group_name_, other.modeline_group_name_);
    swap(code_generation_marker_, other.code_generation_marker_);
}

bool annotation_settings::operator==(const annotation_settings& rhs) const {
    return generate_preamble_ == rhs.generate_preamble_ &&
        copyright_ == rhs.copyright_ &&
        licence_name_ == rhs.licence_name_ &&
        modeline_group_name_ == rhs.modeline_group_name_ &&
        code_generation_marker_ == rhs.code_generation_marker_;
}

annotation_settings& annotation_settings::operator=(annotation_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool annotation_settings::generate_preamble() const {
    return generate_preamble_;
}

void annotation_settings::generate_preamble(const bool v) {
    generate_preamble_ = v;
}

const std::list<std::string>& annotation_settings::copyright() const {
    return copyright_;
}

std::list<std::string>& annotation_settings::copyright() {
    return copyright_;
}

void annotation_settings::copyright(const std::list<std::string>& v) {
    copyright_ = v;
}

void annotation_settings::copyright(const std::list<std::string>&& v) {
    copyright_ = std::move(v);
}

const std::string& annotation_settings::licence_name() const {
    return licence_name_;
}

std::string& annotation_settings::licence_name() {
    return licence_name_;
}

void annotation_settings::licence_name(const std::string& v) {
    licence_name_ = v;
}

void annotation_settings::licence_name(const std::string&& v) {
    licence_name_ = std::move(v);
}

const std::list<std::string>& annotation_settings::modeline_group_name() const {
    return modeline_group_name_;
}

std::list<std::string>& annotation_settings::modeline_group_name() {
    return modeline_group_name_;
}

void annotation_settings::modeline_group_name(const std::list<std::string>& v) {
    modeline_group_name_ = v;
}

void annotation_settings::modeline_group_name(const std::list<std::string>&& v) {
    modeline_group_name_ = std::move(v);
}

const dogen::config::code_generation_marker_settings& annotation_settings::code_generation_marker() const {
    return code_generation_marker_;
}

dogen::config::code_generation_marker_settings& annotation_settings::code_generation_marker() {
    return code_generation_marker_;
}

void annotation_settings::code_generation_marker(const dogen::config::code_generation_marker_settings& v) {
    code_generation_marker_ = v;
}

void annotation_settings::code_generation_marker(const dogen::config::code_generation_marker_settings&& v) {
    code_generation_marker_ = std::move(v);
}

} }