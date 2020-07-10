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
#include "dogen.physical/types/entities/extraction_properties.hpp"

namespace dogen::physical::entities {

extraction_properties::extraction_properties()
    : enable_backend_directories_(static_cast<bool>(0)) { }

extraction_properties::extraction_properties(extraction_properties&& rhs)
    : cpp_headers_output_directory_(std::move(rhs.cpp_headers_output_directory_)),
      enabled_backends_(std::move(rhs.enabled_backends_)),
      enable_backend_directories_(std::move(rhs.enable_backend_directories_)) { }

extraction_properties::extraction_properties(
    const boost::filesystem::path& cpp_headers_output_directory,
    const std::unordered_set<std::string>& enabled_backends,
    const bool enable_backend_directories)
    : cpp_headers_output_directory_(cpp_headers_output_directory),
      enabled_backends_(enabled_backends),
      enable_backend_directories_(enable_backend_directories) { }

void extraction_properties::swap(extraction_properties& other) noexcept {
    using std::swap;
    swap(cpp_headers_output_directory_, other.cpp_headers_output_directory_);
    swap(enabled_backends_, other.enabled_backends_);
    swap(enable_backend_directories_, other.enable_backend_directories_);
}

bool extraction_properties::operator==(const extraction_properties& rhs) const {
    return cpp_headers_output_directory_ == rhs.cpp_headers_output_directory_ &&
        enabled_backends_ == rhs.enabled_backends_ &&
        enable_backend_directories_ == rhs.enable_backend_directories_;
}

extraction_properties& extraction_properties::operator=(extraction_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& extraction_properties::cpp_headers_output_directory() const {
    return cpp_headers_output_directory_;
}

boost::filesystem::path& extraction_properties::cpp_headers_output_directory() {
    return cpp_headers_output_directory_;
}

void extraction_properties::cpp_headers_output_directory(const boost::filesystem::path& v) {
    cpp_headers_output_directory_ = v;
}

void extraction_properties::cpp_headers_output_directory(const boost::filesystem::path&& v) {
    cpp_headers_output_directory_ = std::move(v);
}

const std::unordered_set<std::string>& extraction_properties::enabled_backends() const {
    return enabled_backends_;
}

std::unordered_set<std::string>& extraction_properties::enabled_backends() {
    return enabled_backends_;
}

void extraction_properties::enabled_backends(const std::unordered_set<std::string>& v) {
    enabled_backends_ = v;
}

void extraction_properties::enabled_backends(const std::unordered_set<std::string>&& v) {
    enabled_backends_ = std::move(v);
}

bool extraction_properties::enable_backend_directories() const {
    return enable_backend_directories_;
}

void extraction_properties::enable_backend_directories(const bool v) {
    enable_backend_directories_ = v;
}

}
