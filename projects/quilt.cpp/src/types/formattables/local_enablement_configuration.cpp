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
#include "dogen/quilt.cpp/types/formattables/local_enablement_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

local_enablement_configuration::local_enablement_configuration(local_enablement_configuration&& rhs)
    : facet_enabled_(std::move(rhs.facet_enabled_)),
      formatter_enabled_(std::move(rhs.formatter_enabled_)),
      facet_supported_(std::move(rhs.facet_supported_)),
      facet_overwrite_(std::move(rhs.facet_overwrite_)),
      formatter_overwrite_(std::move(rhs.formatter_overwrite_)) { }

local_enablement_configuration::local_enablement_configuration(
    const boost::optional<bool>& facet_enabled,
    const boost::optional<bool>& formatter_enabled,
    const boost::optional<bool>& facet_supported,
    const boost::optional<bool>& facet_overwrite,
    const boost::optional<bool>& formatter_overwrite)
    : facet_enabled_(facet_enabled),
      formatter_enabled_(formatter_enabled),
      facet_supported_(facet_supported),
      facet_overwrite_(facet_overwrite),
      formatter_overwrite_(formatter_overwrite) { }

void local_enablement_configuration::swap(local_enablement_configuration& other) noexcept {
    using std::swap;
    swap(facet_enabled_, other.facet_enabled_);
    swap(formatter_enabled_, other.formatter_enabled_);
    swap(facet_supported_, other.facet_supported_);
    swap(facet_overwrite_, other.facet_overwrite_);
    swap(formatter_overwrite_, other.formatter_overwrite_);
}

bool local_enablement_configuration::operator==(const local_enablement_configuration& rhs) const {
    return facet_enabled_ == rhs.facet_enabled_ &&
        formatter_enabled_ == rhs.formatter_enabled_ &&
        facet_supported_ == rhs.facet_supported_ &&
        facet_overwrite_ == rhs.facet_overwrite_ &&
        formatter_overwrite_ == rhs.formatter_overwrite_;
}

local_enablement_configuration& local_enablement_configuration::operator=(local_enablement_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<bool>& local_enablement_configuration::facet_enabled() const {
    return facet_enabled_;
}

boost::optional<bool>& local_enablement_configuration::facet_enabled() {
    return facet_enabled_;
}

void local_enablement_configuration::facet_enabled(const boost::optional<bool>& v) {
    facet_enabled_ = v;
}

void local_enablement_configuration::facet_enabled(const boost::optional<bool>&& v) {
    facet_enabled_ = std::move(v);
}

const boost::optional<bool>& local_enablement_configuration::formatter_enabled() const {
    return formatter_enabled_;
}

boost::optional<bool>& local_enablement_configuration::formatter_enabled() {
    return formatter_enabled_;
}

void local_enablement_configuration::formatter_enabled(const boost::optional<bool>& v) {
    formatter_enabled_ = v;
}

void local_enablement_configuration::formatter_enabled(const boost::optional<bool>&& v) {
    formatter_enabled_ = std::move(v);
}

const boost::optional<bool>& local_enablement_configuration::facet_supported() const {
    return facet_supported_;
}

boost::optional<bool>& local_enablement_configuration::facet_supported() {
    return facet_supported_;
}

void local_enablement_configuration::facet_supported(const boost::optional<bool>& v) {
    facet_supported_ = v;
}

void local_enablement_configuration::facet_supported(const boost::optional<bool>&& v) {
    facet_supported_ = std::move(v);
}

const boost::optional<bool>& local_enablement_configuration::facet_overwrite() const {
    return facet_overwrite_;
}

boost::optional<bool>& local_enablement_configuration::facet_overwrite() {
    return facet_overwrite_;
}

void local_enablement_configuration::facet_overwrite(const boost::optional<bool>& v) {
    facet_overwrite_ = v;
}

void local_enablement_configuration::facet_overwrite(const boost::optional<bool>&& v) {
    facet_overwrite_ = std::move(v);
}

const boost::optional<bool>& local_enablement_configuration::formatter_overwrite() const {
    return formatter_overwrite_;
}

boost::optional<bool>& local_enablement_configuration::formatter_overwrite() {
    return formatter_overwrite_;
}

void local_enablement_configuration::formatter_overwrite(const boost::optional<bool>& v) {
    formatter_overwrite_ = v;
}

void local_enablement_configuration::formatter_overwrite(const boost::optional<bool>&& v) {
    formatter_overwrite_ = std::move(v);
}

} } } }
