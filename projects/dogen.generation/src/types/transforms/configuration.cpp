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
#include "dogen.generation/types/transforms/configuration.hpp"

namespace dogen {
namespace generation {
namespace transforms {

configuration::configuration()
    : enable_backend_directories_(static_cast<bool>(0)) { }

configuration::configuration(
    const std::unordered_set<std::string>& enabled_backends,
    const bool enable_backend_directories)
    : enabled_backends_(enabled_backends),
      enable_backend_directories_(enable_backend_directories) { }

void configuration::swap(configuration& other) noexcept {
    using std::swap;
    swap(enabled_backends_, other.enabled_backends_);
    swap(enable_backend_directories_, other.enable_backend_directories_);
}

bool configuration::operator==(const configuration& rhs) const {
    return enabled_backends_ == rhs.enabled_backends_ &&
        enable_backend_directories_ == rhs.enable_backend_directories_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& configuration::enabled_backends() const {
    return enabled_backends_;
}

std::unordered_set<std::string>& configuration::enabled_backends() {
    return enabled_backends_;
}

void configuration::enabled_backends(const std::unordered_set<std::string>& v) {
    enabled_backends_ = v;
}

void configuration::enabled_backends(const std::unordered_set<std::string>&& v) {
    enabled_backends_ = std::move(v);
}

bool configuration::enable_backend_directories() const {
    return enable_backend_directories_;
}

void configuration::enable_backend_directories(const bool v) {
    enable_backend_directories_ = v;
}

} } }
