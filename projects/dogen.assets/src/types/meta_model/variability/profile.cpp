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
#include "dogen.assets/types/meta_model/element_visitor.hpp"
#include "dogen.assets/types/meta_model/variability/profile.hpp"
#include "dogen.assets/io/meta_model/variability/profile_entry_io.hpp"
#include "dogen.assets/io/meta_model/variability/abstract_profile_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::assets::meta_model::variability::profile_entry>& v) {
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

profile::profile(
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
    const std::list<dogen::assets::meta_model::name>& parents,
    const std::string& key_prefix,
    const std::list<dogen::assets::meta_model::variability::profile_entry>& entries)
    : dogen::assets::meta_model::variability::abstract_profile(
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
      decoration,
      stereotype,
      parents,
      key_prefix),
      entries_(entries) { }

void profile::accept(const element_visitor& v) const {
    v.visit(*this);
}

void profile::accept(element_visitor& v) const {
    v.visit(*this);
    }

void profile::accept(const element_visitor& v) {
    v.visit(*this);
}

void profile::accept(element_visitor& v) {
    v.visit(*this);
}

void profile::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::profile\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::variability::abstract_profile::to_stream(s);
    s << ", "
      << "\"entries\": " << entries_
      << " }";
}

void profile::swap(profile& other) noexcept {
    dogen::assets::meta_model::variability::abstract_profile::swap(other);

    using std::swap;
    swap(entries_, other.entries_);
}

bool profile::equals(const dogen::assets::meta_model::element& other) const {
    const profile* const p(dynamic_cast<const profile* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool profile::operator==(const profile& rhs) const {
    return dogen::assets::meta_model::variability::abstract_profile::compare(rhs) &&
        entries_ == rhs.entries_;
}

profile& profile::operator=(profile other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::assets::meta_model::variability::profile_entry>& profile::entries() const {
    return entries_;
}

std::list<dogen::assets::meta_model::variability::profile_entry>& profile::entries() {
    return entries_;
}

void profile::entries(const std::list<dogen::assets::meta_model::variability::profile_entry>& v) {
    entries_ = v;
}

void profile::entries(const std::list<dogen::assets::meta_model::variability::profile_entry>&& v) {
    entries_ = std::move(v);
}

}
