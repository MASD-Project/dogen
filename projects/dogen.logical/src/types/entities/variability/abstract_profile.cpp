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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/variability/abstract_profile.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::variability {

abstract_profile::abstract_profile(
    const dogen::logical::entities::name& name,
    const std::string& documentation,
    const dogen::logical::entities::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::entities::name& meta_name,
    const dogen::logical::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::string& stereotype,
    const std::list<dogen::logical::entities::name>& parents,
    const std::string& key_prefix)
    : dogen::logical::entities::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      artefact_properties,
      enablement_properties,
      decoration),
      stereotype_(stereotype),
      parents_(parents),
      key_prefix_(key_prefix) { }

void abstract_profile::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::variability::abstract_profile\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"stereotype\": " << "\"" << tidy_up_string(stereotype_) << "\"" << ", "
      << "\"parents\": " << parents_ << ", "
      << "\"key_prefix\": " << "\"" << tidy_up_string(key_prefix_) << "\""
      << " }";
}

void abstract_profile::swap(abstract_profile& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(stereotype_, other.stereotype_);
    swap(parents_, other.parents_);
    swap(key_prefix_, other.key_prefix_);
}

bool abstract_profile::compare(const abstract_profile& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        stereotype_ == rhs.stereotype_ &&
        parents_ == rhs.parents_ &&
        key_prefix_ == rhs.key_prefix_;
}

const std::string& abstract_profile::stereotype() const {
    return stereotype_;
}

std::string& abstract_profile::stereotype() {
    return stereotype_;
}

void abstract_profile::stereotype(const std::string& v) {
    stereotype_ = v;
}

void abstract_profile::stereotype(const std::string&& v) {
    stereotype_ = std::move(v);
}

const std::list<dogen::logical::entities::name>& abstract_profile::parents() const {
    return parents_;
}

std::list<dogen::logical::entities::name>& abstract_profile::parents() {
    return parents_;
}

void abstract_profile::parents(const std::list<dogen::logical::entities::name>& v) {
    parents_ = v;
}

void abstract_profile::parents(const std::list<dogen::logical::entities::name>&& v) {
    parents_ = std::move(v);
}

const std::string& abstract_profile::key_prefix() const {
    return key_prefix_;
}

std::string& abstract_profile::key_prefix() {
    return key_prefix_;
}

void abstract_profile::key_prefix(const std::string& v) {
    key_prefix_ = v;
}

void abstract_profile::key_prefix(const std::string&& v) {
    key_prefix_ = std::move(v);
}

}
