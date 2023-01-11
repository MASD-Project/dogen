/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.logical/types/helpers/decoration_configuration.hpp"

namespace dogen::logical::helpers {

decoration_configuration::decoration_configuration(decoration_configuration&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      copyright_notices_(std::move(rhs.copyright_notices_)),
      licence_name_(std::move(rhs.licence_name_)),
      modeline_group_name_(std::move(rhs.modeline_group_name_)),
      marker_name_(std::move(rhs.marker_name_)) { }

decoration_configuration::decoration_configuration(
    const boost::optional<bool>& enabled,
    const std::list<std::string>& copyright_notices,
    const dogen::identification::entities::logical_id& licence_name,
    const dogen::identification::entities::logical_id& modeline_group_name,
    const dogen::identification::entities::logical_id& marker_name)
    : enabled_(enabled),
      copyright_notices_(copyright_notices),
      licence_name_(licence_name),
      modeline_group_name_(modeline_group_name),
      marker_name_(marker_name) { }

void decoration_configuration::swap(decoration_configuration& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(copyright_notices_, other.copyright_notices_);
    swap(licence_name_, other.licence_name_);
    swap(modeline_group_name_, other.modeline_group_name_);
    swap(marker_name_, other.marker_name_);
}

bool decoration_configuration::operator==(const decoration_configuration& rhs) const {
    return enabled_ == rhs.enabled_ &&
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

const boost::optional<bool>& decoration_configuration::enabled() const {
    return enabled_;
}

boost::optional<bool>& decoration_configuration::enabled() {
    return enabled_;
}

void decoration_configuration::enabled(const boost::optional<bool>& v) {
    enabled_ = v;
}

void decoration_configuration::enabled(const boost::optional<bool>&& v) {
    enabled_ = std::move(v);
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

const dogen::identification::entities::logical_id& decoration_configuration::licence_name() const {
    return licence_name_;
}

dogen::identification::entities::logical_id& decoration_configuration::licence_name() {
    return licence_name_;
}

void decoration_configuration::licence_name(const dogen::identification::entities::logical_id& v) {
    licence_name_ = v;
}

void decoration_configuration::licence_name(const dogen::identification::entities::logical_id&& v) {
    licence_name_ = std::move(v);
}

const dogen::identification::entities::logical_id& decoration_configuration::modeline_group_name() const {
    return modeline_group_name_;
}

dogen::identification::entities::logical_id& decoration_configuration::modeline_group_name() {
    return modeline_group_name_;
}

void decoration_configuration::modeline_group_name(const dogen::identification::entities::logical_id& v) {
    modeline_group_name_ = v;
}

void decoration_configuration::modeline_group_name(const dogen::identification::entities::logical_id&& v) {
    modeline_group_name_ = std::move(v);
}

const dogen::identification::entities::logical_id& decoration_configuration::marker_name() const {
    return marker_name_;
}

dogen::identification::entities::logical_id& decoration_configuration::marker_name() {
    return marker_name_;
}

void decoration_configuration::marker_name(const dogen::identification::entities::logical_id& v) {
    marker_name_ = v;
}

void decoration_configuration::marker_name(const dogen::identification::entities::logical_id&& v) {
    marker_name_ = std::move(v);
}

}
