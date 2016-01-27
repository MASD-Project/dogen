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
#include "dogen/quilt.cpp/types/settings/bundle.hpp"
#include "dogen/quilt.cpp/types/settings/opaque_settings.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings>& lhs,
const boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

bundle::bundle(bundle&& rhs)
    : general_settings_(std::move(rhs.general_settings_)),
      element_settings_(std::move(rhs.element_settings_)),
      opaque_settings_(std::move(rhs.opaque_settings_)),
      opaque_settings_for_property_(std::move(rhs.opaque_settings_for_property_)) { }

bundle::bundle(
    const boost::optional<dogen::formatters::general_settings>& general_settings,
    const dogen::quilt::cpp::settings::element_settings& element_settings,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >& opaque_settings,
    const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >& opaque_settings_for_property)
    : general_settings_(general_settings),
      element_settings_(element_settings),
      opaque_settings_(opaque_settings),
      opaque_settings_for_property_(opaque_settings_for_property) { }

void bundle::swap(bundle& other) noexcept {
    using std::swap;
    swap(general_settings_, other.general_settings_);
    swap(element_settings_, other.element_settings_);
    swap(opaque_settings_, other.opaque_settings_);
    swap(opaque_settings_for_property_, other.opaque_settings_for_property_);
}

bool bundle::operator==(const bundle& rhs) const {
    return general_settings_ == rhs.general_settings_ &&
        element_settings_ == rhs.element_settings_ &&
        opaque_settings_ == rhs.opaque_settings_ &&
        opaque_settings_for_property_ == rhs.opaque_settings_for_property_;
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

const dogen::quilt::cpp::settings::element_settings& bundle::element_settings() const {
    return element_settings_;
}

dogen::quilt::cpp::settings::element_settings& bundle::element_settings() {
    return element_settings_;
}

void bundle::element_settings(const dogen::quilt::cpp::settings::element_settings& v) {
    element_settings_ = v;
}

void bundle::element_settings(const dogen::quilt::cpp::settings::element_settings&& v) {
    element_settings_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >& bundle::opaque_settings() const {
    return opaque_settings_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >& bundle::opaque_settings() {
    return opaque_settings_;
}

void bundle::opaque_settings(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >& v) {
    opaque_settings_ = v;
}

void bundle::opaque_settings(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >&& v) {
    opaque_settings_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >& bundle::opaque_settings_for_property() const {
    return opaque_settings_for_property_;
}

std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >& bundle::opaque_settings_for_property() {
    return opaque_settings_for_property_;
}

void bundle::opaque_settings_for_property(const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >& v) {
    opaque_settings_for_property_ = v;
}

void bundle::opaque_settings_for_property(const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >&& v) {
    opaque_settings_for_property_ = std::move(v);
}

} } } }
