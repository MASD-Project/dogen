/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/settings/bundle.hpp"
#include "dogen/cpp/types/settings/opaque_settings.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& lhs,
const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace cpp {
namespace settings {

bundle::bundle(bundle&& rhs)
    : general_settings_(std::move(rhs.general_settings_)),
      type_settings_(std::move(rhs.type_settings_)),
      formatter_settings_(std::move(rhs.formatter_settings_)),
      opaque_settings_(std::move(rhs.opaque_settings_)) { }

bundle::bundle(
    const boost::optional<dogen::formatters::general_settings>& general_settings,
    const dogen::cpp::settings::type_settings& type_settings,
    const std::unordered_map<std::string, dogen::cpp::settings::formatter_settings>& formatter_settings,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >& opaque_settings)
    : general_settings_(general_settings),
      type_settings_(type_settings),
      formatter_settings_(formatter_settings),
      opaque_settings_(opaque_settings) { }

void bundle::swap(bundle& other) noexcept {
    using std::swap;
    swap(general_settings_, other.general_settings_);
    swap(type_settings_, other.type_settings_);
    swap(formatter_settings_, other.formatter_settings_);
    swap(opaque_settings_, other.opaque_settings_);
}

bool bundle::operator==(const bundle& rhs) const {
    return general_settings_ == rhs.general_settings_ &&
        type_settings_ == rhs.type_settings_ &&
        formatter_settings_ == rhs.formatter_settings_ &&
        opaque_settings_ == rhs.opaque_settings_;
}

bundle& bundle::operator=(bundle other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::general_settings>& bundle::general_settings() const {
    return general_settings_;
}

boost::optional<dogen::formatters::general_settings>& bundle::general_settings() {
    return general_settings_;
}

void bundle::general_settings(const boost::optional<dogen::formatters::general_settings>& v) {
    general_settings_ = v;
}

void bundle::general_settings(const boost::optional<dogen::formatters::general_settings>&& v) {
    general_settings_ = std::move(v);
}

const dogen::cpp::settings::type_settings& bundle::type_settings() const {
    return type_settings_;
}

dogen::cpp::settings::type_settings& bundle::type_settings() {
    return type_settings_;
}

void bundle::type_settings(const dogen::cpp::settings::type_settings& v) {
    type_settings_ = v;
}

void bundle::type_settings(const dogen::cpp::settings::type_settings&& v) {
    type_settings_ = std::move(v);
}

const std::unordered_map<std::string, dogen::cpp::settings::formatter_settings>& bundle::formatter_settings() const {
    return formatter_settings_;
}

std::unordered_map<std::string, dogen::cpp::settings::formatter_settings>& bundle::formatter_settings() {
    return formatter_settings_;
}

void bundle::formatter_settings(const std::unordered_map<std::string, dogen::cpp::settings::formatter_settings>& v) {
    formatter_settings_ = v;
}

void bundle::formatter_settings(const std::unordered_map<std::string, dogen::cpp::settings::formatter_settings>&& v) {
    formatter_settings_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >& bundle::opaque_settings() const {
    return opaque_settings_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >& bundle::opaque_settings() {
    return opaque_settings_;
}

void bundle::opaque_settings(const std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >& v) {
    opaque_settings_ = v;
}

void bundle::opaque_settings(const std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >&& v) {
    opaque_settings_ = std::move(v);
}

} } }