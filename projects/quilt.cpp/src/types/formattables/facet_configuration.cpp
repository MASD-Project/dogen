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
#include "dogen/quilt.cpp/types/formattables/facet_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

facet_configuration::facet_configuration()
    : enabled_(static_cast<bool>(0)) { }

facet_configuration::facet_configuration(
    const bool enabled,
    const std::string& directory)
    : enabled_(enabled),
      directory_(directory) { }

void facet_configuration::swap(facet_configuration& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(directory_, other.directory_);
}

bool facet_configuration::operator==(const facet_configuration& rhs) const {
    return enabled_ == rhs.enabled_ &&
        directory_ == rhs.directory_;
}

facet_configuration& facet_configuration::operator=(facet_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool facet_configuration::enabled() const {
    return enabled_;
}

void facet_configuration::enabled(const bool v) {
    enabled_ = v;
}

const std::string& facet_configuration::directory() const {
    return directory_;
}

std::string& facet_configuration::directory() {
    return directory_;
}

void facet_configuration::directory(const std::string& v) {
    directory_ = v;
}

void facet_configuration::directory(const std::string&& v) {
    directory_ = std::move(v);
}

} } } }
