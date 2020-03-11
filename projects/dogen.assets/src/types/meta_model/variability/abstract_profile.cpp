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
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.assets/types/meta_model/variability/abstract_profile.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::assets::meta_model::name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::assets::meta_model::variability {

abstract_profile::abstract_profile(
    const dogen::assets::meta_model::name& name,
    const std::string& documentation,
    const dogen::assets::meta_model::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::assets::meta_model::name& meta_name,
    const dogen::assets::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<dogen::assets::meta_model::technical_space, boost::optional<dogen::assets::meta_model::decoration::element_properties> >& decoration,
    const std::string& stereotype,
    const std::list<dogen::assets::meta_model::name>& parents)
    : dogen::assets::meta_model::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      origin_element_id,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      artefact_properties,
      archetype_location_properties,
      decoration),
      stereotype_(stereotype),
      parents_(parents) { }

void abstract_profile::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::abstract_profile\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"stereotype\": " << "\"" << tidy_up_string(stereotype_) << "\"" << ", "
      << "\"parents\": " << parents_
      << " }";
}

void abstract_profile::swap(abstract_profile& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(stereotype_, other.stereotype_);
    swap(parents_, other.parents_);
}

bool abstract_profile::compare(const abstract_profile& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        stereotype_ == rhs.stereotype_ &&
        parents_ == rhs.parents_;
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

const std::list<dogen::assets::meta_model::name>& abstract_profile::parents() const {
    return parents_;
}

std::list<dogen::assets::meta_model::name>& abstract_profile::parents() {
    return parents_;
}

void abstract_profile::parents(const std::list<dogen::assets::meta_model::name>& v) {
    parents_ = v;
}

void abstract_profile::parents(const std::list<dogen::assets::meta_model::name>&& v) {
    parents_ = std::move(v);
}

}
