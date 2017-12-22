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
#include "dogen.templating/types/wale/properties.hpp"

namespace dogen {
namespace templating {
namespace wale {

properties::properties(properties&& rhs)
    : template_path_(std::move(rhs.template_path_)),
      expected_keys_(std::move(rhs.expected_keys_)),
      supplied_kvps_(std::move(rhs.supplied_kvps_)) { }

properties::properties(
    const boost::filesystem::path& template_path,
    const std::unordered_set<std::string>& expected_keys,
    const std::unordered_map<std::string, std::string>& supplied_kvps)
    : template_path_(template_path),
      expected_keys_(expected_keys),
      supplied_kvps_(supplied_kvps) { }

void properties::swap(properties& other) noexcept {
    using std::swap;
    swap(template_path_, other.template_path_);
    swap(expected_keys_, other.expected_keys_);
    swap(supplied_kvps_, other.supplied_kvps_);
}

bool properties::operator==(const properties& rhs) const {
    return template_path_ == rhs.template_path_ &&
        expected_keys_ == rhs.expected_keys_ &&
        supplied_kvps_ == rhs.supplied_kvps_;
}

properties& properties::operator=(properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& properties::template_path() const {
    return template_path_;
}

boost::filesystem::path& properties::template_path() {
    return template_path_;
}

void properties::template_path(const boost::filesystem::path& v) {
    template_path_ = v;
}

void properties::template_path(const boost::filesystem::path&& v) {
    template_path_ = std::move(v);
}

const std::unordered_set<std::string>& properties::expected_keys() const {
    return expected_keys_;
}

std::unordered_set<std::string>& properties::expected_keys() {
    return expected_keys_;
}

void properties::expected_keys(const std::unordered_set<std::string>& v) {
    expected_keys_ = v;
}

void properties::expected_keys(const std::unordered_set<std::string>&& v) {
    expected_keys_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& properties::supplied_kvps() const {
    return supplied_kvps_;
}

std::unordered_map<std::string, std::string>& properties::supplied_kvps() {
    return supplied_kvps_;
}

void properties::supplied_kvps(const std::unordered_map<std::string, std::string>& v) {
    supplied_kvps_ = v;
}

void properties::supplied_kvps(const std::unordered_map<std::string, std::string>&& v) {
    supplied_kvps_ = std::move(v);
}

} } }
