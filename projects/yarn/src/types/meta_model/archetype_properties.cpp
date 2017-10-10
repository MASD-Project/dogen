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
#include "dogen/yarn/types/meta_model/archetype_properties.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

archetype_properties::archetype_properties()
    : enabled_(static_cast<bool>(0)),
      overwrite_(static_cast<bool>(0)) { }

archetype_properties::archetype_properties(
    const bool enabled,
    const bool overwrite,
    const std::string& facet_directory,
    const std::string& postfix)
    : enabled_(enabled),
      overwrite_(overwrite),
      facet_directory_(facet_directory),
      postfix_(postfix) { }

void archetype_properties::swap(archetype_properties& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(overwrite_, other.overwrite_);
    swap(facet_directory_, other.facet_directory_);
    swap(postfix_, other.postfix_);
}

bool archetype_properties::operator==(const archetype_properties& rhs) const {
    return enabled_ == rhs.enabled_ &&
        overwrite_ == rhs.overwrite_ &&
        facet_directory_ == rhs.facet_directory_ &&
        postfix_ == rhs.postfix_;
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

bool archetype_properties::overwrite() const {
    return overwrite_;
}

void archetype_properties::overwrite(const bool v) {
    overwrite_ = v;
}

const std::string& archetype_properties::facet_directory() const {
    return facet_directory_;
}

std::string& archetype_properties::facet_directory() {
    return facet_directory_;
}

void archetype_properties::facet_directory(const std::string& v) {
    facet_directory_ = v;
}

void archetype_properties::facet_directory(const std::string&& v) {
    facet_directory_ = std::move(v);
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

} } }
