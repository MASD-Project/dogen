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
#include "dogen/yarn/types/transforms/configuration.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

configuration::configuration()
    : enable_kernel_directories_(static_cast<bool>(0)) { }

configuration::configuration(
    const std::unordered_set<std::string>& enabled_kernels,
    const bool enable_kernel_directories)
    : enabled_kernels_(enabled_kernels),
      enable_kernel_directories_(enable_kernel_directories) { }

void configuration::swap(configuration& other) noexcept {
    using std::swap;
    swap(enabled_kernels_, other.enabled_kernels_);
    swap(enable_kernel_directories_, other.enable_kernel_directories_);
}

bool configuration::operator==(const configuration& rhs) const {
    return enabled_kernels_ == rhs.enabled_kernels_ &&
        enable_kernel_directories_ == rhs.enable_kernel_directories_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& configuration::enabled_kernels() const {
    return enabled_kernels_;
}

std::unordered_set<std::string>& configuration::enabled_kernels() {
    return enabled_kernels_;
}

void configuration::enabled_kernels(const std::unordered_set<std::string>& v) {
    enabled_kernels_ = v;
}

void configuration::enabled_kernels(const std::unordered_set<std::string>&& v) {
    enabled_kernels_ = std::move(v);
}

bool configuration::enable_kernel_directories() const {
    return enable_kernel_directories_;
}

void configuration::enable_kernel_directories(const bool v) {
    enable_kernel_directories_ = v;
}

} } }
