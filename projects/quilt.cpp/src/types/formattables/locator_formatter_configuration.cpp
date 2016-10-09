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
#include "dogen/quilt.cpp/types/formattables/locator_formatter_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

locator_formatter_configuration::locator_formatter_configuration(
    const std::string& facet_directory,
    const std::string& facet_postfix,
    const std::string& formatter_postfix)
    : facet_directory_(facet_directory),
      facet_postfix_(facet_postfix),
      formatter_postfix_(formatter_postfix) { }

void locator_formatter_configuration::swap(locator_formatter_configuration& other) noexcept {
    using std::swap;
    swap(facet_directory_, other.facet_directory_);
    swap(facet_postfix_, other.facet_postfix_);
    swap(formatter_postfix_, other.formatter_postfix_);
}

bool locator_formatter_configuration::operator==(const locator_formatter_configuration& rhs) const {
    return facet_directory_ == rhs.facet_directory_ &&
        facet_postfix_ == rhs.facet_postfix_ &&
        formatter_postfix_ == rhs.formatter_postfix_;
}

locator_formatter_configuration& locator_formatter_configuration::operator=(locator_formatter_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& locator_formatter_configuration::facet_directory() const {
    return facet_directory_;
}

std::string& locator_formatter_configuration::facet_directory() {
    return facet_directory_;
}

void locator_formatter_configuration::facet_directory(const std::string& v) {
    facet_directory_ = v;
}

void locator_formatter_configuration::facet_directory(const std::string&& v) {
    facet_directory_ = std::move(v);
}

const std::string& locator_formatter_configuration::facet_postfix() const {
    return facet_postfix_;
}

std::string& locator_formatter_configuration::facet_postfix() {
    return facet_postfix_;
}

void locator_formatter_configuration::facet_postfix(const std::string& v) {
    facet_postfix_ = v;
}

void locator_formatter_configuration::facet_postfix(const std::string&& v) {
    facet_postfix_ = std::move(v);
}

const std::string& locator_formatter_configuration::formatter_postfix() const {
    return formatter_postfix_;
}

std::string& locator_formatter_configuration::formatter_postfix() {
    return formatter_postfix_;
}

void locator_formatter_configuration::formatter_postfix(const std::string& v) {
    formatter_postfix_ = v;
}

void locator_formatter_configuration::formatter_postfix(const std::string&& v) {
    formatter_postfix_ = std::move(v);
}

} } } }
