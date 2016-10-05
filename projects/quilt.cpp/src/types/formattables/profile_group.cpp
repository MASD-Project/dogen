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
#include "dogen/quilt.cpp/types/formattables/profile_group.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

profile_group::profile_group()
    : profile_type_(static_cast<dogen::quilt::cpp::formattables::profile_types>(0)) { }

profile_group::profile_group(profile_group&& rhs)
    : name_(std::move(rhs.name_)),
      parents_(std::move(rhs.parents_)),
      profile_type_(std::move(rhs.profile_type_)),
      bind_to_stereotype_(std::move(rhs.bind_to_stereotype_)),
      decoration_profile_(std::move(rhs.decoration_profile_)),
      default_facet_profile_(std::move(rhs.default_facet_profile_)),
      default_formatter_profile_(std::move(rhs.default_formatter_profile_)),
      facet_profiles_(std::move(rhs.facet_profiles_)),
      formatter_profiles_(std::move(rhs.formatter_profiles_)) { }

profile_group::profile_group(
    const std::string& name,
    const std::list<std::string>& parents,
    const dogen::quilt::cpp::formattables::profile_types profile_type,
    const std::string& bind_to_stereotype,
    const boost::optional<dogen::quilt::cpp::formattables::decoration_profile>& decoration_profile,
    const boost::optional<dogen::quilt::cpp::formattables::facet_profile>& default_facet_profile,
    const boost::optional<dogen::quilt::cpp::formattables::formatter_profile>& default_formatter_profile,
    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>& facet_profiles,
    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>& formatter_profiles)
    : name_(name),
      parents_(parents),
      profile_type_(profile_type),
      bind_to_stereotype_(bind_to_stereotype),
      decoration_profile_(decoration_profile),
      default_facet_profile_(default_facet_profile),
      default_formatter_profile_(default_formatter_profile),
      facet_profiles_(facet_profiles),
      formatter_profiles_(formatter_profiles) { }

void profile_group::swap(profile_group& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(parents_, other.parents_);
    swap(profile_type_, other.profile_type_);
    swap(bind_to_stereotype_, other.bind_to_stereotype_);
    swap(decoration_profile_, other.decoration_profile_);
    swap(default_facet_profile_, other.default_facet_profile_);
    swap(default_formatter_profile_, other.default_formatter_profile_);
    swap(facet_profiles_, other.facet_profiles_);
    swap(formatter_profiles_, other.formatter_profiles_);
}

bool profile_group::operator==(const profile_group& rhs) const {
    return name_ == rhs.name_ &&
        parents_ == rhs.parents_ &&
        profile_type_ == rhs.profile_type_ &&
        bind_to_stereotype_ == rhs.bind_to_stereotype_ &&
        decoration_profile_ == rhs.decoration_profile_ &&
        default_facet_profile_ == rhs.default_facet_profile_ &&
        default_formatter_profile_ == rhs.default_formatter_profile_ &&
        facet_profiles_ == rhs.facet_profiles_ &&
        formatter_profiles_ == rhs.formatter_profiles_;
}

profile_group& profile_group::operator=(profile_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& profile_group::name() const {
    return name_;
}

std::string& profile_group::name() {
    return name_;
}

void profile_group::name(const std::string& v) {
    name_ = v;
}

void profile_group::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& profile_group::parents() const {
    return parents_;
}

std::list<std::string>& profile_group::parents() {
    return parents_;
}

void profile_group::parents(const std::list<std::string>& v) {
    parents_ = v;
}

void profile_group::parents(const std::list<std::string>&& v) {
    parents_ = std::move(v);
}

dogen::quilt::cpp::formattables::profile_types profile_group::profile_type() const {
    return profile_type_;
}

void profile_group::profile_type(const dogen::quilt::cpp::formattables::profile_types v) {
    profile_type_ = v;
}

const std::string& profile_group::bind_to_stereotype() const {
    return bind_to_stereotype_;
}

std::string& profile_group::bind_to_stereotype() {
    return bind_to_stereotype_;
}

void profile_group::bind_to_stereotype(const std::string& v) {
    bind_to_stereotype_ = v;
}

void profile_group::bind_to_stereotype(const std::string&& v) {
    bind_to_stereotype_ = std::move(v);
}

const boost::optional<dogen::quilt::cpp::formattables::decoration_profile>& profile_group::decoration_profile() const {
    return decoration_profile_;
}

boost::optional<dogen::quilt::cpp::formattables::decoration_profile>& profile_group::decoration_profile() {
    return decoration_profile_;
}

void profile_group::decoration_profile(const boost::optional<dogen::quilt::cpp::formattables::decoration_profile>& v) {
    decoration_profile_ = v;
}

void profile_group::decoration_profile(const boost::optional<dogen::quilt::cpp::formattables::decoration_profile>&& v) {
    decoration_profile_ = std::move(v);
}

const boost::optional<dogen::quilt::cpp::formattables::facet_profile>& profile_group::default_facet_profile() const {
    return default_facet_profile_;
}

boost::optional<dogen::quilt::cpp::formattables::facet_profile>& profile_group::default_facet_profile() {
    return default_facet_profile_;
}

void profile_group::default_facet_profile(const boost::optional<dogen::quilt::cpp::formattables::facet_profile>& v) {
    default_facet_profile_ = v;
}

void profile_group::default_facet_profile(const boost::optional<dogen::quilt::cpp::formattables::facet_profile>&& v) {
    default_facet_profile_ = std::move(v);
}

const boost::optional<dogen::quilt::cpp::formattables::formatter_profile>& profile_group::default_formatter_profile() const {
    return default_formatter_profile_;
}

boost::optional<dogen::quilt::cpp::formattables::formatter_profile>& profile_group::default_formatter_profile() {
    return default_formatter_profile_;
}

void profile_group::default_formatter_profile(const boost::optional<dogen::quilt::cpp::formattables::formatter_profile>& v) {
    default_formatter_profile_ = v;
}

void profile_group::default_formatter_profile(const boost::optional<dogen::quilt::cpp::formattables::formatter_profile>&& v) {
    default_formatter_profile_ = std::move(v);
}

const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>& profile_group::facet_profiles() const {
    return facet_profiles_;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>& profile_group::facet_profiles() {
    return facet_profiles_;
}

void profile_group::facet_profiles(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>& v) {
    facet_profiles_ = v;
}

void profile_group::facet_profiles(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>&& v) {
    facet_profiles_ = std::move(v);
}

const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>& profile_group::formatter_profiles() const {
    return formatter_profiles_;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>& profile_group::formatter_profiles() {
    return formatter_profiles_;
}

void profile_group::formatter_profiles(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>& v) {
    formatter_profiles_ = v;
}

void profile_group::formatter_profiles(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>&& v) {
    formatter_profiles_ = std::move(v);
}

} } } }
