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
#include "dogen.physical/types/entities/archetype_properties.hpp"

namespace dogen::physical::entities {

archetype_properties::archetype_properties()
    : enabled_(static_cast<bool>(0)) { }

archetype_properties::archetype_properties(archetype_properties&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      overwrite_(std::move(rhs.overwrite_)),
      postfix_(std::move(rhs.postfix_)),
      computed_postfix_(std::move(rhs.computed_postfix_)),
      backend_properties_(std::move(rhs.backend_properties_)),
      facet_properties_(std::move(rhs.facet_properties_)),
      part_properties_(std::move(rhs.part_properties_)) { }

archetype_properties::archetype_properties(
    const bool enabled,
    const boost::optional<bool>& overwrite,
    const std::string& postfix,
    const std::string& computed_postfix,
    const dogen::physical::entities::backend_properties& backend_properties,
    const dogen::physical::entities::facet_properties& facet_properties,
    const dogen::physical::entities::part_properties& part_properties)
    : enabled_(enabled),
      overwrite_(overwrite),
      postfix_(postfix),
      computed_postfix_(computed_postfix),
      backend_properties_(backend_properties),
      facet_properties_(facet_properties),
      part_properties_(part_properties) { }

void archetype_properties::swap(archetype_properties& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(overwrite_, other.overwrite_);
    swap(postfix_, other.postfix_);
    swap(computed_postfix_, other.computed_postfix_);
    swap(backend_properties_, other.backend_properties_);
    swap(facet_properties_, other.facet_properties_);
    swap(part_properties_, other.part_properties_);
}

bool archetype_properties::operator==(const archetype_properties& rhs) const {
    return enabled_ == rhs.enabled_ &&
        overwrite_ == rhs.overwrite_ &&
        postfix_ == rhs.postfix_ &&
        computed_postfix_ == rhs.computed_postfix_ &&
        backend_properties_ == rhs.backend_properties_ &&
        facet_properties_ == rhs.facet_properties_ &&
        part_properties_ == rhs.part_properties_;
}

archetype_properties& archetype_properties::operator=(archetype_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool archetype_properties::enabled() const {
    return enabled_;
}

void archetype_properties::enabled(const bool v) {
    enabled_ = v;
}

const boost::optional<bool>& archetype_properties::overwrite() const {
    return overwrite_;
}

boost::optional<bool>& archetype_properties::overwrite() {
    return overwrite_;
}

void archetype_properties::overwrite(const boost::optional<bool>& v) {
    overwrite_ = v;
}

void archetype_properties::overwrite(const boost::optional<bool>&& v) {
    overwrite_ = std::move(v);
}

const std::string& archetype_properties::postfix() const {
    return postfix_;
}

std::string& archetype_properties::postfix() {
    return postfix_;
}

void archetype_properties::postfix(const std::string& v) {
    postfix_ = v;
}

void archetype_properties::postfix(const std::string&& v) {
    postfix_ = std::move(v);
}

const std::string& archetype_properties::computed_postfix() const {
    return computed_postfix_;
}

std::string& archetype_properties::computed_postfix() {
    return computed_postfix_;
}

void archetype_properties::computed_postfix(const std::string& v) {
    computed_postfix_ = v;
}

void archetype_properties::computed_postfix(const std::string&& v) {
    computed_postfix_ = std::move(v);
}

const dogen::physical::entities::backend_properties& archetype_properties::backend_properties() const {
    return backend_properties_;
}

dogen::physical::entities::backend_properties& archetype_properties::backend_properties() {
    return backend_properties_;
}

void archetype_properties::backend_properties(const dogen::physical::entities::backend_properties& v) {
    backend_properties_ = v;
}

void archetype_properties::backend_properties(const dogen::physical::entities::backend_properties&& v) {
    backend_properties_ = std::move(v);
}

const dogen::physical::entities::facet_properties& archetype_properties::facet_properties() const {
    return facet_properties_;
}

dogen::physical::entities::facet_properties& archetype_properties::facet_properties() {
    return facet_properties_;
}

void archetype_properties::facet_properties(const dogen::physical::entities::facet_properties& v) {
    facet_properties_ = v;
}

void archetype_properties::facet_properties(const dogen::physical::entities::facet_properties&& v) {
    facet_properties_ = std::move(v);
}

const dogen::physical::entities::part_properties& archetype_properties::part_properties() const {
    return part_properties_;
}

dogen::physical::entities::part_properties& archetype_properties::part_properties() {
    return part_properties_;
}

void archetype_properties::part_properties(const dogen::physical::entities::part_properties& v) {
    part_properties_ = v;
}

void archetype_properties::part_properties(const dogen::physical::entities::part_properties&& v) {
    part_properties_ = std::move(v);
}

}
