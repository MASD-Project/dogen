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
#include "dogen.text.csharp/types/formattables/locator_archetype_configuration.hpp"

namespace dogen::text::csharp::formattables {

locator_archetype_configuration::locator_archetype_configuration(
    const std::string& facet_directory,
    const std::string& facet_postfix,
    const std::string& archetype_postfix)
    : facet_directory_(facet_directory),
      facet_postfix_(facet_postfix),
      archetype_postfix_(archetype_postfix) { }

void locator_archetype_configuration::swap(locator_archetype_configuration& other) noexcept {
    using std::swap;
    swap(facet_directory_, other.facet_directory_);
    swap(facet_postfix_, other.facet_postfix_);
    swap(archetype_postfix_, other.archetype_postfix_);
}

bool locator_archetype_configuration::operator==(const locator_archetype_configuration& rhs) const {
    return facet_directory_ == rhs.facet_directory_ &&
        facet_postfix_ == rhs.facet_postfix_ &&
        archetype_postfix_ == rhs.archetype_postfix_;
}

locator_archetype_configuration& locator_archetype_configuration::operator=(locator_archetype_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& locator_archetype_configuration::facet_directory() const {
    return facet_directory_;
}

std::string& locator_archetype_configuration::facet_directory() {
    return facet_directory_;
}

void locator_archetype_configuration::facet_directory(const std::string& v) {
    facet_directory_ = v;
}

void locator_archetype_configuration::facet_directory(const std::string&& v) {
    facet_directory_ = std::move(v);
}

const std::string& locator_archetype_configuration::facet_postfix() const {
    return facet_postfix_;
}

std::string& locator_archetype_configuration::facet_postfix() {
    return facet_postfix_;
}

void locator_archetype_configuration::facet_postfix(const std::string& v) {
    facet_postfix_ = v;
}

void locator_archetype_configuration::facet_postfix(const std::string&& v) {
    facet_postfix_ = std::move(v);
}

const std::string& locator_archetype_configuration::archetype_postfix() const {
    return archetype_postfix_;
}

std::string& locator_archetype_configuration::archetype_postfix() {
    return archetype_postfix_;
}

void locator_archetype_configuration::archetype_postfix(const std::string& v) {
    archetype_postfix_ = v;
}

void locator_archetype_configuration::archetype_postfix(const std::string&& v) {
    archetype_postfix_ = std::move(v);
}

}
