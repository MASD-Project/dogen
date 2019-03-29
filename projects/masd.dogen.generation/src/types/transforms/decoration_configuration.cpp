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
#include "masd.dogen.generation/types/transforms/decoration_configuration.hpp"

namespace masd::dogen::generation::transforms {

decoration_configuration::decoration_configuration(decoration_configuration&& rhs)
    : generate_decoration_(std::move(rhs.generate_decoration_)),
      copyright_notices_(std::move(rhs.copyright_notices_)),
      licence_name_(std::move(rhs.licence_name_)),
      modeline_group_name_(std::move(rhs.modeline_group_name_)),
      marker_name_(std::move(rhs.marker_name_)) { }

decoration_configuration::decoration_configuration(
    const boost::optional<bool>& generate_decoration,
    const std::list<std::string>& copyright_notices,
    const std::string& licence_name,
    const std::string& modeline_group_name,
    const std::string& marker_name)
    : generate_decoration_(generate_decoration),
      copyright_notices_(copyright_notices),
      licence_name_(licence_name),
      modeline_group_name_(modeline_group_name),
      marker_name_(marker_name) { }

void decoration_configuration::swap(decoration_configuration& other) noexcept {
    using std::swap;
    swap(generate_decoration_, other.generate_decoration_);
    swap(copyright_notices_, other.copyright_notices_);
    swap(licence_name_, other.licence_name_);
    swap(modeline_group_name_, other.modeline_group_name_);
    swap(marker_name_, other.marker_name_);
}

bool decoration_configuration::operator==(const decoration_configuration& rhs) const {
    return generate_decoration_ == rhs.generate_decoration_ &&
        copyright_notices_ == rhs.copyright_notices_ &&
        licence_name_ == rhs.licence_name_ &&
        modeline_group_name_ == rhs.modeline_group_name_ &&
        marker_name_ == rhs.marker_name_;
}

decoration_configuration& decoration_configuration::operator=(decoration_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<bool>& decoration_configuration::generate_decoration() const {
    return generate_decoration_;
}

boost::optional<bool>& decoration_configuration::generate_decoration() {
    return generate_decoration_;
}

void decoration_configuration::generate_decoration(const boost::optional<bool>& v) {
    generate_decoration_ = v;
}

void decoration_configuration::generate_decoration(const boost::optional<bool>&& v) {
    generate_decoration_ = std::move(v);
}

const std::list<std::string>& decoration_configuration::copyright_notices() const {
    return copyright_notices_;
}

std::list<std::string>& decoration_configuration::copyright_notices() {
    return copyright_notices_;
}

void decoration_configuration::copyright_notices(const std::list<std::string>& v) {
    copyright_notices_ = v;
}

void decoration_configuration::copyright_notices(const std::list<std::string>&& v) {
    copyright_notices_ = std::move(v);
}

const std::string& decoration_configuration::licence_name() const {
    return licence_name_;
}

std::string& decoration_configuration::licence_name() {
    return licence_name_;
}

void decoration_configuration::licence_name(const std::string& v) {
    licence_name_ = v;
}

void decoration_configuration::licence_name(const std::string&& v) {
    licence_name_ = std::move(v);
}

const std::string& decoration_configuration::modeline_group_name() const {
    return modeline_group_name_;
}

std::string& decoration_configuration::modeline_group_name() {
    return modeline_group_name_;
}

void decoration_configuration::modeline_group_name(const std::string& v) {
    modeline_group_name_ = v;
}

void decoration_configuration::modeline_group_name(const std::string&& v) {
    modeline_group_name_ = std::move(v);
}

const std::string& decoration_configuration::marker_name() const {
    return marker_name_;
}

std::string& decoration_configuration::marker_name() {
    return marker_name_;
}

void decoration_configuration::marker_name(const std::string& v) {
    marker_name_ = v;
}

void decoration_configuration::marker_name(const std::string&& v) {
    marker_name_ = std::move(v);
}

}
